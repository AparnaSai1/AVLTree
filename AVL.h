#include <string>
#include <iostream>
#include <queue>
using namespace std;

//got structure from breakdown video and proceeded to declare everything to be implemented in AVL.cpp

struct Node {
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;
    Node() : name(""), ufid(""), left(nullptr), right(nullptr) {}
    Node(string n, string id) : name(n), ufid(id), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree{
private:
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rotateLeftRight(Node* node);
    int get_balance_factor(Node* node);
    Node* b_node(Node* node);
    int get_height(Node* node);
    Node* smallest_val(Node* node);
    Node* insertHelper(Node* node, string name, string ufid);
    Node* removeHelper(Node* node, string ufid);
    Node* removeInorderHelper(Node* node, int& the_count, int the_result);
    void searchUFIDHelper(Node* node, const string& ufid);
    void searchNameHelper(Node* node, const string& name, bool& found);
    void printInorder(Node* node, vector<string>& answer);
    void printPreorder(Node* node, vector<string>& answer);
    void printPostorder(Node* node, vector<string>& answer);

public:
    Node* root;
    AVLTree() : root() {}
    void insert(string name, string ufid);
    void remove(string ufid);
    void searchUFID(string ufid);
    void searchName(string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder (int n);

};
