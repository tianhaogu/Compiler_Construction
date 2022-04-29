/* File: tac.h
 * -----------
 * This module contains the Instruction class (and its various
 * subclasses) that represent Tac instructions and the Location
 * class used for operands to those instructions.
 *
 * Each instruction is mostly just a little struct with a
 * few fields, but each responds polymorphically to the methods
 * Print and Emit, the first is used to print out the TAC form of
 * the instruction (helpful when debugging) and the second to
 * convert to the appropriate MIPS assembly.
 *
 * The operands to each instruction are of Location class.
 * A Location object is a simple representation of where a variable
 * exists at runtime, i.e. whether it is on the stack or global
 * segment and at what offset relative to the current fp or gp.
 *
 * You may need to make changes/extensions to these classes
 * if you are working on IR optimization.

 */

#ifndef _H_tac
#define _H_tac

#include "list.h" // for VTable
#include <set>
#include <map>
// #include "mips.h"
class Mips;


    // A Location object is used to identify the operands to the
    // various TAC instructions. A Location is either fp or gp
    // relative (depending on whether in stack or global segemnt)
    // and has an offset relative to the base of that segment.
    // For example, a declaration for integer num as the first local
    // variable in a function would be assigned a Location object
    // with name "num", segment fpRelative, and offset -8. 
 
typedef enum {fpRelative, gpRelative} Segment;

class Location
{
  protected:
    const char *variableName;
    Segment segment;
    int offset;
    Location *reference;
    int refOffset;
    int spillCost;
    List<Location*> interferences;
    // Mips::Register regst;
	  
  public:
    Location(Segment seg, int offset, const char *name);
    Location(Location *base, int refOff) :
	variableName(base->variableName), segment(base->segment),
	offset(base->offset), reference(base), refOffset(refOff) {}
 
    const char *GetName()           { return variableName; }
    Segment GetSegment()            { return segment; }
    int GetOffset()                 { return offset; }
    bool IsReference()              { return reference != NULL; }
    Location *GetReference()        { return reference; }
    int GetRefOffset()              { return refOffset; }
    void IncrementSpillCost() { ++spillCost; }
    double GetScore() { return static_cast<double>(spillCost) / interferences.NumElements(); }
    void AddInterference(Location *loc) {
	    interferences.Remove(loc);
	    interferences.Append(loc);
    }
    List<Location*> *GetInterferences() { return &interferences; }
    // void SetRegister(Mips::Register reg) { regst = reg; }
    // Mips::Register GetRegister() { return regst; }
};
 


  // base class from which all Tac instructions derived
  // has the interface for the 2 polymorphic messages: Print & Emit
  
class Instruction {
  protected:
    char printed[128];
	  
  public:
	virtual void Print();
	virtual void EmitSpecific(Mips *mips) = 0;
	virtual void Emit(Mips *mips);
    void AddSuccessor(Instruction* tac) { successors.Append(tac); }
    List<Location*> *GetLiveVariables() { return &liveVariables; }
    virtual void SetKill() { return; }
    virtual void SetGen() { return; }
    List<Instruction*> successors;  // can be changed to std::list due to the new operation in constructor of children classes ???
	List<Location*> liveVariables;
    // type of elements need to be Location* ???
    std::set<Location*> in_set;
    std::set<Location*> intemp_set;
    std::set<Location*> out_set;
    std::set<Location*> kill_set;
    std::set<Location*> gen_set;
    bool Analyze();
    /*Abstract function for all children class. Uncomment and implement for the other children classes*/
    //virtual void AnalyzeSpecific() = 0;
};

  
  
  // for convenience, the instruction classes are listed here.
  // the interfaces for the classes follows below
  
class LoadConstant;
class LoadStringConstant;
class LoadLabel;
class Assign;
class Load;
class Store;
class BinaryOp;
class Label;
class Goto;
class IfZ;
class BeginFunc;
class EndFunc;
class Return;
class PushParam;
class RemoveParams;
class LCall;
class ACall;
class VTable;


typedef std::map<Location*, std::set<Location*> > INTERFERENCEGRAPH;


class LoadConstant: public Instruction {
    Location *dst;
    int val;
  public:
    LoadConstant(Location *dst, int val);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
};

