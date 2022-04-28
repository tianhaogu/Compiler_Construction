/* File: codegen.cc
 * ----------------
 * Implementation for the CodeGenerator class. The methods don't do anything
 * too fancy, mostly just create objects of the various Tac instruction
 * classes and append them to the list.
 */

#include "codegen.h"
#include <string.h>
#include "tac.h"
#include "mips.h"
#include "ast_decl.h"
#include "errors.h"
  
CodeGenerator::CodeGenerator() {
    code = new List<Instruction*>();
    label_table = new Hashtable<Instruction*>;
    function_positions = new List<std::pair<int, int> >;
    curGlobalOffset = 0;
}

char *CodeGenerator::NewLabel() {
    static int nextLabelNum = 0;
    char temp[10];
    sprintf(temp, "_L%d", nextLabelNum++);
    return strdup(temp);
}


Location *CodeGenerator::GenTempVar() {
    static int nextTempNum;
    char temp[10];
    Location *result = NULL;
    sprintf(temp, "_tmp%d", nextTempNum++);
    return GenLocalVariable(temp);
}


Location *CodeGenerator::GenLocalVariable(const char *varName)
{            
    curStackOffset -= VarSize;
    return new Location(fpRelative, curStackOffset+4,  varName);
}

Location *CodeGenerator::GenGlobalVariable(const char *varName)
{
    curGlobalOffset += VarSize;
    return new Location(gpRelative, curGlobalOffset -4, varName);
}
 

Location *CodeGenerator::GenLoadConstant(int value) {
    Location *result = GenTempVar();
    code->Append(new LoadConstant(result, value));
    return result;
}

Location *CodeGenerator::GenLoadConstant(const char *s) {
    Location *result = GenTempVar();
    code->Append(new LoadStringConstant(result, s));
    return result;
} 

Location *CodeGenerator::GenLoadLabel(const char *label) {
    Location *result = GenTempVar();
    code->Append(new LoadLabel(result, label));
    return result;
} 


void CodeGenerator::GenAssign(Location *dst, Location *src) {
    code->Append(new Assign(dst, src));
}


Location *CodeGenerator::GenLoad(Location *ref, int offset) {
    Location *result = GenTempVar();
    code->Append(new Load(result, ref, offset));
    return result;
}

void CodeGenerator::GenStore(Location *dst,Location *src, int offset) {
    code->Append(new Store(dst, src, offset));
}


Location *CodeGenerator::GenBinaryOp(const char *opName, Location *op1, Location *op2) {
    Location *result = GenTempVar();
    code->Append(new BinaryOp(BinaryOp::OpCodeForName(opName), result, op1, op2));
    return result;
}


