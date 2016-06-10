/**
 *  CSE 100 PA2
 *  Authors: Yihong Zhang, Hao Gai
 *  Date: 4.16.2016
 *  1.Read the file header (which contains the code) to recreate the tree
 *  2.Decode each letter by reading the file and using the tree
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
    //Check for empty file
    in.seekg(0, ios_base::end); 
    unsigned int len = in.tellg();
    if(len==0) 
    {
	ofstream out;
	out.open(argv[2],ios::binary);
	out.close();
	return 0;
    }
    in.seekg(0, ios_base::beg);
    vector<int> count(256,0);
    BitInputStream is = BitInputStream(in);

    /**
    * 2. Read the file header at the beginning of the input file,
    * and reconstruct the Huffman coding tree.
    */
    int countAll = 0;
    int index = 0;
    int realcount = is.readInt();
    for(int i=0;i<realcount;i++) {
	index = is.readInt();
	count[index] = is.readInt();
	countAll += count[index];
    }
    is.readByte();		// Read last space
    HCTree Huffman;
    Huffman.build(count);

    /** 3. Open the output file for writing. */
    ofstream out;
    out.open(argv[2],ios::binary);

    /**
    * 4. Using the Huffman coding tree, decode the bits from the input file
    * into the appropriate sequence of bytes, writing them to the output file.
    */
    BitOutputStream os = BitOutputStream(out);
    while(countAll) {
	os.writeByte(Huffman.decode(is));
	if(!out.good()) break;
	countAll--;
    }

    /** 5. Close the input and output files. */
    in.close();
    out.close();
    return 0;
}
