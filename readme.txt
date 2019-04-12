The HForest and HTree classes and their associated files were used from Danny Riso's submission for Homework7. bitio.hh,
test_bitio.cc, huffman.hh, test_huffman.cc, and Makefile were built from the starting files given on the Moodle. All other
files were built by Danny.

On the Huffman class:
	The constructor's only unique job is to initialize the frequency table, represented as a vector of ints, to all
zeros. The code for building a Huffman tree was kept in a separate function, build_huff_tree(), so it could be repeatedly
called whenever the frequency table was updated.
	encode() creates a new Huffman tree, then navigates through it to the desired symbol, adding the left or right
branches as 1's or 0's. It updates the frequency table for the symbol, then returns the generated code.
	decode() functions using the class variable current_decode_node, which is initialized as the root of the Huffman
tree. If, when decode() is called, current_decode_node is still the root of the Huffman tree (indicating that the byte
being generated is a new byte, and not in the middle of bits), it builds a new Huffman tree to ensure the frequency table
is correctly represented. From there, decode() follows whatever direction is passed to it and moved the current_decode_node
to the left or right child, repeating until it reaches a valid symbol. Once it does, it updates the frequency table and
resets the current_decode_node to prepare for the next int.
	Using valgrind, no memory leaks were detected.

On BitIO:
	The constructor of BitIO first asserts that only one of the two iostreams is nullptr. Following that, it initializes
the buffer and bit_index, then depending on whether it is an input or output buffer, saves the stream accordingly in class
stringstreams in and out. The destructor uses the flush() method from the ostream class to remove unused output bits and
trailing zeros. I was unable to figure out how to write the unused bits to the ostream due to poor time management.
	output_bit() takes in bits and gradually fills a buffer until an entire character is constructed. The size of the
buffer is iterated with bit_index; when it reaches 8, the buffer is inserted into the ostream, and the buffer and bit_index
are reset. Until then, bit_index is incremented with every call to output_bit(), and the buffer grows by adding the value
of the bit in the position designated by bit_index.
	input_bit() reads the incoming stream passed to the BitIO object and returns its first bit. It does so by first
checking that there is something to read - if not, it gets the next character from the istream. Once the buffer is thus
determined, input_bit() uses a mask to compare each bit of the buffer to 1; using bitwise and, it eventually returns the
bit in each position of the int. This method was the last of many to attempt to pull a bit from the buffer, none of which
were able to pass all the asserts in test_bitio. Again, due to poor time management, I was unable to seek help with this
error. Efforts will be made in the future to ensure that assignments are complete and help is sought when needed. As it is,
input_bit() is not usable.
	Without the failed asserts, valgrind did not detect any memory leaks.

On encoder and decoder:
	encoder takes in any number of files as command line arguments and encodes them using a Huffman tree. It first
reads the original file, character-by-character, and encodes each according to the adaptive Huffman tree. Then, each bit
is processed using output_bit() to produce a binary file. The binary file, already named with the .comp suffix, and
original file are then both closed.
	decoder does much of the same. It takes in files as command line arguments, creates a Huffman tree, and creates a
new file for the decoded symbols. It reads each bit from the compressed file and runs them through decode() until it reaches
a leaf and returns a valid symbol. Then the symbol is printed in the new file, identical to the original, and it keeps
cycling until it reaches Huffman::HEOF.
	Neither encoder nor decoder could be tested practically due to input_bit()'s failure.
	Using valgrind, there were no memory leaks in encoder or decoder.

Unfortunately, since BitIO's input_bit() doesn't actually work, the compression couldn't be tested with real files. There
are no results for the compression tests.
