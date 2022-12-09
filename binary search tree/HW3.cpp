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
        Node* search(const int& num, std::ofstream& o);
        void insert(const int& num, std::ofstream& o);
        void delet(Node* & root, const int& num, std::ofstream& o);
        void inorder(std::ofstream& o);
        void preorder(std::ofstream& o);
        void postorder(std::ofstream& o);
        void inorder(Node* current, std::ofstream& o);
        void preorder(Node* current, std::ofstream& o);
        void postorder(Node* current, std::ofstream& o);
        void level_order(std::ofstream& o);
        Node* root = 0;
};

void insert(std::ifstream& inFile, BST& tree, std::ofstream& o);
void delet(std::ifstream& inFile, BST& tree, std::ofstream& o);
void search(std::ifstream& inFile, BST& tree, std::ofstream& o);
void print(BST& tree, std::ofstream& o);


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
    outFile << "File name: " << fileName << std::endl;
    fileName.clear(); // free up space fileName

    BST tree;
    while(true){

        std::cout << "\n"; 
        std::cout << "(I)nsert a number." << std::endl; 
        std::cout << "(D)elete a number." << std::endl; 
        std::cout << "(S)earch a number." << std::endl; 
        std::cout << "(P)rint 4 kinds of orders." << std::endl; 
        std::cout << "(E)xit" << std::endl; 
        outFile << "\n";
        outFile << "(I)nsert a number." << std::endl;
        outFile << "(D)elete a number." << std::endl;
        outFile << "(S)earch a number." << std::endl;
        outFile << "(P)rint 4 kinds of orders." << std::endl;
        outFile << "(E)xit" << std::endl;

        char choice;
        inFile >> choice;

        switch(choice) {
            case 'e' :
            case 'E' : 
                inFile.close(); 
                outFile.close(); 
                std::cout << "\nExit\n";
                outFile << "\nExit\n";
                return 0;

            case 'i' : 
            case 'I' : insert(inFile, tree, outFile); break;

            case 'd' :
            case 'D' : delet(inFile, tree, outFile); break;

            case 's' : 
            case 'S' : search(inFile, tree, outFile); break;

            case 'p' :
            case 'P' : print(tree, outFile); break;

            default : std::cout << "\n\n !! (" << choice << ") " << "is not a operation. !!\n\n";
        }
    }
}

// search a specific number in BST, and return it's pointer
// if the BST does not contain the number then return NULL
Node* BST::search(const int& num, std::ofstream& outFile){
    for(Node* t = root; t; ){ 
        if(num == t->data) {
            std::cout << "Bingo! " << num <<" is found.\n";
            outFile << "Bingo! " << num <<" is found.\n";
            return t; // return the pointer
        }
        if(num < t->data) t = t->left;
        else t = t->right;   
    }
    std::cout << "Sorry! " << num << " is not found.\n";
    outFile << "Sorry! " << num << " is not found.\n";
    return 0; //return 0 if the BST is empty or didn't find the element;
};


// insert a new node to into BST
void BST::insert(const int& num, std::ofstream& outFile){
    
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
            outFile << "Error! Number " << num << " exists.\n";
            std::cout << "Error! Number " << num << " exists.\n";
            return ;
        }
    }
    outFile << "Number " << num << " is inserted.\n";
    std::cout << "Number " << num << " is inserted.\n";
};

void BST::delet(Node*& root, const int& num, std::ofstream& outFile){
    
    if(root == 0) {
        std::cout << "Number " << num << " is not existed.\n";
        outFile << "Number " << num << " is not existed.\n";
        return ;
    }
    
    if (num < root->data) delet(root->left, num, outFile);
    else if (num > root->data) delet(root->right, num, outFile);
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
            } while(current != 0);


            // Replace the root's key with the successor's key
            root->data = successor->data;
            // Delete the successor
            delet(root->right, successor->data, outFile);
        }
        if(num > 0){
            std::cout << "Number " << num <<" is deleted.\n";
            outFile << "Number " << num <<" is deleted.\n";
        }
    } 
};
void delet(std::ifstream& inFile, BST& tree, std::ofstream& outFile){

    std::cout << "\nDelete:\n";
    outFile << "\nDelete:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.delet(tree.root, num, outFile);
        } else break;
    }
    
}

void BST::inorder(std::ofstream& outFile){
    inorder(root, outFile);
    std::cout << std::endl;
    outFile << std::endl;
}
void BST::inorder(Node* current, std::ofstream& outFile){
    if(current){
        inorder(current->left, outFile);
        std::cout << current->data << " ";
        outFile << current->data << " ";
        inorder(current->right, outFile);
    }
}

void BST::preorder(std::ofstream& outFile){
    preorder(root, outFile);
    std::cout << std::endl;
    outFile << std::endl;
}
void BST::preorder(Node* current, std::ofstream& outFile){
    if(current){
        std::cout << current->data << " ";
        outFile << current->data << " ";
        preorder(current->left, outFile);
        preorder(current->right, outFile);
    }
}

void BST::postorder(std::ofstream& outFile){
    postorder(root, outFile);
    std::cout << std::endl;
    outFile << std::endl;
}
void BST::postorder(Node* current, std::ofstream& outFile){
    if(current){
        postorder(current->left, outFile);
        postorder(current->right, outFile);
        std::cout << current->data << " ";
        outFile << current->data << " ";
    }
}

void BST::level_order(std::ofstream& outFile){
    std::queue <Node *> q;
    Node* current = root;

    while(current){
        std::cout << current->data << " ";
        outFile << current->data << " ";
        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);
        current = q.front();
        if(current) q.pop();
    }
}

void insert(std::ifstream& inFile, BST& tree, std::ofstream& outFile){
    
    std::cout << "\nInsert:\n";
    outFile << "\nInsert:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.insert(num, outFile);
        } else break;
    }
    
}

void search(std::ifstream& inFile, BST& tree, std::ofstream& outFile){
    
    std::cout << "\nSearch:\n";
    outFile << "\nSearch:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.search(num, outFile);
        } else break;
    }
    
}

void print(BST& tree, std::ofstream& outFile) {

    std::cout << "\nPrint:\n";
    outFile << "\nPrint:\n";

    std::cout << "The tree in prefix order: ";
    outFile << "The tree in prefix order: ";

    tree.preorder(outFile);

    std::cout << "The tree in infix order: ";
    outFile << "The tree in infix order: ";

    tree.inorder(outFile);

    std::cout << "The tree in post order: ";
    outFile << "The tree in post order: ";

    tree.postorder(outFile);

    std::cout << "The tree in level order: ";
    outFile << "The tree in level order: ";

    tree.level_order(outFile);

    std::cout << std::endl;
    outFile << std::endl;
}