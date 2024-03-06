#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>    
#include <cmath>
#include <algorithm> 
#include <vector>
#include <regex>

using namespace std;

void __parseerror(int errcode, int lineNum, int offset) {
    static const char* errstr[] = {
        "NUM_EXPECTED",           
        "SYM_EXPECTED",           
        "MARIE_EXPECTED",         
        "SYM_TOO_LONG",           
        "TOO_MANY_DEF_IN_MODULE", 
        "TOO_MANY_USE_IN_MODULE", 
        "TOO_MANY_INSTR"          
    };
    cout << "Parse Error line"
         << " " 
         << lineNum 
         << " "
         << "offset" << " " << offset 
         << ":" 
         << " "
         << errstr[errcode]  
         << endl;

    exit(0);
};

int readInt(string token, int lineNum, int offset) {  
    if (!isdigit(token[0])) { 
        __parseerror(0, lineNum, offset);
    } 
    else { 
        if (offset >= pow(2,30)){ 
         __parseerror(0, lineNum, offset);
        } 
    };
    return stoi(token);
};

string readSymbol(const string& token, int lineNum, int offset, int tokenLen) {
    for (char c : token) {
        if (!isalnum(c)) {
            __parseerror(1, lineNum, offset);
        }
    }

    if (all_of(token.begin(), token.end(), ::isdigit) == true) { 
        __parseerror(1, lineNum, offset);
    }

    if (tokenLen > 16) {
        __parseerror(3, lineNum, offset);
    }

    return token;
}

char readMARIE(string token, int lineNum, int offset) { 
    if (token[0] != 'M' && 
        token[0] != 'A' && 
        token[0] != 'R' && 
        token[0] != 'I' &&  
        token[0] != 'E') { 
        __parseerror(2, lineNum, offset);  
    } 
    return token[0];
};

int moduleNumPass1 = 0;
int moduleNumPass2 = 0;
map <int, int> baseAdressMod;  

