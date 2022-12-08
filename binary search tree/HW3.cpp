#include <iostream>

class Node;
class BST;

class Node {
    friend class BST;
    private:
        int data;
        Node* left;
        Node* right;
};

class BST {
    public : 
        Node* search(const int& num);
        void insert();
        void delet();
        void inorder();
        void preorder();
        void postorder();
        void level_order();
        
    private :
        Node* first = 0;
};



int main(){
    
    BST tree;
    
    while(true){
        std::cout << "(I)nsert a number." << std::endl;
        std::cout << "(D)elete a number." << std::endl;
        std::cout << "(S)earch a number." << std::endl;
        std::cout << "(P)rint 4 kinds of orders." << std::endl;
        std::cout << "(E)xit" << std::endl;

        char choice;
        std::cin >> choice;

        switch(choice) {
            case 'e' :
            case 'E' : return 0;

            case 'i' :
            case 'I' : break;

            case 'd' :
            case 'D' : break;

            case 's' : 
            case 'S' : break;

            case 'p' :
            case 'P' : break;
            default : std::cout << "\n\n !! (" << choice << ") " << "is not a operation. !!\n\n";
        }

    }
}

Node* BST::search(const int& num){
  for()  
};