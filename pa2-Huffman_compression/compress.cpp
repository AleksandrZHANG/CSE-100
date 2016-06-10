/**
 *  CSE 100 PA2
 *  Authors: Yihong Zhang, Hao Gai
 *  Date: 4.16.2016
 *  1.Scan text file to compute frequencies
 *  2.Build Huffman Tree
 *  3.Find code for every symbol (letter)
 *  4.Create new compressed file by saving the entire code at the top
 *  of the file followed by the code for each symbol (letter) in the file
*/

#include "HCTree.hpp"

using namespace std;

int main(int argc,char **argv)
{
    //Check for arguments
    if(argc != 3) {
	cout << "Invalid number of arguments.\n" 
	<< "Usage: ./compress <input filename> <output filename>.\n";
	return -1;
    }

    //Check for file names
    if(!strcmp(argv[1],argv[2])) { 
	cerr << "Error: Same name for input and output files.\n"; 
	return -1; 
    }

    /** 1. Open the input file for reading. */
    ifstream in;
    in.open(argv[1],ios::binary);

    /**
    * 2. Read bytes from the file, counting the number of occurrences of
    * each byte value; then close the file.
    */
    vector<int> count(256,0);
    int ch;
    int isempty = 1;
    while(1) {
	ch = in.get();
	if(!in.good()) break;		// failure
	count[ch]++;			// read a char, count it
	isempty = 0;
    }

    if(isempty) {			// empty file
	ofstream out;
	out.open(argv[2],ios::binary);
	out.close();
	return 0;
    }

    if(!in.eof()) {			// loop stopped for some bad reason...
	cerr << "There was a problem, sorry." << endl; 
	return -1; 
    }
    in.close();

    /**
    * 3. Use these byte counts to construct a Huffman coding tree. Each 
    * unique byte with a non-zero count will be a leaf node in the Huffman tree.
    */
    HCTree Huffman;
    Huffman.build(count);
    
    /** 4. Open the output file for writing. */
    ofstream out;   
    out.open(argv[2],ios::binary);

    /**
    * 5. Write enough information to the output file to enable the coding
    * tree to be reconstructed when the file is read by your uncompress program.
    */   
    BitOutputStream os = BitOutputStream(out);
    int realcount = 0;
    for(int i=0;i<count.size();i++) {
	if (count[i]) realcount++;	//count for asciis that appear	
    }
    os.writeInt(realcount);		//print the number of asciis that appear
    os.writeByte('\n');
    for(int i=0;i<count.size();i++) {
	if (count[i]) {
	os.writeInt(i);
	os.writeByte(' ');
	os.writeInt(count[i]);
	os.writeByte('\n');
	}
    }

    /** 6. Open input file for reading again. */
    in.open(argv[1],ios::binary);

    /**
    * 7. Using the Huffman coding tree, translate each byte from the input
    * file into its code, and append these codes as a sequence of bits to
    * the output file, after the header.
    */
    char symbol;
    while(1) {
	symbol = in.get();
	if(!in.good()) break;
	Huffman.encode(symbol,os);
    }
    os.flush();

    /** 8. Close the input and output files. */
    in.close();
    out.close();
    return 0;
  }
