#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <queue>

//////////////////////////////// forward declarations & prototypes /////////////////////////////
class Node;
class BST;
void insert(std::ifstream& inFile, BST& tree, std::ofstream& o);
void delet(std::ifstream& inFile, BST& tree, std::ofstream& o);
void search(std::ifstream& inFile, BST& tree, std::ofstream& o);
void print(BST& tree, std::ofstream& o);


//////////// define the class of node of BST 
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

////// define the BST class ( with funstions required in this HW3 ) 
class BST {
    friend class Node;
    public : 
        Node* search(const int& num, std::ofstream& o);
        void insert(const int& num, std::ofstream& o);
        bool delet(Node* & root, const int& num, std::ofstream& o);
        void delet(const int& num, std::ofstream& o);
        void inorder(std::ofstream& o);
        void preorder(std::ofstream& o);
        void postorder(std::ofstream& o);
        void inorder(Node* current, std::ofstream& o);
        void preorder(Node* current, std::ofstream& o);
        void postorder(Node* current, std::ofstream& o);
        void level_order(std::ofstream& o);
    
    private:
        Node* root = 0;
};

/////////////////////////////////////////// main function /////////////////////////////////////////////
int main(){
    
    // File input|output
    std::cout << "Enter file name: ";
    std::string fileName;
    std::cin >> fileName;

    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(fileName);
    outFile.open("output.txt");

    // check if files opened successfully
    if(inFile.fail() || outFile.fail()){ 
        std::cout << "Fail to open file" << std::endl;
        return 1;
    }
    outFile << "File name: " << fileName << std::endl; // required ouput
    fileName.clear(); 


    // the main structure of this program
    BST tree;
    while(true){ // a infinite loop. will break only if the input is 'e'/'E'
        
        // required ouput to console & output.txt
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

        // input the choice and call the corresponding function
        char choice;
        inFile >> choice;
        switch(choice) { 
            // e & E for exit
            case 'e' :
            case 'E' : 
                inFile.close(); 
                outFile.close(); 
                std::cout << "\nExit\n";
                outFile << "\nExit\n";
                return 0;

            // i & I for insert
            case 'i' : 
            case 'I' : insert(inFile, tree, outFile); break;

            // d & D for delete
            case 'd' :
            case 'D' : delet(inFile, tree, outFile); break;

            // s & S for search
            case 's' : 
            case 'S' : search(inFile, tree, outFile); break;

            // p & P for print
            case 'p' :
            case 'P' : print(tree, outFile); break;

            // default situation is just for debugging
            default : std::cout << "\n\n !! (" << choice << ") " << "is not a operation. !!\n\n";
        }
    }
}

///////////////////////////////////////// Defining Functions ////////////////////////////////////////////

// function in BST (BST::search)
// search a specific number in BST, and return it's pointer
// if the BST does not contain the number then return 0(NULL)
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
// search function that handles the input|output, and call BST::search()
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


// function in BST (BST::insert)
// insert a new node to into BST
// implemented without recursion
void BST::insert(const int& num, std::ofstream& outFile){
    
    Node* current = root;

    if(root == 0)
        root = new Node(num);
    
    // infinite loop. current pointer will keep tracing down 
    while(current){ // when current hits 0, the while loop will stop
        
        // if num < the node, then go to left subtree
        if(num < current->data){ 
            if(current->left == 0){
                current->left = new Node(num);
                break;
            }
            current = current->left;

        // if num > the node, then go to right subtree
        } else if(num > current->data){ 
            if(current->right == 0){
                current->right = new Node(num);
                break;
            }
            current = current->right;
        
        // if num == the node, then tell the user it exists
        } else {
            outFile << "Error! Number " << num << " exists.\n";
            std::cout << "Error! Number " << num << " exists.\n";
            return ;
        }
    }

    // requried output
    outFile << "Number " << num << " is inserted.\n";
    std::cout << "Number " << num << " is inserted.\n";
};
// insert function that handles the input|output, and call the BST::insert
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

// function in BST (BST::delet)
// delete a node in BST
bool BST::delet(Node*& root, const int& num, std::ofstream& outFile){
    
    if(root == 0) {
        std::cout << "Number " << num << " is not existed.\n";
        outFile << "Number " << num << " is not existed.\n";
        return false;
    }
    
    if (num < root->data) return delet(root->left, num, outFile);
    else if (num > root->data) return delet(root->right, num, outFile);
    else {
        // If the node has no children, delete it and set the root to NULL
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        // If the node has one child, delete it and replace it with its child
        else if (root->left == NULL || root->right == NULL) {
            
            Node* child;
            if(!root->left) child = root->right;
            else if (!root->right) child = root->left;

            delete root;
            root = child;
        }
        // If the node has two children, find its successor and replace it with the successor
        else {
            Node *successor= root->right;;
             while(successor != 0 && successor->left != 0){
                successor = successor->left;
            }

            // assign successor's data to the root's data 
            root->data = successor->data;
            // Delete the successor
            delet(root->right, successor->data, outFile);
        }
        return true;
    } 
};

void BST::delet(const int& num, std::ofstream& outFile){
    if(delet(root, num, outFile)){
        std::cout << "Number " << num << " is deleted.\n";
        outFile << "Number " << num << " is deleted.\n";
    }
}

// delet fuction that handles the input|output, and call the BST::delete()
void delet(std::ifstream& inFile, BST& tree, std::ofstream& outFile){

    std::cout << "\nDelete:\n";
    outFile << "\nDelete:\n";
    
    int num;
    while(true){
        inFile >> num;
        if(num != -1) {
            tree.delet(num, outFile);
        } else break;
    }
    
}

// inorder traversal in BST
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

// preorder traversal in BST
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

// postorder traversal in BST
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

// level order traversal in BST
// implement with queue
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

// print function that output prefix, infix, postfix, level order
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
