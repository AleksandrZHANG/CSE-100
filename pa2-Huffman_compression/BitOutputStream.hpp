/**
/* Name: Yihong Zhang
/* Date: 1.25.2016
/* Assignment number: PA2
*/

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>

class BitOutputStream {
private:
    char buf;				// one byte buffer of bits
    int nbits;				// how many bits have been written to buf
    std::ostream& out;			// reference to the output stream to use
public:
    /**
    * Initialize a BitOutput Stream that will use
    * the given ostream for output.
    */
    BitOutputStream(std::ostream& os) : out(os), buf(0), nbits(0) {
    // clear buffer and bit counter
    }
    void writeBit(int bit);		// write a bit to the bit stream
    void writeByte(int i);		// write an byte to the stream
    void writeInt(int i);		// write an integer to the stream
    void flush();
};
#endif

