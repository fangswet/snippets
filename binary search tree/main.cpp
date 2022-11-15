#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class BST
{
    struct Node
    {
        int value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        
        Node(int v) : value(v) {}
        Node(Node* p, int v) : value(v), parent(p) {}
        
        static void print(const string& prefix, const Node* node, bool left)
        {
            if (!node) return;
            
            cout << prefix;
            cout << (left ? "├──" : "└──");
            cout << node->value << endl;
            
            auto p = prefix + (left ? "│   " : "    ");
            print(p, node->left, true);
            print(p, node->right, false);
        }
        
        static void insert(Node* node, int value)
        {
            if (node->value < value)
            {
                if (!node->right) node->right = new Node(node, value);
                else insert(node->right, value);
            }
            else
            {
                if (!node->left) node->left = new Node(node, value);
                else insert(node->left, value);
            }
        }
        
        static int height(const Node* node)
        {
            if (!node) return 0;
            
            auto r = height(node->left);
            auto l = height(node->right);
            
            return r < l ? ++l : ++r;
        }
        
        static void postorder(const Node* node)
        {
            if (!node) return;
            
            postorder(node->left);
            postorder(node->right);
            cout << node->value << ' ';
        }
        
        static void inorder(const Node* node)
        {
            if (!node) return;
            
            inorder(node->left);
            cout << node->value << ' ';
            inorder(node->right);
        }
        
        static void preorder(const Node* node)
        {
            if (!node) return;
            
            cout << node->value << ' ';
            preorder(node->left);
            preorder(node->right);
        }
        
        static void onlevel(const Node* node, int level)
        {
            if (!node) return;
            if (level == 1) cout << node->value << ' ';
            else if (level > 1)
            {
                onlevel(node->left, level - 1);
                onlevel(node->right, level - 1);
            }
        }
        
        static void levelorder(const Node* node)
        {
            for (int i = 1; i <= height(node); i++) onlevel(node, i);
        }
        
        static Node* min(Node* node)
        {
            if (!node) return node;
            
            while (node->left) node = node->left;
            
            return node;
        }
        
        static Node* max(Node* node)
        {
            if (!node) return node;
            
            while (node->right) node = node->right;
            
            return node;
        }
        
        static Node* find(Node* node, int value)
        {
            while (node && node->value != value)
            {
                node = node->value < value ? node->right : node->left;
            }
            
            return node;
        }
        
        Node* successor()
        {
            if (right) return min(right);
            
            auto node = this;
            auto p = parent;
            while (p && node == p->right)
            {
                node = p;
                p = p->parent;
            }
            
            return p;
        }
    };
    
    Node* root = nullptr;
    
public:   
    void insert(int value)
    {
        if (!root) root = new Node(value);
        else Node::insert(root, value);
    }
    
    int height() { return Node::height(root); }
    
    void postorder()
    {
        Node::postorder(root);
        cout << endl;
    }
    
    void inorder()
    {
        Node::inorder(root);
        cout << endl;
    }
    
    void preorder()
    {
        Node::preorder(root);
        cout << endl;
    }
    
    void levelorder()
    {
        Node::levelorder(root);
        cout << endl;
    }
    
    Node* min() { return Node::min(root); }
    
    Node* max() { return Node::max(root); }
    
    void print() { Node::print("", root, false); }
    
    Node* find(int value) { return Node::find(root, value); }
};

int main()
{
    BST bst;
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> numbers;
    
    for (string token; getline(iss, token, ' ');)
    {
        auto i = stoi(token);
        if (find(numbers.begin(), numbers.end(), i) == numbers.end())
        {
            bst.insert(i);
            numbers.push_back(i);
        }
        else break;
    }
    
    cout << bst.height() << endl;
    bst.preorder();
    bst.inorder();
    bst.postorder();
    bst.levelorder();
    bst.print();

    while (getline(cin, line))
    {
        auto n = bst.find(stoi(line));
        if (!n) break;
        auto s = n->successor();
        if (s) cout << s->value << endl;
    }

    return 0;
}

