/**
/* Name: Yihong Zhang
/* Date: 1.25.2016
/* Assignment number: PA2
*/

#include "BitInputStream.hpp"

using namespace std;

int BitInputStream::readBit() {
    if(nbits == 8) { 
	buf = in.get(); 
	nbits = 0; 
    } 
    int result = (buf>>(7-nbits)) & 1; 
    nbits++; 
    return result; 
}

int BitInputStream::readByte() { 
    return in.get();
} 

int BitInputStream::readInt() {
    int count;
    if(!in.eof() && in.good()) {
	int count;
	in >> count;
	return count;
    }
    else return -1;
}
