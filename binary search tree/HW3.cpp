#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <queue>


class Node;
class BST;

class Node {
    friend class BST;
    public:
        Node(int a){
            data = a;
            left = right = 0;
        };
    private:
        int data;
        Node* left;
        Node* right;
};

class BST {
    friend class Node;
    public : 
        Node* search(const int& num);
        void insert(const int& num);
        void delet(Node* & root, const int& num);
        void inorder();
        void preorder();
        void postorder();
        void inorder(Node* current);
        void preorder(Node* current);
        void postorder(Node* current);
        void level_order();
        Node* root = 0;
};

void insert(std::ifstream& inFile, BST& tree);
void delet(std::ifstream& inFile, BST& tree);
void search(std::ifstream& inFile, BST& tree);
void print(BST& tree);


int main(){
    
    // File input
    std::cout << "Enter file name:";
    std::string fileName;
    std::cin >> fileName;

    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(fileName);
    outFile.open("output.txt");
    if(inFile.fail() || outFile.fail()){
        std::cout << "Fail to open file" << std::endl;
        return 1;
    }
    fileName.clear(); // free up space fileName

    BST tree;
    while(true){
        std::cout << "\n";
        std::cout << "(I)nsert a number." << std::endl;
        std::cout << "(D)elete a number." << std::endl;
        std::cout << "(S)earch a number." << std::endl;
        std::cout << "(P)rint 4 kinds of orders." << std::endl;
        std::cout << "(E)xit" << std::endl;

        char choice;
        inFile >> choice;

        switch(choice) {
            case 'e' :
            case 'E' : inFile.close(); outFile.close(); break; std::cout << "Exit\n"; return 0;

            case 'i' : 
            case 'I' : insert(inFile, tree); break;

            case 'd' :
            case 'D' : delet(inFile, tree); break;

            case 's' : 
            case 'S' : search(inFile, tree); break;

            case 'p' :
            case 'P' : print(tree); std::cout << "2"; break;

            default : std::cout << "\n\n !! (" << choice << ") " << "is not a operation. !!\n\n";
        }

    }
}


// search a specific number in BST, and return it's pointer
// if the BST does not contain the number then return NULL
Node* BST::search(const int& num){
    for(Node* t = root; t; ){ 
        if(num == t->data) {
            std::cout << "Bingo! " << num <<" is found.\n";
            return t; // return the pointer
        }
        if(num < t->data) t = t->left;
        else t = t->right;   
    }
    std::cout << "Sorry! " << num << " is not found.\n";
    return 0; //return 0 if the BST is empty or didn't find the element;
};


// insert a new node to into BST
void BST::insert(const int& num){
    
    Node* current = root;

    if(root == 0)
        root = new Node(num);
    
    while(current){ // when t hits 0, the while loop will stop
        if(num < current->data){ 
            if(current->left == 0){
                current->left = new Node(num);
                break;
            }
            current = current->left;
        } else if(num > current->data){ 
            if(current->right == 0){
                current->right = new Node(num);
                break;
            }
            current = current->right;
        } else { // if (num == current->data)
            std::cout << "Error! Number " << num << " exists.\n";
            return ;
        }
    }
    std::cout << "Number " << num << " is inserted.\n";
};

void BST::delet(Node* & root, const int& num){
    
    if(root == 0) {
        std::cout << "Number " << num << " is not existed.\n";
        return ;
    }
    
    if (num < root->data) delet(root->left, num);
    else if (num > root->data) delet(root->right, num);
    else {
        // If the node has no children, simply delete it by setting the root to NULL
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        // If the node has one child, delete it by replacing it with its child
        else if (root->left == NULL || root->right == NULL) {
            
            Node* child;
            if(root->left == 0) child = root->right;
            else if (root->right == 0) child = root->left;

            delete root;
            root = child;
        }
        // If the node has two children, find its successor and replace it with the successor
        else {
            Node* current = root->right;
            Node *successor;
            do{
                successor = current;
                current = current->left;
            }while(current != 0);


            // Replace the root's key with the successor's key
            root->data = successor->data;
            // Delete the successor
            delet(root->right, successor->data);
        }
    }
};

void BST::inorder(){
    inorder(root);
    std::cout << std::endl;
}
void BST::inorder(Node* current){
    if(current){
        inorder(current->left);
        std::cout << current->data << " ";
        inorder(current->right);
    }
}

void BST::preorder(){
    preorder(root);
    std::cout << std::endl;
}
void BST::preorder(Node* current){
    if(current){
        std::cout << current->data << " ";
        preorder(current->left);
        preorder(current->right);
    }
}

void BST::postorder(){
    postorder(root);
    std::cout << std::endl;
}
void BST::postorder(Node* current){
    if(current){
        inorder(current->left);
        inorder(current->right);
        std::cout << current->data << " ";
    }
}

void BST::level_order(){
    std::queue <Node *> q;
    Node* current = root;
    while(current){
        std::cout << current->data << " ";
        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);
        current = q.front();
        q.pop();
    }
    std::cout << "啊啊\n";
}

void insert(std::ifstream& inFile, BST& tree){
    
    std::cout << "\nInsert:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.insert(num);
        } else break;
    }
    
}

void delet(std::ifstream& inFile, BST& tree){

    std::cout << "\nDelete:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.delet(tree.root, num);
        } else break;
    }
    
}

void search(std::ifstream& inFile, BST& tree){
    
    std::cout << "\nSearch:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.search(num);
        } else break;
    }
    
}

void print(BST& tree){

    std::cout << "\nPrint:\n";    
    std::cout << "The tree in prefix order: ";
    tree.preorder();
    std::cout << "The tree in infix order: ";
    tree.inorder();
    std::cout << "The tree in post order: ";
    tree.postorder();
    std::cout << "The tree in level order: ";
    tree.level_order();
    std::cout << "ㄏㄟ" << std::endl;

}