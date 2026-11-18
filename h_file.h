#ifndef H_FILE_H
#define H_FILE_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "h_const.h"
#include "h_list.h"
#include "h_tree.h"
using namespace std;

struct code_book
{
	char** codes;
	int* codes_length;
	code_book()
	{
		codes = (char**)malloc(POSSIBLE_CHARS*sizeof(char*));
		for (int i = 0; i < POSSIBLE_CHARS; i++)
		{
			codes[i] = nullptr;
			codes_length = 0;
		}
	}
};

struct h_file
{
	ifstream i_file;
	ofstream o_file;
	char* filename;
	int mode;

	char* msg;
	size_t msg_size;
	int unique_chars;

	h_node** node_table;
	char** code_table;
	code_book cb;
	h_tree tree;

	h_file(char* filename, int mode = UNKNOWN_MODE)
	{
		this->filename = filename;
		this->mode = mode;
		node_table = (h_node**)malloc(POSSIBLE_CHARS*sizeof(h_node*));
		code_table = (char**)malloc(POSSIBLE_CHARS*sizeof(char*));
		for (int i = 0; i < POSSIBLE_CHARS; i++)
		{
			node_table[i] = nullptr;
			code_table[i] = nullptr;
		}
		parse_file();
	}

	~h_file()
	{
		for (int i = 0; i < POSSIBLE_CHARS; i++)
			free(node_table[i]);
		free(node_table);
	}

	int parse_file()
	{
		// Open file and make sure it can be opened
		i_file.open(filename);
		if (!i_file)
		{
			cerr << "File '" << filename << "' could not open!\n";
			return BAD_FILE;
		}

		// Find msg_size
		i_file.seekg(0, ios::end);
		msg_size = i_file.tellg();
		i_file.seekg(0);

		// Specify mode if unknown and compress or decompress accordingly
		if (mode == UNKNOWN_MODE)
			mode = i_file_is_compressed() ? DECOMPRESSION_MODE : COMPRESSION_MODE;
		if (mode == COMPRESSION_MODE)
			return compress_file();
		else if (mode == DECOMPRESSION_MODE)
		{
			if (!i_file_is_compressed()) // File is already decompressed
			{
				cerr << "File '" << filename << "' is not compressed!\n";
				i_file.close();
				return ALREADY_DECOMPRESSED;
			}
			else
			{

			}
		}
		return OK_FILE;
	}

	int compress_file()
	{
		if (i_file_is_compressed()) // Compressed files do not have to be compressed again
		{
			cerr << "File '" << filename << "' is already compressed!\n";
			i_file.close();
			return ALREADY_COMPRESSED;
		}
		else
		{
			// here is where compression happens
			if (msg_size == 0)
			{
				cerr << "File '" << filename << "' is an empty file, nothing to compress!\n"; 
				return EMPTY_FILE;
			}
			else if (msg_size != 0)
			{
				index_file();
				build_tree();
				transverse_tree(tree.head);
				print_codes();
			}
		}
		return OK_FILE;
	}

	// Uses MAGIC_BYTES which are signed in compressed files
	bool i_file_is_compressed()
	{
		// Using peek instead of getting characters to not need to
		// close and open file
		char* first_bytes = (char*)malloc(MAGIC_SIZE*sizeof(char));
		for (int i =0; i < MAGIC_SIZE; i++)
		{
			i_file.seekg(i);
			first_bytes[i] = i_file.peek();
		}
		i_file.seekg(0);
		bool ret = (*first_bytes == *MAGIC_BYTES);
		free(first_bytes);
		return ret;
	}

	void index_file()
	{
		// Buffer for file input
		size_t buffer_size = msg_size;
		if (buffer_size > MAX_BUFFER)
			buffer_size = MAX_BUFFER;
		char* buffer = (char*)malloc(buffer_size*sizeof(char));

		// Fill data of node_table and find number of unique chars
		unique_chars = 0;
		i_file.seekg(0);
		while (i_file.read(buffer, buffer_size))
		{
			for (size_t i = 0; i < buffer_size; i++)
			{
				if (node_table[(int)buffer[i]] == nullptr)
				{
					node_table[(int)buffer[i]] = (h_node*)malloc(sizeof(h_node));
					*(node_table[(int)buffer[i]]) = h_node(buffer[i]);
					unique_chars++;
				}
				(node_table[(int)buffer[i]])->freq++;
			}
		}
		free(buffer);
	}

	void build_tree()
	{
		// Make list of non-null nodes
		h_list* nodes_list = (h_list*)malloc(sizeof(h_list));
		*nodes_list = h_list();
		for (int i = 0, j = 0; i < POSSIBLE_CHARS && j < unique_chars; i++)
		{
			if (node_table[i] != nullptr)
			{
				nodes_list->insert_at_freq(node_table[i]);
				j++;
			}
		}

		// Find head by applying huffman algorithm
		while (nodes_list->length > 1)
		{
			h_node* combined = (h_node*)malloc(sizeof(h_node));
			*combined = h_node();
			combined->freq = ((*nodes_list)[0])->freq + (*nodes_list)[1]->freq;
			combined->left = ((*nodes_list)[0]);
			combined->right = ((*nodes_list)[1]);
			nodes_list->pop_head();
			nodes_list->pop_head();
			nodes_list->insert_at_freq(combined);
		}

		// First (and only) in list is the head of tree
		tree = h_tree();
		tree.head = ((*nodes_list)[0]);

		// Special case where only one character exists in file
		// needs to put a parent to stay consistant with idea of
		// left edge=0, right edge=1, so head code would be NULL
		if (tree.head->data != EOF)
		{
			h_node* new_head = (h_node*)malloc(sizeof(h_node));
			*new_head = h_node();
			new_head->left = tree.head;
			tree.head = new_head;
		}
	}

	void transverse_tree(h_node* cur_node, int length = 0, char* prev_code = nullptr, char next = '0')
	{
		if (cur_node == nullptr)
			return;
		char* cur_code = (char*)malloc(length*sizeof(char));
		for (int i = 0; i < length-1; i++)
			cur_code[i] = prev_code[i];
		cur_code[length-1] = next;
		if (length != 0)
		{
			if (cur_node->data != EOF)
			{
				code_table[(int)(cur_node->data)] = cur_code;
			}
		}
		transverse_tree(cur_node->left, length+1, cur_code, '0');
		transverse_tree(cur_node->right, length+1, cur_code, '1');
	}


	void print_codes()
	{
		for (int i = 0; i < POSSIBLE_CHARS; i++)
			if (code_table[i] != nullptr)
				cout << setbase(16) << showbase << i << " '" << (char)i << "' : " << code_table[i] << "\n";
	}

};

#endif
