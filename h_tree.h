#ifndef H_TREE_H
#define H_TREE_H
#include <cstdlib>
#include <cstdio>
#include "h_const.h"
using namespace std;

struct h_node
{
	char data;
	int freq;
	h_node* left;
	h_node* right;
	// EOF is used as default for data instead of 0 (NULL in ASCII), this is for non-leaf nodes
	// A normal text file usually do not have NULL char but if it does, it may cause issues, 
	// EOF will never be in file only once and it is ignored
	h_node(char data = EOF, int freq = 0)
	{
		this->data = data;
		this->freq = freq;
		left = nullptr;
		right = nullptr;
	}
	// ~h_node()
};

struct h_tree
{
	h_node* head;
	h_tree()
	{
		head = (h_node*)malloc(sizeof(h_node));
		*head = h_node();
	}
};

#endif