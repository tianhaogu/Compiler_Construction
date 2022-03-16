/* File: dppmain.cc
 * ----------------
 * This file defines the main() routine for the preprocessor, 
 * the filtering tool which runs before the compiler.
 */

#include "scanner.h"
#include "errors.h"
#include <stdio.h>

#include <iostream>
#include <unordered_map>

using namespace std;

/* Function: main()
 * ----------------
 * Entry point to the preprocessor.
 * As given below, this "filter" just copies stdin to stdout unchanged.
 * It will be your job to actually do some filtering, either by hand-coded
 * transformation of the input or by setting up a lex scanner in the dpp.l
 * file and changing the main below to invoke it via yylex. When finished,
 * the preprocessor should echo stdin to stdout making the transformations
 * to strip comments and handle preprocessor directives.
 */
int main(int argc, char *argv[]) {
    int ch;
    bool inString = false;
    bool inMultComment = false;
    bool inSingComment = false;
    bool creatingMacro = false;
    bool setMacro = false;
    int lineCounter = 1;
    int waitingChar = -1;
    unordered_map<string, string> macroMap;

    while ((ch = getc(stdin)) != EOF) {
        if (!inString && !inSingComment && !inMultComment && ch == '#') {
            string name = "";
            string value = "";
            int newCh = getc(stdin);
            if (isupper(newCh)) {
                creatingMacro = false;
                setMacro = false;
            } 
            else {
                creatingMacro = true;
                setMacro = true;
            }
            string def = "define";
            for (int i = 0; creatingMacro && i < 6; ++i) {
                if (newCh != def[i]) {
                    creatingMacro = false;
                    break;
                }
                newCh = getc(stdin);
            }
            if (setMacro && !creatingMacro) {
                ReportError::InvalidDirective(lineCounter);
                while (newCh != EOF) {
                    if (newCh == '\n') {
                        break;
                    }
                    newCh = getc(stdin);
                }
            }
            else {
                if (setMacro) {
                    bool flag = true;
                    newCh = getc(stdin);
                    while (newCh != EOF && newCh != ' ') {
                        if (!isupper(newCh)) {
                            flag = false;
                            ReportError::InvalidDirective(lineCounter);
                            while (newCh != EOF) {
                                if (newCh == '\n') {
                                    break;
                                }
                                newCh = getc(stdin);
                            }
                            break;
                        }
                        name += (char)newCh;
                        newCh = getc(stdin);
                    }
                    if (flag) {
                        newCh = getc(stdin);
                        while (newCh != EOF && newCh != '\n') {
                            value += (char)newCh;
                            newCh = getc(stdin);
                        }
                        macroMap[name] = value;
                    }
                }
                else {
                    while (newCh != EOF && isupper(newCh)) {
                        name += (char)newCh;
                        newCh = getc(stdin);
                    }
                    if (macroMap.find(name) == macroMap.end()) {
                        ReportError::InvalidDirective(lineCounter);
                        while (newCh != EOF) {
                            if (newCh == '\n') {
                                break;
                            }
                            newCh = getc(stdin);
                        }
                    }
                    else {
                        value = macroMap[name];
                        for (int i = 0; i < value.length(); ++i) {
                            putc((int)value[i], stdout);
                        }
                    }
                }
            }
            ch = newCh;
        }
        if (ch == EOF) {
            break;
        }
        if (ch == '\n') {
            lineCounter++;
            if (waitingChar != -1 && !inMultComment) {
                putc(waitingChar, stdout);
            }
            waitingChar = -1;
            putc(ch, stdout);
            inSingComment = false;
            inString = false;
            continue;
        }
        else {
            if (inSingComment) {
                continue;
            }
            else if (inMultComment) {
                if (waitingChar == '*') {
                    if (ch == '/') {
                        inMultComment = false;
                        waitingChar = -1;
                    }
                }
                if (ch == '*') {
                    waitingChar = ch;
                }
                continue;
            }
            else if (inString) {
                if (ch == '\\') {
                    if (waitingChar == '\\') {
                        waitingChar = -1;
                    }
                    else {
                        waitingChar == '\\';
                    }
                }
                else if (ch == '\"') {
                    if (waitingChar == '\\') {
                        inString = false;
                    }
                }
                putc(ch, stdout);
                continue;
            }
            else {
                if (waitingChar == '/') {
                    if (ch == '*') {
                        inMultComment = true;
                        waitingChar = -1;
                        continue;
                    }
                    else if (ch == '/') {
                        inSingComment = true;
                        waitingChar = -1;
                        continue;
                    }
                    else {
                        putc(waitingChar, stdout);
                        waitingChar = -1;
                    }
                }
                if (ch == '/') {
                    waitingChar = ch;
                    continue;
                }
                else if (ch == '\"') {
                    inString = true;
                }
            }
        }
        putc(ch, stdout);
    }
    return 0;
}
