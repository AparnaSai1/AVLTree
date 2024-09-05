
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include "AVL.h"

using namespace std;

// got this from TA breakdown video on the parsing slide for isalpha, etc
string verifyNext(const string& input) {
    for (char c : input) {
        if (!isalpha(c) && !isdigit(c) && !isspace(c)) {
            return "INVALID";
        }
    }
    return input;
}

int Conversion(const string& str) {
    int answer = 0;
    for (char c : str) {
        if (isdigit(c)) {
            answer = answer * 10 + (c - '0');
        } else {
            throw invalid_argument("Invalid input for number of commands.");
        }
    }
    return answer;
}

string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    if (start == string::npos || end == string::npos)
        return "";
    return str.substr(start, end - start + 1);
}

bool ifUFIDExists(const Node* node, const string& ufid) {
    if (node == nullptr) {
        return false;
    }

    if (node->ufid == ufid) {
        return true;
    }

    return ifUFIDExists(node->left, ufid) || ifUFIDExists(node->right, ufid);
}

bool processCommands(const string& command_name, AVLTree& t, istringstream& inputStream)
{
    bool success = true;

    if (command_name == "insert")
    {
        string line;
        getline(inputStream, line);

        // Find the position of the first and last double quotes
        size_t firstQuotePos = line.find('"');
        size_t lastQuotePos = line.rfind('"');

        // Extract the name between double quotes
        string name = line.substr(firstQuotePos + 1, lastQuotePos - firstQuotePos - 1);

        // Extract the ID after the last double quote
        string ID = line.substr(lastQuotePos + 1);

        // Trim leading and trailing whitespaces from ID
        ID = trim(ID);

        if (!name.empty() && !ID.empty())
            t.insert(name, ID);
        else
            cout << "unsuccessful" << endl;

    }


    else if (command_name == "remove")
    {
        string x;
        inputStream >> x; //reading straight in
        (verifyNext(x) != "INVALID") ? //create lambda function
        t.remove(x) :
        [](){ cout << "unsuccessful" << endl; }();
    }

    else if (command_name == "search") {
        string query;
        inputStream >> ws; // Skip leading whitespaces
        getline(inputStream, query, '\n'); // Read the entire line

        // Trim leading and trailing whitespaces
        query = trim(query);

        if (query.empty()) {
            cout << "unsuccessful" << endl;
        } else {
            // Check if the query is enclosed in double quotes
            if (query.front() == '"' && query.back() == '"') {
                // Remove the enclosing double quotes
                query = query.substr(1, query.length() - 2);
                if (verifyNext(query) != "INVALID") {
                    t.searchName(query);
                } else {
                    cout << "unsuccessful" << endl;
                }
            } else {
                if (verifyNext(query) != "INVALID") {
                    t.searchUFID(query);
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        }
    }

    else if (command_name == "printInorder") //kept this the same as it accomplished by just calling the method
    {
        t.printInorder();
        cout << endl;
    }
    else if (command_name == "printPreorder")
    {
        t.printPreorder();
        cout << endl;

    } else if (command_name == "printPostorder")
    {
        t.printPostorder();
        cout << endl;
    }
    else if (command_name == "printLevelCount")
    {
        t.printLevelCount();
    }
    else if (command_name == "removeInorder")
    {
        int order;
        if (inputStream >> order) {  // Try to extract an integer from the input stream
            t.removeInorder(order);
        } else {
            cout << "unsuccessful" << endl;
            // Clear the input stream in case it fails
            inputStream.clear();
            string placeholderr;
            getline(inputStream, placeholderr);  // for rest of the line
        }
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

int main() {
    AVLTree t;

    set<string> validCommands = {"insert", "remove", "search", "printInorder", "printPreorder", "printPostorder", "printLevelCount", "removeInorder"};
    string number_command_strings; // the following code sets up the vector and gets the number of commands
    getline(cin, number_command_strings);


    int numberOfCommands = Conversion(number_command_strings);
    vector<string> no_line;

    no_line.resize(numberOfCommands);
    while (numberOfCommands--) {
        string line;
        getline(cin, line);
        no_line[no_line.size() - numberOfCommands - 1] = line;
    }

    auto it = no_line.begin();
    while (it != no_line.end()) {
        istringstream inputStream(*it);
        string the_command;
        inputStream >> the_command;

        if (validCommands.find(the_command) == validCommands.end()) {
            cout << "unsuccessful" << endl;
            ++it;
            continue;
        }

        processCommands(the_command, t, inputStream);

        ++it;
    }

    return 0;
}