void CodeGenerator::GenLabel(const char *label) {
    code->Append(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, const char *label) {
    code->Append(new IfZ(test, label));
}

void CodeGenerator::GenGoto(const char *label) {
    code->Append(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val) {
    code->Append(new Return(val));
}


BeginFunc *CodeGenerator::GenBeginFunc(FnDecl *fn) {
    BeginFunc *result = new BeginFunc;
    code->Append(insideFn = result);
    List<VarDecl*> *formals = fn->GetFormals();
    int start = OffsetToFirstParam;
    if (fn->IsMethodDecl()) start += VarSize;
    for (int i = 0; i < formals->NumElements(); i++)
        formals->Nth(i)->rtLoc = new Location(fpRelative, i*VarSize + start, formals->Nth(i)->GetName());
    curStackOffset = OffsetToFirstLocal;
    return result;
}

void CodeGenerator::GenEndFunc() {
    code->Append(new EndFunc());
    insideFn->SetFrameSize(OffsetToFirstLocal-curStackOffset);
    insideFn = NULL;
}

void CodeGenerator::GenPushParam(Location *param) {
    code->Append(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams) {
    Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0); // sanity check
    if (numBytesOfParams > 0)
        code->Append(new PopParams(numBytesOfParams));
}

Location *CodeGenerator::GenLCall(const char *label, bool fnHasReturnValue) {
    Location *result = fnHasReturnValue ? GenTempVar() : NULL;
    code->Append(new LCall(label, result));
    return result;
}

Location *CodeGenerator::GenFunctionCall(const char *fnLabel, List<Location*> *args, bool hasReturnValue) {
    for (int i = args->NumElements()-1; i >= 0; i--) // push params right to left
        GenPushParam(args->Nth(i));
    Location *result = GenLCall(fnLabel, hasReturnValue);
    GenPopParams(args->NumElements()*VarSize);
    return result;
}

Location *CodeGenerator::GenACall(Location *fnAddr, bool fnHasReturnValue) {
    Location *result = fnHasReturnValue ? GenTempVar() : NULL;
    code->Append(new ACall(fnAddr, result));
    return result;
}
 
Location *CodeGenerator::GenMethodCall(Location *rcvr, Location *meth, List<Location*> *args, bool fnHasReturnValue) {
    for (int i = args->NumElements()-1; i >= 0; i--)
        GenPushParam(args->Nth(i));
    GenPushParam(rcvr);	// hidden "this" parameter
    Location *result= GenACall(meth, fnHasReturnValue);
    GenPopParams((args->NumElements()+1)*VarSize);
    return result;
}


static struct _builtin {
  const char *label;
  int numArgs;
  bool hasReturn;
} builtins[] =
 {{"_Alloc", 1, true},
  {"_ReadLine", 0, true},
  {"_ReadInteger", 0, true},
  {"_StringEqual", 2, true},
  {"_PrintInt", 1, false},
  {"_PrintString", 1, false},
  {"_PrintBool", 1, false},
  {"_Halt", 0, false}};

Location *CodeGenerator::GenBuiltInCall(BuiltIn bn,Location *arg1, Location *arg2) {
    Assert(bn >= 0 && bn < NumBuiltIns);
    struct _builtin *b = &builtins[bn];
    Location *result = NULL;

    if (b->hasReturn) result = GenTempVar();
                // verify appropriate number of non-NULL arguments given
    Assert((b->numArgs == 0 && !arg1 && !arg2)
	    || (b->numArgs == 1 && arg1 && !arg2)
	    || (b->numArgs == 2 && arg1 && arg2));
    if (arg2) code->Append(new PushParam(arg2));
    if (arg1) code->Append(new PushParam(arg1));
    code->Append(new LCall(b->label, result));
    GenPopParams(VarSize*b->numArgs);
    return result;
}


void CodeGenerator::GenVTable(const char *className, List<const char *> *methodLabels) {
    code->Append(new VTable(className, methodLabels));
}


void CodeGenerator::DoFinalCodeGen() {
    LivenessAnalysis();
    if (IsDebugOn("tac")) { // if debug don't translate to mips, just print Tac
        for (int i = 0; i < code->NumElements(); i++)
	        code->Nth(i)->Print();
    }
    else {
        Mips mips;
        List<Location*> locations;
        for (int i = 0; i < code->NumElements(); ++i) {
            for (int j = 0; j < code->Nth(i)->GetLiveVariables()->NumElements(); ++j)
                locations.Append(code->Nth(i)->GetLiveVariables()->Nth(j));
        }
        locations.Unique();
        mips.AllocateRegisters(&locations);
        mips.EmitPreamble();
        for (int i = 0; i < code->NumElements(); i++)
	        code->Nth(i)->Emit(&mips);
    }
}



Location *CodeGenerator::GenArrayLen(Location *array) {
    return GenLoad(array, -4);
}

Location *CodeGenerator::GenNew(const char *vTableLabel, int instanceSize) {
    Location *size = GenLoadConstant(instanceSize);
    Location *result = GenBuiltInCall(Alloc, size);
    Location *vt = GenLoadLabel(vTableLabel);
    GenStore(result, vt);
    return result;
}


Location *CodeGenerator::GenDynamicDispatch(Location *rcvr, int vtableOffset, List<Location*> *args, bool hasReturnValue) {
    Location *vptr = GenLoad(rcvr); // load vptr
    Assert(vtableOffset >= 0);
    Location *m = GenLoad(vptr, vtableOffset*4);
    return GenMethodCall(rcvr, m, args, hasReturnValue);
}

// all variables (ints, bools, ptrs, arrays) are 4 bytes in for code generation
// so this simplifies the math for offsets
Location *CodeGenerator::GenSubscript(Location *array, Location *index) {
    Location *zero = GenLoadConstant(0);
    Location *isNegative = GenBinaryOp("<", index, zero);
    Location *count = GenLoad(array, -4);
    Location *isWithinRange = GenBinaryOp("<", index, count);
    Location *pastEnd = GenBinaryOp("==", isWithinRange, zero);
    Location *outOfRange = GenBinaryOp("||", isNegative, pastEnd);
    const char *pastError = NewLabel();
    GenIfZ(outOfRange, pastError);
    GenHaltWithMessage(err_arr_out_of_bounds);
    GenLabel(pastError);
    Location *four = GenLoadConstant(VarSize);
    Location *offset = GenBinaryOp("*", four, index);
    Location *elem = GenBinaryOp("+", array, offset);
    return new Location(elem, 0); 
}



Location *CodeGenerator::GenNewArray(Location *numElems) {
    Location *one = GenLoadConstant(1);
    Location *isNonpositive = GenBinaryOp("<", numElems, one);
    const char *pastError = NewLabel();
    GenIfZ(isNonpositive, pastError);
    GenHaltWithMessage(err_arr_bad_size);
    GenLabel(pastError);

    // need (numElems+1)*VarSize total bytes (extra 1 is for length)
    Location *arraySize = GenLoadConstant(1);
    Location *num = GenBinaryOp("+", arraySize, numElems);
    Location *four = GenLoadConstant(VarSize);
    Location *bytes = GenBinaryOp("*", num, four);
    Location *result = GenBuiltInCall(Alloc, bytes);
    GenStore(result, numElems);
    return GenBinaryOp("+", result, four);
}

void CodeGenerator::GenHaltWithMessage(const char *message) {
    Location *msg = GenLoadConstant(message);
    GenBuiltInCall(PrintString, msg);
    GenBuiltInCall(Halt, NULL);
}

void CodeGenerator::ConstructCFG() {
    for (int i = 0; i < code-> NumElements(); i++) {
        if (dynamic_cast<Label*> (code-> Nth(i)) && i != code-> NumElements() - 1) {
            Label *label = dynamic_cast<Label*> (code-> Nth(i));
            label_table-> Enter(label-> GetLabel(), code-> Nth(i + 1));
        }
    }
    bool isInFunction = false;
    int function_begin = -1;
    for (int i = 0; i < code-> NumElements() - 1; i++) {
        if (isInFunction) {
            if (dynamic_cast<EndFunc*> (code-> Nth(i))) {
                isInFunction = false;
                function_positions-> Append(std::make_pair(function_begin, i));
            }
            else if (dynamic_cast<Goto*> (code-> Nth(i))) {
                Goto *gt = dynamic_cast<Goto*> (code-> Nth(i));
                Instruction *goto_tac = label_table-> Lookup(gt-> GetLabel());
                gt-> successors.Append(goto_tac);
            }
            else if (dynamic_cast<IfZ*> (code-> Nth(i))) {
                IfZ *ifz = dynamic_cast<IfZ*> (code-> Nth(i));
                Instruction *ifz_tac = label_table-> Lookup(ifz-> GetLabel());
                ifz-> successors.Append(ifz_tac);
                ifz-> successors.Append(code-> Nth(i + 1));  // need to consider???
            }
            else {
                Instruction *inst = code-> Nth(i);
                inst-> successors.Append(code-> Nth(i + 1));
            }
        }
        else if (dynamic_cast<BeginFunc*> (code-> Nth(i))) {
            isInFunction = true;
            function_begin = i;
            BeginFunc *bgfn = dynamic_cast<BeginFunc*> (code-> Nth(i));
            bgfn-> successors.Append(code-> Nth(i + 1));
        }
    }
}

void CodeGenerator::VarLiveAnalysis() {
    for (int p = 0; p < function_positions-> NumElements(); p++) {  // loop over functions one by one
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = function_positions-> Nth(p).second; i >= function_positions-> Nth(p).first; i--) {  // for each TAC in CFG
                Instruction *curr_tac = code-> Nth(i);
                // OUT[TAC] = Union(IN[SUCC(TAC)])
                for (int j = 0; j < curr_tac-> successors.NumElements(); j++) {
                    curr_tac-> out_set.insert(curr_tac-> successors.Nth(j)-> in_set.begin(), curr_tac-> successors.Nth(j)-> in_set.end());
                }
                // IN'[TAC] = OUT[TAC] - KILL(TAC) + GEN(TAC)
                curr_tac-> SetGen();
                curr_tac-> SetKill();
                curr_tac-> intemp_set = curr_tac-> out_set;
                for (auto kill_item : curr_tac-> kill_set) {
                    curr_tac-> intemp_set.erase(kill_item);
                }
                curr_tac-> intemp_set.insert(curr_tac-> gen_set.begin(), curr_tac-> gen_set.end());
                // if IN'[TAC] != IN[TAC]
                if (curr_tac-> intemp_set != curr_tac-> in_set) {
                    curr_tac-> in_set = curr_tac-> intemp_set;
                    changed = true;
                }
            }
        }
    }
}

