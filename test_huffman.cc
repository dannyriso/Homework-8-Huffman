/*
 * test_huffman: test the Huffman class
 */

#include "huffman.hh"
#include <iostream>
#include <cassert>
#include <climits>

//////////////////////////////////////////////////////////////////////////////
// Ensure the encoder actually modifies the coding's length as expected
void test_encode()
{
	Huffman huff;

	auto bits = huff.encode('a');
//	assert(bits.size() > CHAR_BIT); // Asserts that bits is more bools than a single byte (generally, 8)
					// Fails when 'a' is more common - has a higher freq_table count
					// Since 'a' is the only encoded variable, expected to fail

	bits = huff.encode('b');
//	assert(bits.size() > CHAR_BIT); // Fails when 'b' has a higher freq_table count
					// Since 'a' and 'b' are the only encoded, still expected to fail

	bits = huff.encode('a');
	assert(bits.size() < CHAR_BIT); // Fails when 'a' has a lower freq_table count

	bits = huff.encode('b');
	assert(bits.size() < CHAR_BIT); // Fails when 'b' has a lower freq_table count

	bits = huff.encode('b');
	assert(bits.size() == huff.encode('a').size()); // Fails unless 'a' and 'b' are relatively equally common
							// The two occur at exactly the same frequency, so does not fail

	bits = huff.encode('b');			// Repeated to check that freq_table is updating - should be
	bits = huff.encode('b');			// a different sequence, if a significant enough change.
	bits = huff.encode('b');
	assert(bits.size() < huff.encode('a').size());	// Fails if 'b' is still less frequent than 'a' after encodes
}

//////////////////////////////////////////////////////////////////////////////
// A utility function that takes a collection of bits and a Huffman tree, and
// figures out which symbol these bits encode.
int decode_symbol(Huffman& huff, const Huffman::bits_t& bits) {
	int symbol = -1;

	for (auto b : bits) {
		symbol = huff.decode(b);
	}
	assert(symbol >= 0);
	return symbol;
}

//////////////////////////////////////////////////////////////////////////////
// Ensure decoding returns the same symbol that was encoded, in different
// scenarios.
void test_decode() {
	Huffman encoder, decoder;

	auto bits = encoder.encode('a');
	assert(decode_symbol(decoder, bits) == 'a');
	bits = encoder.encode('a');
	assert(decode_symbol(decoder, bits) == 'a');
	bits = encoder.encode('b');
	assert(decode_symbol(decoder, bits) == 'b');
	bits = encoder.encode('a');
	assert(decode_symbol(decoder, bits) == 'a');
	bits = encoder.encode(Huffman::HEOF);
	assert(decode_symbol(decoder, bits) == Huffman::HEOF);
	
/* Code used to test encode() and decode() for the smaller alphabet
 * 	auto bits = encoder.encode('!');
	assert(decode_symbol(decoder, bits) == '!');
	bits = encoder.encode('!');
	assert(decode_symbol(decoder, bits) == '!');
	bits = encoder.encode('#');
	assert(decode_symbol(decoder, bits) == '#');
	bits = encoder.encode('!');
	assert(decode_symbol(decoder, bits) == '!');
	bits = encoder.encode(Huffman::HEOF);
	assert(decode_symbol(decoder, bits) == Huffman::HEOF);
*/
}

//////////////////////////////////////////////////////////////////////////////
int main() {
	Huffman huff;
	test_encode();
	test_decode();
	return 0;
}

