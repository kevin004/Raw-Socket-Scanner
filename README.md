# Raw-Socket-Scanner
Network analyzer to sort incoming packets by source ip address in a self-balancing tree

There are four files:
AVL.h
AVL.cpp
main.cpp
README.md

To test the code, I first build the main file; I then run the file as sudo ./main as this open a raw socket. After 100 unique source IP addresses have been saved in my AVL_Tree, my socket closes and I test the AVL_Tree by examining the height of each node through an inorder traversal of the tree.
