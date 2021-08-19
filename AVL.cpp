#include "AVL.h"
#include <memory>
#include <iostream>

using namespace std;

//Constructor
AVL::AVL() {
    shared_ptr<avl_node> root_ptr(NULL);
}

//Deconstructor -- not used as I use shared pointers
AVL::~AVL() {
}

//Initializes an AVL node.
shared_ptr<avl_node> AVL::InitNode(int protocol, int source, int dest) {
    shared_ptr<avl_node> ret(new avl_node);
    ret->source = source;
    ret->dest = dest;
    ret->protocol = protocol;
    ret->left = shared_ptr<avl_node>(NULL);
    ret->right = shared_ptr<avl_node>(NULL);
    ret->parent = shared_ptr<avl_node>(NULL);
    ret->count = 1;
    return ret;
}

//Checks to see if AVL tree contains a source IP address.
bool AVL::Contains(int data) {
  shared_ptr<avl_node> curr_ptr(root_ptr);

  while (curr_ptr != NULL) {
    if (curr_ptr->source == data) {
      return true;
    }
    if (curr_ptr->source < data) {
      curr_ptr = curr_ptr->right;
    } else {
      curr_ptr = curr_ptr->left;
    }
  }

  return false;
}

//Inserts node into AVL_tree
void AVL::InsertNode(shared_ptr<avl_node> new_node) {
    shared_ptr<avl_node> curr_node(root_ptr);
    int packets = 0;
    if (new_node == NULL) {
        return;
    }
    if (root_ptr == NULL) {
        SetRoot(new_node);
        Print(root_ptr);
    } else {
        while (curr_node != NULL) {
        if (curr_node->source < new_node->source) {
            if (curr_node->right != NULL) {
            curr_node = curr_node->right;
            } else {
            new_node->parent = curr_node;
            curr_node->right = new_node;
            cout << "Root: " << (unsigned int)root_ptr->source << endl;
            packets = PacketsRecvd(root_ptr, packets);
            cout << "Unique IP Addresses: " << packets << endl;
            //Print(root_ptr);
            break;
            }
        } else if (curr_node->source > new_node->source) {
            if (curr_node->left != NULL) {
            curr_node = curr_node->left;
            } else {
            new_node->parent = curr_node;
            curr_node->left = new_node;
            cout << "Root: " << (unsigned int)root_ptr->source << endl;
            packets = PacketsRecvd(root_ptr, packets);
            cout << "Unique IP Addresses: " << packets << endl;
            //Print(root_ptr);
            break;
            }
        } else {
            if (curr_node->source == new_node->source){
                curr_node->count++;
                break;
            }
        }
        }
    }
    //TraverseTreeUp(new_node->parent);
    BalanceTree(root_ptr);
}

//Returns the height of a subtree
int AVL::GetHeight(shared_ptr<avl_node> node) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (node == NULL) {
        return -1;
    }
    leftHeight = GetHeight(node->left);
    rightHeight = GetHeight(node->right);
    return 1 + max(leftHeight, rightHeight);
}

//Gets the height difference between left and right subtrees
int AVL::HeightDifference(shared_ptr<avl_node> node) {
    int left = 0;
    int right = 0;
    left = GetHeight(node->left);
    right = GetHeight(node->right);
    return left - right;
}

//Determines the total number of unique source IP addresses
int AVL::PacketsRecvd(shared_ptr<avl_node> node, int count) {
    if (node == NULL) {
        return count;
    }
    count = PacketsRecvd(node->left, count);
    count = 1 + PacketsRecvd(node->right, count);
    return count;
}

//Prints IP address and packets sent from ip address for each node
void AVL::Print(shared_ptr<avl_node> node) {
    if (node == NULL) {
        return;
    }
    Print(node->left);
    cout << "IP Address: " << (unsigned int)node->source;
    cout << " Packet Count: " << node->count << endl;
    Print(node->right);
}

//Traverses the tree from the node up to the root pointer
//Balances each node
void AVL::TraverseTreeUp(shared_ptr<avl_node> node) {
    if (node == NULL) {
        return;
    }
    BalanceTree(node);
    if (node->parent){
        TraverseTreeUp(node->parent);
    }
}

