/**
 *  CSE 100 PA2
 *  Authors: Yihong Zhang, Hao Gai
 *  Date: 4.16.2016 
 */

#include "HCTree.hpp" 

using namespace std;

void HCTree::deleteAll(HCNode *n) {
    if(n) {
	deleteAll(n->c0);
	deleteAll(n->c1);
    }
    delete(n);
}

/** Default destructor.
      Delete every node in HCTree.
*/
HCTree::~HCTree() {
    deleteAll(root);
}

//Build Huffman Tree
void HCTree::build(const vector<int>& frequency){
    priority_queue<HCNode,vector<HCNode *>,HCNodePtrComp> pq;
    for(int i=0;i<frequency.size();i++) {
	if(frequency[i] > 0) {  
	    leaves[i] = new HCNode(frequency[i], i);  
	    pq.push(leaves[i]);  
	}
    }
    while(pq.size() > 1) {
	HCNode* c0 = pq.top();
	pq.pop();
	HCNode* c1 = pq.top();
	pq.pop();
	HCNode* merge=new HCNode(c0->count+c1->count,c0->symbol,c0,c1);
	c0->p = merge;
	c1->p = merge;
	pq.push(merge);
    }
    root = pq.top();
    pq.pop();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* curr = leaves[symbol];
    stack<int> heap;  
    while(curr->p) {
	HCNode* p = curr->p;
	if(p->c0 == curr) heap.push(0);
	else if(p->c1 == curr) heap.push(1);
	curr = p;  
    }  
    while(!heap.empty()) {
	out.writeBit(heap.top());
	heap.pop();
    }
}

int HCTree::decode(BitInputStream& in) const {
    HCNode* curr = root;
    int bit;
    while(curr->c1 || curr->c0) {
	bit = in.readBit();
	if(!bit) curr = curr->c0;
	else curr = curr->c1;
    }
    return curr->symbol;
}
