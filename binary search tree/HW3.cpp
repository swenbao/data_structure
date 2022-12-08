#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


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
        void delet(const int& num);
        void inorder();
        void preorder();
        void postorder();
        void inorder(Node* current);
        void preorder(Node* current);
        void postorder(Node* current);
        void level_order();
        
    private :
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
            case 'E' : std::cout << "Exit\n"; return 0;

            case 'i' : 
            case 'I' : insert(inFile, tree); break;

            case 'd' :
            case 'D' : delet(inFile, tree); break;

            case 's' : 
            case 'S' : search(inFile, tree); break;

            case 'p' :
            case 'P' : print(tree); break;
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
    Node* t = root;
    while(t){ // when t hits 0, the while loop will stop
        if(t->data == num){ // the node already exists
            std::cout << "Error! Number " << num << " exists.\n";
            return;
        } else if(num < t->data){ 
            t = t->left;
        } else { // if (num > t->data)
            t = t->right;
        }
    }
    t = new Node(num); // insert
    std::cout << "Number " << num << " is inserted.\n";
};

void BST::delet(const int& num){
    Node* t = root;
    Node* previous;
    bool from_left;

    while(t){ 
        if(num == t->data) break;
        if(num < t->data){
            previous = t;
            t = t->left;
            from_left = true;
        } else {
            previous = t;
            t = t->right;
            from_left = false;
        }
    }

    if(t == 0){
        std::cout << "Number " << num << " is not existed.\n";
    } else {
        if(t->left == 0 && t->right == 0){
            std::cout << "Number " << num << " is deleted.\n";
            free(t);
            if(from_left) previous->left = 0;
            else previous->right = 0;
        } else if(t->left == 0 && t->right != 0){
            std::cout << "Number " << num << " is deleted.\n";
            free(t->right);
            t->right = 0;
        } else if(t->left != 0 && t->right == 0){
            std::cout << "Number " << num << " is deleted.\n";
            free(t->left);
            t->left = 0;
        } else {
            std::cout << "Number " << num << " is deleted.\n";
            Node* del_node = t;
            t = t->right;
            do {
                previous = t;
                t = t->left;
            } while(t->left);
            del_node->data = t->data;
            free(t);
            previous->left = 0;
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
        inorder(current->left);
        inorder(current->right);
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

void BST::level_order(){}

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
            tree.delet(num);
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
    std::cout << std::endl;
}