// Reads in symbols from an un-encoded file, reads them into bits encoded by the Huffman tree, and then prints the encoded
// result in a new .comp file. 

#include "bitio.hh"
#include "huffman.hh"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
	for(int i = 1; i < argc; ++i) {
		std::stringstream bits;
		Huffman huff;

		// Reads in the file
		auto raw_file_name = argv[i];
		std::ifstream read_in(raw_file_name);
		
		// Writes a new file with a .comp suffix
		std::ofstream write_out(*raw_file_name + ".comp");
	
		// Compresses the original file
		while(read_in.get()) {
			auto symbol = read_in.get();
			BitIO bit_write(&bits, nullptr);
			Huffman::bits_t comp = huff.encode(symbol);
			for(auto bit : comp) {
				bit_write.output_bit(bit);
			}
			write_out << bits.str();
		}
		
		// Closes both files
		read_in.close();
		write_out.close();
	}

	return 0;
}
