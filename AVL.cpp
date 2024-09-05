
#include <string>
#include <iostream>
#include <queue>
#include "AVL.h"
#include <vector>
using namespace std;

//rotating code used from class 

Node* AVLTree::rotateLeft(Node* node) {
    Node* right_temp = node->right;
    node->right = right_temp->left;
    right_temp->left = node;
    return right_temp;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* left_temp = node->left;
    node->left = left_temp->right;
    left_temp->right = node;
    return left_temp;
}

Node* AVLTree::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node* AVLTree::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

int AVLTree::get_balance_factor(Node* node) {
    if (node == nullptr)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

int AVLTree::get_height(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        int left_height = get_height(node->left);
        int right_height = get_height(node->right);

        // Return the maximum of the heights of left and right subtrees, plus 1 for the current node
        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}

Node* AVLTree::b_node(Node* node)
{
    // Check if the node is null
    if (node == nullptr) {
        return nullptr;
    }

    // Calculate the balance factor
    int balance_factor = get_balance_factor(node);

    // If balance factor is greater than 1, the tree is left-heavy
    if (balance_factor > 1) {
        // Check the balance factor of the left child
        int left_balance = get_balance_factor(node->left);
        if (left_balance >= 0) {
            return rotateRight(node);
        }
        else {
            return rotateLeftRight(node);
        }
    }
    else if (balance_factor < -1) {
        int right_balance = get_balance_factor(node->right);
        if (right_balance <= 0) {
            return rotateLeft(node);
        }
        else {
            return rotateRightLeft(node);
        }
    }

    return node;
}


Node* AVLTree::smallest_val(Node *node)
{
    if (node == nullptr)
        return nullptr;

    while (node->left != nullptr)
        node = node->left;

    return node;

}

Node* AVLTree::insertHelper(Node* node, string name, string ufid)
{
    int answer = 0;
    for (char c : ufid) {
        if (isdigit(c)) {
            answer = answer * 10 + (c - '0');
        } else {
            cout << "unsuccessful" << endl;
            return node;
        }
    }

    if (node == nullptr) {
        cout << "successful" << endl;
        return new Node(name, ufid);
    }

    // Compare the GatorID of the current node with the given GatorID
    int nodeKey = 0;
    for (char c : node->ufid) {
        if (isdigit(c)) {
            nodeKey = nodeKey * 10 + (c - '0');
        } else {
            cout << "unsuccessful" << endl;
            return node;
        }
    }

    if (answer < nodeKey) {
        // If the given GatorID is less than the current node's GatorID, insert into the left subtree
        node->left = insertHelper(node->left, name, ufid);
    } else if (answer > nodeKey) {
        // If the given GatorID is greater than the current node's GatorID, insert into the right subtree
        node->right = insertHelper(node->right, name, ufid);
    } else {
        // If the given GatorID is equal to the current node's GatorID, print unsuccessful
        cout << "unsuccessful" << endl;
        return node;
    }

    // After insertion, balance the tree and update the height of the current node
    node = b_node(node);
    node->height = get_height(node);

    return node;
}
//
//void AVLTree::insert(string name, string ID) {
//    // Check if the name contains double inverted commas
//    if (name.front() != '"' || name.back() != '"') {
//        cout << "unsuccessful" << endl;
//        return;
//    }
//
//    // Check if ID is unique
//    if (searchUFID(ID)) {
//        cout << "unsuccessful" << endl;
//        return;
//    }
//
//    // Remove the double inverted commas from the name
//    name = name.substr(1, name.length() - 2);
//
//    // Split the ID into two parts
//    string part1 = ID.substr(0, ID.length() / 2);
//    string part2 = ID.substr(ID.length() / 2);
//
//    // Convert parts to integers
//    int num1 = stoi(part1);
//    int num2 = stoi(part2);
//
//    // Perform some arbitrary calculation
//    int sum = num1 + num2;
//    int product = num1 * num2;
//
//    // Insert the node into the tree
//    if (sum > product) {
//        root = insertHelper(root, name, part1);
//    } else {
//        root = insertHelper(root, name, part2);
//    }
//
//    cout << "successful" << endl;
//}




void AVLTree::insert(string name, string ufid)
{
    this->root = insertHelper(this->root, name, ufid);
}

Node* AVLTree::removeHelper(Node* node, string ufid) {
    int answer = 0;
    for (char c : ufid) {
        if (isdigit(c)) {
            answer = answer * 10 + (c - '0');
        } else {
            cout << "unsuccessful" << endl;
            return node;
        }
    }

    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return node;
    }

    int nodeUfid = 0;
    for (char c : node->ufid) {
        if (isdigit(c)) {
            nodeUfid = nodeUfid * 10 + (c - '0');
        } else {
            cout << "unsuccessful" << endl;
            return node;
        }
    }

    if (nodeUfid < answer)
        node->right = removeHelper(node->right, ufid);
    else if (nodeUfid > answer)
        node->left = removeHelper(node->left, ufid);
    else { // value matches
        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            cout << "successful" << endl;
            return temp;
        } else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            cout << "successful" << endl;
            return temp;
        } else {
            Node* temp = smallest_val(node->right);
            node->ufid = temp->ufid;
            node->name = temp->name;
            node->right = removeHelper(node->right, temp->ufid);
        }
    }

    node->height = get_height(node);

    return node;
}


