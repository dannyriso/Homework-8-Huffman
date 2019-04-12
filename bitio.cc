/*
 * A simple class to perform stream I/O on individual bits.
 * Before reading any bits, ensure your input stream still has valid inputs.
 */

#include "bitio.hh"

BitIO::BitIO(std::ostream* os, std::istream* is) {
	// Asserts that either os or is isn't nullptr, and that at least one is nullptr
	assert((os || is) && (!(os && is)));

	bit_index = 0;
	buffer = 0;
	if(os) {
		out = os;
	}
	if(is) {
		in = is;
	}
}

// Flushes out any remaining output bits and trailing zeros, if any:
BitIO::~BitIO() {
	if(bit_index) {
		out->flush();
	}
}

// Outout a single bit (buffered)
void BitIO::output_bit(bool bit) {
	bit_index++;
	if(bit_index == 8) {
		out->put(buffer);
		buffer = 0;
		bit_index = 0;
	} else {
		buffer += (bit << (bit_index - 1));
	}
}

// Read a single bit (or trailing zero)
bool BitIO::input_bit() {
	auto bit = false;
	if(!buffer) {
		buffer = in->get(); 
	}
	
	bit = (buffer >> bit_index) & 1;
	bit_index++;
	return bit;
}
