#include <iostream>

// define the node structure
struct node {
  int data;
  node* left;
  node* right;
};

// create a new node
node* new_node(int data) {
  // allocate memory for the new node
  node* new_node = new node;

  // assign the data to the new node
  new_node->data = data;

  // set the left and right pointers to NULL
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

// insert a new node into the tree
void insert(node** root, int data) {
  // check if the tree is empty
  if (*root == NULL) {
    // create a new node
    *root = new_node(data);
    return;
  }

  // if the data is less than the root data, insert it into the left 
subtree
  if (data < (*root)->data) {
    insert(&(*root)->left, data);
  }
  // if the data is greater than or equal to the root data, insert it into 
the right subtree
  else {
    insert(&(*root)->right, data);
  }
}

// search for a node in the tree
node* search(node* root, int data) {
  // check if the tree is empty
  if (root == NULL) {
    return NULL;
  }

  // check if the data is at the root
  if (root->data == data) {
    return root;
  }

  // if the data is less than the root data, search the left subtree
  if (data < root->data) {
    return search(root->left, data);
  }
  // if the data is greater than or equal to the root data, search the 
right subtree
  else {
    return search(root->right, data);
  }
}

// main function
int main() {
  // create an empty tree
  node* root = NULL;

  // insert some data into the tree
  insert(&root, 5);
  insert(&root, 2);
  insert(&root, 7);
  insert(&root, 1);
  insert(&root, 3);
  insert(&root, 6);
  insert(&root, 8);

  // search for a node with data = 7
  node* node7 = search(root, 7);
  if (node7 != NULL) {
    std::cout << "Found node with data = 7" << std::endl;
  }
  else {
    std::cout << "Could not find node with data = 7" << std::endl;
  }

  // search for a node with data = 10
  node* node10 = search(root, 10);
  if (node10 != NULL) {
    std::cout << "Found node with data = 10" << std::endl;
  }
  else {
    std::cout << "Could not find node with data = 10" << std::endl;
  }

  return 0;
}

