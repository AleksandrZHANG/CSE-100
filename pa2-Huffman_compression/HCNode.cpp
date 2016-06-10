/**
 *  CSE 100 PA2
 *  Authors: Yihong Zhang, Hao Gai
 *  Date: 4.16.2016 
*/

#include "HCNode.hpp"
/** Compare this HCNode and other for priority ordering.
 *  Small count means higher priority.
 *  Use node symbol for deterministic tiebreaking
 */
bool HCNode::operator<(HCNode const & other){ 
    // if counts are different, just compare symbols
    if(count != other.count) return count > other.count;

    // counts are equal. use symbol value to break tie.
    // (for this to work, internal HCNodes must have symb set.)
    return symbol < other.symbol;
};

