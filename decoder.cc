// Takes in a compressed file (.comp), reads in bit-by-bit, turns into symbols, and then returns a new file formed from 
// the symbols.

#include "bitio.hh"
#include "huffman.hh"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
	for(int i = 1; i < argc; ++i) {
		Huffman huff;
		auto symbol = -1;
		
		// Reads in the compressed file
		auto comp_file_name = argv[i];
		std::ifstream read_in(comp_file_name);
		
		// Writes the new, decoded file with .plaintext suffix
		std::ofstream write_out(*comp_file_name + ".plaintext");
		
		// Decodes the binary file - loop based on the example given on the Moodle
		while(symbol != Huffman::HEOF) {
			BitIO bit_read(nullptr, &read_in);
			while(symbol < 0) {
				symbol = huff.decode(bit_read.input_bit());
			}
			write_out << symbol;
			symbol = -1;
		}

	}
	return 0;
}