map <string, string> Parser1(string filename) {

    ifstream inputFile(filename);
    map <string, string> symbolTable; 
    vector <string> symbolTableVec;
    vector <string> symbolTableWarnings;

    vector <string> defListSym; 
    vector <int> defListAddr;    

    string line;
    int lineNum = 1;
    int offset = 1;
    int match = 0;
    int tokenLen = 0;

    bool defCountDone = false;
    int defCount = 0;
    int defCountTotal = 0;
    string defSym = "";
    int defAddr = 0;
    bool defSymAddrSwap = false;
    int defCountIncr = 0;

    bool useCountDone = false;
    int usecountTotal = 0;
    string useSym = "";
    int useCountIncr = 0;

    bool codeCountDone = false;
    int codeCount = 0;
    int codeCountFile = 0;
    int codeCountTotal = 0; 
    char addrmode;
    int instr = 0;
    int codeCountIncr = 0;
    bool addrmodeInstrSwap = false;
    int baseAddress = 0;
    int opcode = 0; 
    int operand = 0;
    string operandBaseAddress = "";
    string rightError = "";
    
    while (getline(inputFile, line)) {
        int match = -1;
        char * lineChar = new char[line.length() + 1];
        strcpy(lineChar, line.c_str());
        char * token = strtok(lineChar, " \t");
        while (token != NULL) {
            match = line.find(token, match + 1);
            line = line.replace(0, match+strlen(token), match + strlen(token), '_');
            tokenLen = strlen(token);
            offset = match + 1;

            /////////////////////////////////////////////////////
            //////////////////// 1) DEF LIST ////////////////////
            /////////////////////////////////////////////////////

            if (defCountDone == false) {
                defCount = readInt(token, lineNum, offset); 
                if (defCount > 16) { 
                    __parseerror(4, lineNum, offset);
                }
                defCountTotal = 2 * defCount;
                defCountDone = true;
                token = strtok(NULL, " \t");
                continue;
            }
            
            if (defCountDone == true && defCountIncr < defCountTotal) { 
                if (defCountTotal == 0) { 
                    defCountIncr = defCountIncr + 1;
                    
                    token = strtok(NULL, " \t");
                    continue;
                }
                
                if (defSymAddrSwap == false) { 
                    defSym = readSymbol(token, lineNum, offset, tokenLen);
                    defListSym.push_back(defSym);
                    defSymAddrSwap = true;
                }

                else if (defSymAddrSwap == true) { 
                    defAddr = readInt(token, lineNum, offset);
                    defListAddr.push_back(defAddr);
                    defSymAddrSwap = false;
                }

                defCountIncr = defCountIncr + 1;
                token = strtok(NULL, " \t");
                continue;
            }
            
            /////////////////////////////////////////////////////
            //////////////////// 2) USE LIST ////////////////////
            /////////////////////////////////////////////////////

            if (useCountDone == false) { 
                usecountTotal = readInt(token, lineNum, offset); 

                if (usecountTotal > 16) { 
                    __parseerror(5, lineNum, offset);
                }      

                useCountDone = true;
                token = strtok(NULL, " \t");
                continue;
            }

            if (useCountDone == true && useCountIncr < usecountTotal) { 
                useSym = readSymbol(token, lineNum, offset, tokenLen);
                useCountIncr = useCountIncr + 1;
                token = strtok(NULL, " \t");
                continue;
            }

            //////////////////////////////////////////////////////
            /////////////////// 3) PROGRAM TEXT //////////////////
            //////////////////////////////////////////////////////

            if (codeCountDone == false) { 
                codeCount = readInt(token, lineNum, offset);
                codeCountFile = codeCountFile + codeCount;

                if (codeCountFile > 512) { 
                    __parseerror(6, lineNum, offset);
                }

                for (int i=0; i < defListSym.size(); i++) { 
                    auto it = symbolTable.find(defListSym[i]);
                    if (it == symbolTable.end()) { 
                        if (codeCount < defListAddr[i] || codeCount == 0) { 
                            symbolTableWarnings.push_back("Warning: Module " + 
                                                          to_string(moduleNumPass1) + 
                                                          ":" + 
                                                          " " + 
                                                          defListSym[i] + 
                                                          "=" + 
                                                          to_string(defListAddr[i]) + 
                                                          " " + 
                                                          "valid" + 
                                                          "=" + 
                                                          "["  + 
                                                          "0" + 
                                                          ".." + 
                                                          to_string(codeCount-1) + 
                                                          "]" + 
                                                          " " + 
                                                          "assume zero relative");
                            if (baseAddress <= 512) { 
                                symbolTable[defListSym[i]] = to_string(baseAddress);
                                symbolTableVec.push_back(defListSym[i] + "=" + to_string(baseAddress));
                            }
                            else { 
                                symbolTable[defListSym[i]] = "512";
                                symbolTableVec.push_back(defListSym[i] + "=" + "512");
                            }
                        }
                        else if (codeCount >= defListAddr[i]) { 
                            symbolTable[defListSym[i]] = to_string(defListAddr[i] + baseAddress); 
                            if (defListAddr[i] + baseAddress <= 512) { 
                                symbolTableVec.push_back(defListSym[i] + "=" + to_string(defListAddr[i] + baseAddress));
                            } 
                            else { 
                                symbolTableVec.push_back(defListSym[i] + "=" + "512");
                            }
                        }
                    }
                    else if (it != symbolTable.end()) { 
                        for (int j = 0; j < symbolTableVec.size(); j++) {
                            rightError = " Error: This variable is multiple times defined; first value used";
                            auto foundError = symbolTableVec[j].find(" Error: This variable");

                            if (symbolTableVec[j] == defListSym[i] + "=" + symbolTable[defListSym[i]]) {
                                symbolTableVec[j] += rightError;
                                symbolTableWarnings.push_back("Warning: Module " + 
                                                              to_string(moduleNumPass1) +
                                                              ": " + 
                                                              defListSym[i] + 
                                                              " redefinition ignored");
                            }

                            else if (symbolTableVec[j] == defListSym[i]+"="+symbolTable[defListSym[i]] + rightError) { 
                                symbolTableVec[j] = std::regex_replace(symbolTableVec[j], std::regex(rightError), "");
                                symbolTableVec[j] += rightError;
                                symbolTableWarnings.push_back("Warning: Module " + 
                                                              to_string(moduleNumPass1) + 
                                                              ": " + 
                                                              defListSym[i] + 
                                                              " redefinition ignored");
                            }
                        }                                
                    }
                }                         
                          
                codeCountTotal = codeCount * 2;
                codeCountDone = true;
                token = strtok(NULL, " \t");
                continue;
            };
        
            if (codeCountDone == true) { 
                if (addrmodeInstrSwap == false && codeCountIncr != codeCountTotal) { 
                    addrmode = readMARIE(token, lineNum, offset);
                    addrmodeInstrSwap = true;   
                    codeCountIncr = codeCountIncr + 1;          
                } 
                
                else if (addrmodeInstrSwap == true && codeCountIncr != codeCountTotal) { 
                    instr = readInt(token, lineNum, offset);
                    opcode = instr / 1000;
                    operand = instr % 1000;
                    addrmodeInstrSwap = false;  
                    codeCountIncr = codeCountIncr + 1;           
                } 
                
                else if (codeCountIncr == codeCountTotal) { 

                    if (defCount > 16) { 
                        __parseerror(4, lineNum, offset);
                    }

                    baseAddress = baseAddress + codeCount;    
                    moduleNumPass1 = moduleNumPass1 + 1;
                    baseAdressMod[moduleNumPass1] = baseAddress; 
                           
                    defCountDone = true;
                    defCount = readInt(token, lineNum, offset); 

                    defCountTotal = 2 * defCount;            
                    defCountIncr = 0;

                    useCountDone = false; 
                    useCountIncr = 0; 
                    usecountTotal = 0;

                    codeCountDone = false;
                    codeCountIncr = 0;
                    codeCountTotal = 0;                      
                    
                    defSymAddrSwap = false;
                    addrmodeInstrSwap = false; 

                    defListSym.clear();
                    defListAddr.clear();
                                  
                    token = strtok(NULL, " \t");
                    continue;      
                }
                token = strtok(NULL, " \t");
                continue;               
            }  
        };
        delete [] lineChar;
        
        lineNum = lineNum + 1;
        if (line.empty()) { 
            offset = 0;
        }
        baseAdressMod[moduleNumPass1] = baseAddress;  
    }

    lineNum = lineNum - 1;  

    if (defCount > 16) { 
        __parseerror(4, lineNum, offset);
    }    
    if (usecountTotal > 16) { 
        __parseerror(5, lineNum, offset);
    }          

    if (codeCountFile > 512) { 
        __parseerror(6, lineNum, offset);
    }    

    if (defCountIncr != defCountTotal) { 
        if (defCountIncr == 0 && defCountTotal != 0) { 
            __parseerror(1, lineNum, offset+1);
        }

        else if (defCountIncr % 2 != 0 && defCountTotal != 0) { 
            __parseerror(0, lineNum, offset);
        }

        else if (defCountIncr % 2 == 0 && defCountTotal != 0) { 
            __parseerror(1, lineNum, offset+1);
        }
    }

    if (useCountIncr != usecountTotal) { 
        __parseerror(1, lineNum, offset);
    }

    if (codeCountIncr != codeCountTotal) { 
        if (codeCountIncr % 2 == 0) { 
            __parseerror(2, lineNum, offset+tokenLen);
        }

        else if (codeCountIncr % 2 != 0) { 
            __parseerror(0, lineNum, offset);
        }
    }
    
    for (string val: symbolTableWarnings) { 
        cout << val << endl;
    }

    cout << "Symbol Table" << endl;
    for (string val: symbolTableVec) { 
        cout << val << endl;
    }  

    cout << endl;
    inputFile.close();
    return symbolTable;
}   

