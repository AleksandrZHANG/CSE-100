/**
 *  CSE 100 PA1
 *  Authors: Yihong Zhang, Yi Zheng
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;
  
public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0), iheight(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
     deleteAll(root);
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  For the reasoning
   *  behind this, see the assignment writeup.
   */ // TODO
  virtual bool insert(const Data& item) {
     unsigned int iiheight=0;
     if (empty()) {
	root = new BSTNode<Data>(item);
	isize++;				// Number of Data items +1
	iheight=++iiheight;
	return true;
     }
     else {
	BSTNode<Data>* curr = root;
	while(1) {
	    if (item < curr->data) {
		if (!curr->left) {		// has no left child
		    curr->left = new BSTNode<Data>(item);
		    curr->left->parent = curr;	// insert as left child
		    iiheight++;
		    break;
		}
		else {
		    curr = curr->left;
		    iiheight++;
		}				// go down
	    }
	    else if (curr->data < item) {
		if (!curr->right) {		// has no right child
		    curr->right = new BSTNode<Data>(item);
		    curr->right->parent = curr;	// insert as right child
		    iiheight++;
		    break;
		}
		else {
		    curr = curr->right;
		    iiheight++;
		}				// go down
	    }
	    // if item was already in this BST
	    else return false;
	}
	isize++;				// Number of Data items +1
	if (iheight<iiheight) iheight = iiheight;
	return true;
    }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */ // TODO
  iterator find(const Data& item) const {
    if (empty()) return 0;
    BSTNode<Data>* curr = this->root;
    while (curr) {
	if (item < curr->data) curr = curr->left;
	else if (curr->data < item) curr = curr->right;
	else return curr;
     }
     return end();
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }
  
  /** Return the height of the BST.
   */ // TODO
  unsigned int height() const {
    return iheight;
  }


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return !root;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
    return typename BST<Data>::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    if (!n) return;
    inorder(n->left);
    std::cout << n->data << std::endl;
    inorder(n->right);
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
    if (!n) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }


 };


#endif //BST_HPP