//Test to ensure AVL_tree is set up properly.
void AVL::TestTraverseTreeInorder(shared_ptr<avl_node> node){
    int height;
    int rootheight;
    rootheight = GetHeight(root_ptr);
    if (node == NULL) {
        return;
    }
    TestTraverseTreeInorder(node->left);
    height = 0;
    height = HeightDifference(node);
    if (node == root_ptr){
        cout << "Root Height: " << rootheight << " ----- ";
    }
    cout << "Node: " << (unsigned int)node->source;
    cout << "--- Height Balance: " << height << endl;
    TestTraverseTreeInorder(node->right);
}

//Balance each subtree by height
void AVL::BalanceTree(shared_ptr<avl_node> node) {
    if (node == NULL) {
        return;
    }
    int height = 0;
    height = HeightDifference(node);
    //cout <<"Node: " << node->source << " Height: " << height << endl;
    if (height < -1) {
        RotateLeft(node->right);
    } else if (height > 1) {
        RotateRight(node->left);
    } else {
        return;
    }
}

//Rotate node left
void AVL::RotateLeft(shared_ptr<avl_node> node){
    shared_ptr<avl_node> grandparent(new avl_node);
    shared_ptr<avl_node> temp1(new avl_node);
    shared_ptr<avl_node> temp2(new avl_node);
    shared_ptr<avl_node> curr(node);
    shared_ptr<avl_node> leftchild(node->left);
    shared_ptr<avl_node> rightchild(node->right);
    shared_ptr<avl_node> par(node->parent);

    if (node == NULL || node->parent == NULL) {
        return;
    }

    if (node->parent->parent){
        grandparent = node->parent->parent;
    } else {
        grandparent = NULL;
    }
    if (par == root_ptr){
        SetRoot(node);
    }
    if (leftchild){
        node->left = NULL;
        par->right = NULL;
        par->parent = leftchild;
        temp1 = leftchild->left;
        leftchild->left = par;
        temp2 = leftchild->right;
        leftchild->right = node;
        node->parent = leftchild;
        leftchild->parent = grandparent;
        if (node == root_ptr){
            SetRoot(leftchild);
        }
        InsertNode(temp1);
        InsertNode(temp2);
    } else if (rightchild){
        node->left = par;
        par->right = NULL;
        par->parent = node;
        node->parent = grandparent;
    }
}

//Rotate node right
void AVL::RotateRight(shared_ptr<avl_node> node) {
    shared_ptr<avl_node> grandparent(new avl_node);
    shared_ptr<avl_node> temp1(new avl_node);
    shared_ptr<avl_node> temp2(new avl_node);
    shared_ptr<avl_node> curr(node);
    shared_ptr<avl_node> leftchild(node->left);
    shared_ptr<avl_node> rightchild(node->right);
    shared_ptr<avl_node> par(node->parent);

    if (node == NULL || node->parent == NULL) {
        return;
    }

    if (node->parent->parent){
        grandparent = node->parent->parent;
    } else {
        grandparent = NULL;
    }
    if (par == root_ptr){
        SetRoot(node);
    }

    if (rightchild){
        node->right = NULL;
        par->left = NULL;
        par->parent = rightchild;
        node->parent = rightchild;
        rightchild->parent = grandparent;
        temp1 = rightchild->left;
        rightchild->left = node;
        temp2 = rightchild->right;
        rightchild->right = par;
        if (node == root_ptr){
            rightchild->parent = NULL;
            SetRoot(rightchild);
        }
        InsertNode(temp1);
        InsertNode(temp2);
    } else if (leftchild){
        node->right = par;
        par->left = NULL;
        par->parent = node;
        node->parent = grandparent;
    } 
}

//Returns root pointer
shared_ptr<avl_node> AVL::GetRoot(){
    return root_ptr;
}

//Sets root pointer
void AVL::SetRoot(shared_ptr<avl_node> root){
    root_ptr = root;
    root_ptr->source = root->source;
    root_ptr->parent = NULL;
}