void Parser2(string filename, map <string, string> symbolTable) {
    ifstream inputFile(filename);
    string line;

    int lineNum = 1;
    int offset = 1;
    int match = 0;
    int tokenLen = 0;

    bool defCountDone = false;
    int defCount = 0;
    int defCountTotal = 0;
    string defSym = "";
    int defAddr = 0;
    bool defSymAddrSwap = false;
    int defCountIncr = 0;

    bool useCountDone = false;
    int usecountTotal = 0;
    string useSym = "";
    int useCountIncr = 0;

    bool codeCountDone = false;
    int codeCount = 0;
    int codeCountTotal = 0; 
    char addrmode;
    int instr = 0;
    string instrUpdated = "";
    int codeCountIncr = 0;
    bool addrmodeInstrSwap = false;
    int baseAddress = 0;
    int opcode = 0; 
    int operand = 0;
    string operandBaseAddress;
    string rightError = "";
    string symbolTableAddr = "";
    string baseAddressToAdd = "";
    string rule3Error = "";

    vector<string> rule3Vector;
    vector<string> memoryMapVector;

    vector<string> defList;                                             // A vector of the symbols in definition lists across all modules 
    vector<string> useList;                                             // A vector of the symbols in use lists across all modules 
    vector<int> operandList;                                            // A vector of the operands in the instructions across all modules 
    
    map <int, string> useMapIndAllModules;                              // A hashmap which its keys are the indices of the symbols in the use list and the values are the symbols.

    map <int, string> useMapIndPerModule;                               // A hashmap which its keys are the indices of the symbols in the use list and the values are the symbols.

    map <int, map <int, string> > useNestedMapMod;                      // A hashmap which its keys are the module number of the use lists and 
                                                                        // the values are the array of symbols in the use lists in each

    map <int, vector<string> > useListMod;                              // A hashmap which its keys are the module number of the use lists and 
                                                                        // the values are the array of symbols in the use lists in each module.

    map <int, vector<string> > defListMod;                              // A hashmap which its keys are the module number of the def lists and 
                                                                        // the values are the array of symbols in the def lists in each module.

    map <int, vector<int> > eOperandMod;                                // A hashmap which its keys are the module number of the instructions and 
                                                                        // the values are the array of the operands of the E-instructions in each module.

    map <string, int> isAssociatedMap;                                  // A hashmap which its keys are the symbols of the use lists and the values are the 0 or 1. 
                                                                        // Note that the association is searched over all the modules.
                                                                        // (0 shows that the symbol is not associated with an E-instruction. 
                                                                        // 1 shows that the symbol is associated with an E-instruction.)

    map <pair<const int, const string>, int> isAssociatedMapPerModule;  // A hashmap which its keys are the symbols of the use lists and the values are the 0 or 1. 
                                                                        // Note that the association is searched per module.
                                                                        // (0 shows that the symbol is not associated with an E-instruction. 
                                                                        // 1 shows that the symbol is associated with an E-instruction.)

    while (getline(inputFile, line)) {
        int match = -1;
        char * lineChar = new char[line.length() + 1];
        strcpy(lineChar, line.c_str());
        char * token = strtok(lineChar, " \t");
        
        while (token != NULL) {
            match = line.find(token, match + 1);
            tokenLen = strlen(token);
            offset = match + 1;
            
            /////////////////////////////////////////////////////
            //////////////////// 1) DEF LIST ////////////////////
            /////////////////////////////////////////////////////

            if (defCountDone == false) {
                defCount = readInt(token, lineNum, offset); 
                defCountTotal = 2 * defCount;
                defCountDone = true;
                token = strtok(NULL, " \t");
                continue;
            }
            
            if (defCountDone == true && defCountIncr < defCountTotal) { 
                if (defCountTotal == 0) { 
                    defCountIncr = defCountIncr + 1;
                    token = strtok(NULL, " \t");
                    continue;
                }
                
                if (defSymAddrSwap == false) { 
                    defSym = readSymbol(token, lineNum, offset, tokenLen);
                    defSymAddrSwap = true;
                    defList.push_back(defSym);
                }

                else if (defSymAddrSwap == true) { 
                    defAddr = readInt(token, lineNum, offset);
                    defSymAddrSwap = false;
                }

                defCountIncr = defCountIncr + 1;
                token = strtok(NULL, " \t");
                continue;
            }
            
            /////////////////////////////////////////////////////
            //////////////////// 2) USE LIST ////////////////////
            /////////////////////////////////////////////////////

            if (useCountDone == false) { 
                usecountTotal = readInt(token, lineNum, offset);      
                useCountDone = true;
                token = strtok(NULL, " \t");
                continue;
            }

            if (useCountDone == true && useCountIncr < usecountTotal) { 
                useSym = readSymbol(token, lineNum, offset, tokenLen); 
                useList.push_back(useSym);  
                useMapIndAllModules[useCountIncr] = useSym;
                useMapIndPerModule[useCountIncr] = useSym;
                useCountIncr = useCountIncr + 1;   
                token = strtok(NULL, " \t");
                continue;
            }

            ///////////////////////////////////////////////////////
            /////////////////// 3) PROGRAM TEXT ///////////////////
            ///////////////////////////////////////////////////////

            if (codeCountDone == false) { 
                codeCount = readInt(token, lineNum, offset);
                codeCountTotal = codeCount * 2;
                codeCountDone = true;
                token = strtok(NULL, " \t");
                continue;
            };

            if (codeCountDone == true) { 

                if (addrmodeInstrSwap == false && codeCountIncr != codeCountTotal) { 
                    addrmode = readMARIE(token, lineNum, offset);
                    addrmodeInstrSwap = true;   
                    codeCountIncr = codeCountIncr + 1;          
                } 
                
                else if (addrmodeInstrSwap == true && codeCountIncr != codeCountTotal) { 
                    instr = readInt(token, lineNum, offset);
                    opcode = instr / 1000;
                    operand = instr % 1000;

                    if (opcode >= 10) {
                        rightError = " Error: Illegal opcode; treated as 9999";
                        instrUpdated = "9999" + rightError;
                        memoryMapVector.push_back(instrUpdated);
                    }
 
                    else if (addrmode == 'M') { 

                        if (operand > moduleNumPass1) { 
                            rightError = " Error: Illegal module operand ; treated as module=0";
                            instrUpdated = to_string(opcode) + "000" + rightError;
                            memoryMapVector.push_back(instrUpdated);              
                        }

                        else if (operand <= moduleNumPass2) {
                            baseAddressToAdd = to_string(baseAdressMod[operand]);
                            string numZeroOperand(3 - baseAddressToAdd.length(), '0');
                            instrUpdated = to_string(opcode) + numZeroOperand + baseAddressToAdd;
                            memoryMapVector.push_back(instrUpdated);
                        }    

                        else if (operand > moduleNumPass2) {
                            baseAddressToAdd = to_string(baseAdressMod[operand]);
                            string numZeroOperand(3 - baseAddressToAdd.length(), '0');
                            instrUpdated = to_string(opcode) + numZeroOperand + baseAddressToAdd;
                            memoryMapVector.push_back(instrUpdated);
                        }                                             
                    }

                    else if (addrmode == 'A') {  
                        if (operand >= 512) {
                            rightError = " Error: Absolute address exceeds machine size; zero used"; 
                            instrUpdated = to_string(opcode) + "000" + rightError; 
                            memoryMapVector.push_back(instrUpdated);
                        }
                        else if (operand <= 512) { 
                            string numZeroOperand(4 - to_string(instr).length(), '0');
                            instrUpdated = numZeroOperand + to_string(instr);
                            memoryMapVector.push_back(instrUpdated);                                                     
                        }
                    }

                    else if (addrmode == 'R') { 
                        if (operand >= codeCount) { 

                            rightError = " Error: Relative address exceeds module size; relative zero used";
                            string numZeroOperand(3 - to_string(baseAddress).length(), '0');
                            instrUpdated = to_string(opcode) + numZeroOperand + to_string(baseAddress) + rightError;
                            memoryMapVector.push_back(instrUpdated);                          
                        }

                        else if (operand < codeCount) { 
                            instrUpdated = to_string(operand + baseAddress);
                            string numZeroOperand(3 - instrUpdated.length(), '0');
                            memoryMapVector.push_back(to_string(opcode) + numZeroOperand + instrUpdated); 
                        } 
                    }  

                    else if (addrmode == 'I') { 
                        if (operand >= 900) { 
                            rightError = " Error: Illegal immediate operand; treated as 999";
                            instrUpdated = to_string(opcode) + "999" + rightError;
                            memoryMapVector.push_back(instrUpdated);                   
                        }
                        
                        else if (operand < 900) { 
                            string numZeroOperand(4 - to_string(instr).length(), '0');
                            instrUpdated = numZeroOperand + to_string(instr);
                            memoryMapVector.push_back(instrUpdated);                                
                        }  
                    }                    

                    else if (addrmode == 'E') {  
                        operandList.push_back(operand);
                        
                        for (pair<const int, const string> umpPair: useMapIndPerModule) { 
                                    
                            map <string, string> symbolTableIter(symbolTable);
                            
                            rule3Error = "";
                            if (symbolTableIter.count(umpPair.second) == 0) {
                                rule3Error = " Error: " + umpPair.second + " is not defined; zero used";
                            } 

                            if (umpPair.first == operand && codeCount != 0) { 
                                isAssociatedMap[umpPair.second] = 1;  
                                isAssociatedMapPerModule[umpPair] = 1;
                                symbolTableAddr = symbolTableIter[umpPair.second];                                  

                                string numZeroOperand(3 - symbolTableAddr.length(), '0');                            
                                instrUpdated = to_string(opcode) + numZeroOperand + symbolTableAddr + rule3Error;  
                                memoryMapVector.push_back(instrUpdated);                                                                               
                            }

                            else if (isAssociatedMap[umpPair.second] != 1) { 
                                isAssociatedMap[umpPair.second] = 0;
                                isAssociatedMapPerModule[umpPair] = 0;
                                rule3Error = "";     
                            }
                        }
                        
                        if (operand > usecountTotal-1) { 
                            rightError = " Error: External operand exceeds length of uselist; treated as relative=0";
                            string numZeroOperand(3 - to_string(baseAddress).length(), '0');  
                            instrUpdated = to_string(opcode) + numZeroOperand + to_string(baseAddress) + rightError;
                            memoryMapVector.push_back(instrUpdated);                                          
                        }
                    }

                    else if (strlen(token) == 4 && addrmode != 'E') { 
                        memoryMapVector.push_back(to_string(instr));                        
                    }

                    addrmodeInstrSwap = false;  
                    codeCountIncr = codeCountIncr + 1;              
                } 

                else if (codeCountIncr == codeCountTotal) { 

                    for (pair<int, string> umpPair: useMapIndPerModule) { 
                        if (isAssociatedMapPerModule[umpPair] == 0) {  
                            memoryMapVector.push_back("Warning: Module " + 
                                                      to_string(moduleNumPass2) + 
                                                      ":" + 
                                                      " " + 
                                                      "uselist" + 
                                                      "[" + 
                                                      to_string(umpPair.first) + 
                                                      "]" + 
                                                      "=" + 
                                                      umpPair.second + 
                                                      " " + 
                                                      "was not used");
                        }
                    }
                    
                    eOperandMod[moduleNumPass2] = operandList;
                    defListMod[moduleNumPass2] = defList;
                    useListMod[moduleNumPass2] = useList;    
                    useNestedMapMod[moduleNumPass2] = useMapIndPerModule;

                    useMapIndPerModule.clear();
                    isAssociatedMapPerModule.clear();
                    
                    moduleNumPass2 = moduleNumPass2 + 1;
                    baseAddress = baseAddress + codeCount;  
                    
                    defCount = readInt(token, lineNum, offset); 
                    defCountDone = true;
                    defCountTotal = 2 * defCount;            
                    defCountIncr = 0;

                    useCountDone = false; 
                    useCountIncr = 0; 
                    usecountTotal = 0;

                    codeCountDone = false;
                    codeCountIncr = 0;
                    codeCountTotal = 0;
                                    
                    defSymAddrSwap = false;
                    addrmodeInstrSwap = false;   

                    token = strtok(NULL, " \t");
                    continue;      
                }
                token = strtok(NULL, " \t");
                continue;               
            }
        };
        delete [] lineChar;
        lineNum = lineNum + 1;
        if (line.empty()) { 
            offset = 0;
        }

        eOperandMod[moduleNumPass2] = operandList;
        defListMod[moduleNumPass2] = defList;
        useListMod[moduleNumPass2] = useList;   
        useNestedMapMod[moduleNumPass2] = useMapIndPerModule;     
    }

    lineNum = lineNum - 1;

    for (pair<int, string> umpPair: useMapIndPerModule) { 
        if (isAssociatedMapPerModule[umpPair] == 0) {  
            memoryMapVector.push_back("Warning: Module " + 
                                      to_string(moduleNumPass2) + 
                                      ":" + 
                                      " " + 
                                      "uselist" + 
                                      "[" + 
                                      to_string(umpPair.first) + 
                                      "]" + 
                                      "=" + 
                                      umpPair.second + 
                                      " " + 
                                      "was not used");
        }
    }           

    for (auto const & dlPair: defListMod) {
        for (string symbol: dlPair.second) {  
            if (isAssociatedMap[symbol] == 0 && find(rule3Vector.begin(), rule3Vector.end(), symbol) == rule3Vector.end()) {
                memoryMapVector.push_back("Warning: Module " + 
                                          to_string(dlPair.first) + 
                                          ":" +
                                          " " +  
                                          symbol +
                                          " " +   
                                          "was defined but never used");  
                rule3Vector.push_back(symbol);
            }
        }
    }

    cout << "Memory Map" << endl;
    int mpInd = 0;
    for (string mp: memoryMapVector) { 
        size_t found1 = mp.find("Warning");
        size_t found2 = mp.find("uselist");

        if (found1 != string::npos && found2 == std::string::npos) { 
            cout << endl << mp << endl;
        }
        else if (found1 != string::npos && found2 != std::string::npos) { 
            cout << mp << endl;
        }
        else { 
            string numZeroInd(3 - to_string(mpInd).length(), '0');
            cout << numZeroInd 
                 << to_string(mpInd) 
                 << ": " 
                 << mp  
                 << endl;
            mpInd = mpInd + 1;
        }            
    }

    inputFile.close();
}   

int main(int argc, char* argv[]) { 
    map <string, string> symbolTable = Parser1(argv[1]);
    Parser2(argv[1], symbolTable);
    return 0;
}