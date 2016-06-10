/**
/* Name: Yihong Zhang
/* Date: 1.25.2016
/* Assignment number: PA2
*/

#include <iostream> 
#include "BitOutputStream.hpp"

using namespace std;

/** Write the least significant bit of the argument to
* the bit buffer, and increment the bit buffer index.
* But flush the buffer first, if it is full.
*/

void BitOutputStream::writeBit(int bit) {
    if(bit == 1) buf = buf | (1<<(7-nbits));
    else buf = buf & ~(1<<(7-nbits));
    if(++nbits == 8) flush();
} 

void BitOutputStream::writeByte(int i) {
    out.put(i);
}

void BitOutputStream::writeInt(int i) {
    out << i;
}

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}