class LoadStringConstant: public Instruction {
    Location *dst;
    char *str;
  public:
    LoadStringConstant(Location *dst, const char *s);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
};
    
class LoadLabel: public Instruction {
    Location *dst;
    const char *label;
  public:
    LoadLabel(Location *dst, const char *label);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
};

class Assign: public Instruction {
    Location *dst, *src;
  public:
    Assign(Location *dst, Location *src);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
    void SetGen() { gen_set.insert(src); }
};

class Load: public Instruction {
    Location *dst, *src;
    int offset;
  public:
    Load(Location *dst, Location *src, int offset = 0);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
    void SetGen() { gen_set.insert(src); }
};

class LoadThis: public Instruction {
    Location *src;
  public:
    LoadThis(Location *src);
    void EmitSpecific(Mips *mips);
    void SetGen() { gen_set.insert(src); }
};

class Store: public Instruction {
    Location *dst, *src;
    int offset;
  public:
    Store(Location *d, Location *s, int offset = 0);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
    void SetGen() { gen_set.insert(src); }
};

class BinaryOp: public Instruction {
  public:
    typedef enum {Add, Sub, Mul, Div, Mod, Eq, Less, And, Or, NumOps} OpCode;
    static const char * const opName[NumOps];
    static OpCode OpCodeForName(const char *name);
    
  protected:
    OpCode code;
    Location *dst, *op1, *op2;
  public:
    BinaryOp(OpCode c, Location *dst, Location *op1, Location *op2);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
    void SetGen() { gen_set.insert(op1); gen_set.insert(op2); }
};

class Label: public Instruction {
    const char *label;
  public:
    Label(const char *label);
    void Print();
    void EmitSpecific(Mips *mips);
    const char *GetLabel() { return label; }
};

class Goto: public Instruction {
    const char *label;
  public:
    Goto(const char *label);
    void EmitSpecific(Mips *mips);
    const char *GetLabel() { return label; }
};

class IfZ: public Instruction {
    Location *test;
    const char *label;
  public:
    IfZ(Location *test, const char *label);
    void EmitSpecific(Mips *mips);
    const char *GetLabel() { return label; }
    void SetGen() { gen_set.insert(test); }
};

class BeginFunc: public Instruction {
    int frameSize;
    bool IsMethodDecl;
  public:
    BeginFunc();
    BeginFunc(bool IsMethodDecl);
    // used to backpatch the instruction with frame size once known
    void SetFrameSize(int numBytesForAllLocalsAndTemps);
    void EmitSpecific(Mips *mips);
    void SetGen() { return; }
    // INTERFERENCEGRAPH inter_graph;
};

class EndFunc: public Instruction {
  public:
    EndFunc();
    void EmitSpecific(Mips *mips);
};

class Return: public Instruction {
    Location *val;
  public:
    Return(Location *val);
    void EmitSpecific(Mips *mips);
    void SetGen() { if (val) gen_set.insert(val); }
};   

class PushParam: public Instruction {
    Location *param;
  public:
    PushParam(Location *param);
    void EmitSpecific(Mips *mips);
    void SetGen() { gen_set.insert(param); }
}; 

class PopParams: public Instruction {
    int numBytes;
  public:
    PopParams(int numBytesOfParamsToRemove);
    void EmitSpecific(Mips *mips);
}; 

class CallerSave: public Instruction {

  public:

    void EmitSpecific(Mips *mips);
}; 

class CallerLoad: public Instruction {
    Location *dst;
    Location *th;
  public:
    CallerLoad(Location *d, Location *t);
    void EmitSpecific(Mips *mips);
}; 

class LCall: public Instruction {
    const char *label;
    Location *dst;
  public:
    LCall(const char *labe, Location *result);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
};

class ACall: public Instruction {
    Location *dst, *methodAddr;
  public:
    ACall(Location *meth, Location *result);
    void EmitSpecific(Mips *mips);
    void SetKill() { kill_set.insert(dst); }
};

class VTable: public Instruction {
    List<const char *> *methodLabels;
    const char *label;
  public:
    VTable(const char *labelForTable, List<const char *> *methodLabels);
    void Print();
    void EmitSpecific(Mips *mips);
};


#endif
