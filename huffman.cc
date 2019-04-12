// The implementation of the Huffman class.

#include "huffman.hh"

Huffman::Huffman() {
	for(int i = 0; i < ALPHABET_SIZE; ++i) {
		freq_table.push_back(0);
	}
	build_huff_tree();
}

// Creates a new Huffman tree given an updated frequency table
void Huffman::build_huff_tree() {
	HForest forest;
	for(int i = 0; i < Huffman::ALPHABET_SIZE; ++i) {
		HTree tree(i, freq_table[i]);
		forest.add_tree(tree.point());
	}
	auto key = -1;
	while(forest.size() > 1) {
		auto lowest = forest.pop_tree();
		auto next_lowest = forest.pop_tree();
		auto value = lowest->get_value() + next_lowest->get_value();
		auto new_tree = HTree(key, value, lowest, next_lowest);
		forest.add_tree(new_tree.point());
		key--;
	}
	huff_tree = forest.get_trees().front();
	current_decode_node = huff_tree;
}

// Encode a symbol into a sequence of bits, then update frequency table.
Huffman::bits_t Huffman::encode(int symbol) {
	build_huff_tree();
	bits_t bits;
	auto path = huff_tree->path_to(symbol);
	for(auto dir : path) {
		if(dir == HTree::Direction::LEFT) {
			bits.push_back(0);
		} else if(dir == HTree::Direction::RIGHT) {
			bits.push_back(1);
		} else {
			std::cerr << "This shouldn't be possible. But, Direction must be LEFT or RIGHT.";
		}
	}
	freq_table[symbol]++;
	return bits;
}

// Decode a single bit into a symbol. If no symbol can be unmabiguously decoded
// without additional bits, returns a negative value.
// Subsequent calls with more bits should eventually resolve to either
// a character symbol or HEOF.
// Finally, updates the frequency table with this additional symbol.
int Huffman::decode(bool bit) {
	if(current_decode_node == huff_tree) {
		build_huff_tree();
	}
	auto symbol = current_decode_node->get_key();
	if(bit) {
		current_decode_node = current_decode_node->get_child(HTree::Direction::RIGHT);
	} else {
		current_decode_node = current_decode_node->get_child(HTree::Direction::LEFT);
	}
	symbol = current_decode_node->get_key();
	if(symbol >= 0) {
		freq_table[symbol]++;
		current_decode_node = huff_tree;
	}
	return symbol;
}