void AVLTree::remove(string ufid)
{
    this->root = removeHelper(this->root, ufid);
}

// troubleshooted method after running into issues

Node* AVLTree::removeInorderHelper(Node* node, int& the_count, int the_result) {
    if (node == nullptr) {
        return nullptr;
    }
    Node* leftResult = removeInorderHelper(node->left, the_count, the_result); //this deals wth the left
    if (the_count == the_result) {
        Node* removedNode = removeHelper(node, node->ufid); //delete the node
        ++the_count; // increment count after removing the node
        return removedNode;
    }
    // Increment count before processing the right subtree
    ++the_count;
    Node* rightResult = removeInorderHelper(node->right, the_count, the_result); //deal with the right
    // Update the left and right children of the current node
    node->left = leftResult;
    node->right = rightResult;
    return node;
}


//void AVLTree::removeInorder(int n) {
//    vector<string> ufids;
//    inorderTraversal(root, ufids);
//
//    if (n >= ufids.size()) {
//        cout << "unsuccessful" << endl;
//        return;
//    }
//
//    // Remove the UFID from the tree
//    string targetUFID = ufids[n];
//    root = removeHelper(root, targetUFID);
//
//    cout << "successful" << endl;
//}
//
//void AVLTree::inorderTraversal(Node* node, vector<string>& ufids) {
//    if (node == nullptr) {
//        return;
//    }
//    inorderTraversal(node->left, ufids);
//    ufids.push_back(node->ufid);
//    inorderTraversal(node->right, ufids);
//}


void AVLTree::removeInorder(int n)
{
    int x = 0;
    root = removeInorderHelper(root, x, n);
}

void AVLTree::searchUFIDHelper(Node* node, const string& ufid) {
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }

    bool found = true;
    for (size_t i = 0; i < ufid.length(); ++i) {
        if (!isdigit(ufid[i])) {
            found = false;
            break;
        }
    }

    if (!found) {
        cout << "unsuccessful" << endl;
        return;
    }

    int answer = stoi(ufid);
    while (node != nullptr) {
        int nodeKey = stoi(node->ufid);
        if (nodeKey == answer) {
            cout << node->name << endl;
            return;
        } else if (nodeKey < answer) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    cout << "unsuccessful" << endl;
}


void AVLTree::searchNameHelper(Node* node, const string& name, bool& found) {
    if (node == nullptr)
        return;

    // Check if the current node's name matches the target name
    bool nameMatch = true;
    for (size_t i = 0; i < name.size(); ++i) {
        if (node->name.size() <= i || node->name[i] != name[i]) {
            nameMatch = false;
            break;
        }
    }

    if (nameMatch) {
        cout << node->ufid << endl;
        found = true;
    }

    // Continue traversing the left and right subtrees
    searchNameHelper(node->left, name, found);
    searchNameHelper(node->right, name, found);
}

void AVLTree::searchUFID(string ufid) {
    searchUFIDHelper(this->root, ufid);
}

void AVLTree::searchName(string name) {
    bool found = false;
    searchNameHelper(this->root, name, found);
    if (!found) {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::printInorder() {
    vector<string> answer; // Vector to store traversal results
    printInorder(root, answer);
    bool the_node = true;
    for (const auto& name : answer) {
        if (!the_node)
            cout << ", ";
        else
            the_node = false;
        cout << name;
    }
}

void AVLTree::printInorder(Node* node, vector<string>& answer) {
    if (node == nullptr)
        return;

    printInorder(node->left, answer);

    answer.push_back(node->name); // Store node's name in the result vector

    printInorder(node->right, answer);
}


void AVLTree::printPreorder(Node* node, vector<string>& answer) {
    if (node == nullptr)
        return;

    answer.push_back(node->name); // Store node's name in the result vector

    printPreorder(node->left, answer);
    printPreorder(node->right, answer);
}

void AVLTree::printPreorder() {
    vector<string> answer; // Vector to store traversal results
    printPreorder(root, answer);
    bool the_node = true;
    for (const auto& name : answer) {
        if (!the_node)
            cout << ", ";
        else
            the_node = false;
        cout << name;
    }
}

void AVLTree::printPostorder(Node* node, vector<string>& answer) {
    if (node == nullptr)
        return;

    printPostorder(node->left, answer);
    printPostorder(node->right, answer);
    answer.push_back(node->name); // Store node's name in the result vector
}

void AVLTree::printPostorder() {
    vector<string> answer; // Vector to store traversal results
    printPostorder(root, answer);
    bool the_node = true;
    for (auto it = answer.begin(); it != answer.end(); ++it) {
        if (!the_node)
            cout << ", ";
        else
            the_node = false;
        cout << *it;
    }
}

void AVLTree::printLevelCount() {
    if (this->root == nullptr) {
        cout << "0" << endl;
        return;
    }

    queue<Node*> nodesQueue;
    nodesQueue.push(this->root);

    int levelCount = 0;

    while (!nodesQueue.empty()) {
        int levelSize = nodesQueue.size();

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            Node* currentNode = nodesQueue.front();
            nodesQueue.pop();

            // Enqueue the left and right children of the current node
            if (currentNode->left != nullptr)
                nodesQueue.push(currentNode->left);
            if (currentNode->right != nullptr)
                nodesQueue.push(currentNode->right);
        }

        // Increment the level count after processing all nodes at the current level
        ++levelCount;
    }

    cout << levelCount << endl;
}
