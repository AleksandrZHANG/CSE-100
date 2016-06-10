/**
 *  CSE 100 PA1
 *  Authors: Yihong Zhang, Yi Zheng
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    BSTNode<Data>* succ;
    // has no right child
    if (!right)
    {
	if (!parent) return 0;			// root
	// is the left child of parent => succ = parent
	else {						// going up
	    succ = this;
	    while (succ == succ->parent->right) {	// is the right child 
		succ = succ->parent;
		if (!succ->parent) return 0;		// is the biggest node
		else if (succ == succ->parent->left) break;
	    }
	    // is the left child of parent => succ = parent
	    succ = succ->parent;
	}
    }
    // has right child
    else {
	succ = this->right;				// going down
	while (succ->left)	succ = succ->left;	// is the left child
    }
    return succ;
  }

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