void CodeGenerator::ConstructRIG() {
    for (int p = 0; p < function_positions-> NumElements(); p++) {
        BeginFunc* bgfn = dynamic_cast<BeginFunc*> (code-> Nth(function_positions-> Nth(p).first));
        for (int i = function_positions-> Nth(p).first; i <= function_positions-> Nth(p).second; i++) {
            Instruction *curr_tac = code-> Nth(i);
            for (auto in_item_src : curr_tac-> in_set) {
                if (bgfn-> inter_graph.find(in_item_src) == bgfn-> inter_graph.end()) {
                    bgfn-> inter_graph[in_item_src] = {};
                }
                for (auto in_item_dst : curr_tac-> in_set) {
                    if (in_item_src != in_item_dst) {
                        bgfn-> inter_graph[in_item_src].insert(in_item_dst);
                    }
                }
            }
            // Do the same thing for the union of out_set and kill_set, but don't know why ???
        }
    }
}

void CodeGenerator::ColorGraph() {
    int k = 10000;  // try
    for (int p = 0; p < function_positions-> NumElements(); p++) {
        std::stack<Location*> nodes_removed;
        BeginFunc* bgfn = dynamic_cast<BeginFunc*> (code-> Nth(function_positions-> Nth(p).first));
        // 1. Remove the nodes
        while (bgfn-> inter_graph.size() > 0) {
            Location *node_to_remove = NULL;
            int max_edges = -1;
            for (auto node : bgfn-> inter_graph) {
                if (node.second.size() < k) {
                    node_to_remove = node.first;
                    break;
                }
                if (node.second.size() > max_edges) {
                    node_to_remove = node.first;
                    max_edges = node.second.size();
                }
            }
            for (auto node_to : bgfn-> inter_graph[node_to_remove]) {
                bgfn-> inter_graph[node_to].erase(node_to_remove);
            }
            nodes_removed.push(node_to_remove);
            bgfn-> inter_graph.erase(node_to_remove);
        }
        // Reconstruct the graph
        while (!nodes_removed.empty()) {
            Location *curr_node = nodes_removed.top();
            nodes_removed.pop();
            // remaining for registers
        }
    }
}

/*To be implemented.*/
void CodeGenerator::LivenessAnalysis() {
    this-> ConstructCFG();
    this-> VarLiveAnalysis();
    this-> ConstructRIG();
    this-> ColorGraph();
}
