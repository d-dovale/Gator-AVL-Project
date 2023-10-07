#pragma once
#include "regex"

string generateRandomString(int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int max_index = (sizeof(charset) - 1);
    std::string randomString;

    for (int i = 0; i < length; ++i) {
        randomString += charset[rand() % max_index];
    }

    return randomString;
}

bool checkName(string name){
    regex validNamePattern("^([a-zA-Z]+(\\s[a-zA-Z]+)*)$");
    return regex_match(name, validNamePattern);
}

bool checkUFID(string ufid){
    regex validUFIDPattern("^\\d{8}$");
    return regex_match(ufid, validUFIDPattern);
}

void handleUserCommands(AVLTree& tree){
    string command;
    string numberCommands;
    string name;
    string ufid;

    // Regex Patterns for the correct command input

    regex insertPattern(R"(insert\s+\"(.*?)\"\s+(\d+))");
    regex removePattern(R"(remove\s+(\d{8}))");
    regex searchIDPattern(R"(search\s+(\d{8}))");
    regex searchNamePattern(R"(search\s+\"(.*?)\")");
    regex printInOrderPattern("^printInorder$");
    regex printPreOrderPattern("^printPreorder$");
    regex printPostOrderPattern("^printPostorder$");
    regex printLevelCountPattern("^printLevelCount$");
    regex removeInOrderPattern(R"(^removeInorder\s+(-?\d+)$)");

    getline(cin, numberCommands);

    for(int i = 0; i < stoi(numberCommands); i++){
        getline(cin, command);
        smatch match_results;

        if (command.find("insert") == 0){
            if (regex_match(command, match_results, insertPattern)){
                name = match_results[1].str();
                ufid = match_results[2].str();

                if (checkName(name) && checkUFID(ufid)){
                    tree.Insert(name, ufid);
                }
                else{
                    cout << "unsuccessful" << endl;
                }
            }

            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if (command.find("remove") == 0){
            if(regex_match(command, match_results, removePattern)){
                ufid = match_results[1].str();
                if (checkUFID(ufid)){
                    tree.Remove(ufid);
                }

                else{
                    cout << "unsuccessful" << endl;
                }
            }

            else if (regex_match(command, match_results, removeInOrderPattern)) {
                int n = stoi(match_results[1].str());
                tree.RemoveInOrder(n);
            }

            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if (command.find("search") == 0){
            if(regex_match(command, match_results, searchIDPattern)){
                ufid = match_results[1].str();
                if (checkUFID(ufid)){
                    tree.SearchID(ufid);
                }

                else{
                    cout << "unsuccessful" << endl;
                }
            }

            else if (regex_match(command, match_results, searchNamePattern)){
                name = match_results[1].str();
                if (checkName(name)){
                    tree.SearchName(name);
                }

                else{
                    cout << "unsuccessful" << endl;
                }
            }

            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if (command.find("printInorder") == 0 && regex_match(command, match_results, printInOrderPattern)){
            tree.PrintInOrder();
        }

        else if (command.find("printPreorder") == 0 && regex_match(command, match_results, printPreOrderPattern)){
            tree.PrintPreOrder();
        }

        else if (command.find("printPostorder") == 0 && regex_match(command, match_results, printPostOrderPattern)){
            tree.PrintPostOrder();
        }

        else if (command.find("printLevelCount") == 0 && regex_match(command, match_results, printLevelCountPattern)){
            tree.PrintLevelCount();
        }
    }
}