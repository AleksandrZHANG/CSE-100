/**
/* Name: Yihong Zhang
/* Date: 1.25.2016
/* Assignment number: PA2
*/

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP
#include <iostream>
#include <string>

class BitInputStream {
private:
    char buf;		// one byte buffer of bits
    int nbits;		// how many bits have been written to buf
    std::istream& in;	// the input stream to use
public: 
    /** Initialize a BitInputStream that will use
    * the given istream for input.
    */
    BitInputStream(std::istream & is) : in(is){
	buf = 0;	// clear buffer
	nbits = 8;	// initialize bit index
    }
    int readBit();	// read next bit
    int readByte(); 	// read next byte
    int readInt();	// read next int
}; 
#endif 
