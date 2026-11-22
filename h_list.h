#ifndef H_LIST_H
#define H_LIST_H
#include <cstdlib>
#include "h_const.h"
#include "h_tree.h"
using namespace std;

struct h_list_node
{
	h_node* h_data;
	h_list_node* next;
	h_list_node(h_node* h_data)
	{
		this->h_data = h_data;
	}
};

struct h_list
{
	h_list_node* head;
	int length;
	h_list()
	{
		head = nullptr;
		length = 0;
	}
	void pop_head()
	{
		if (head != nullptr)
		{
			h_list_node* old_head = head;
			head = head->next;
			free(old_head);
			length--;
		}
	}
	void insert_at_freq(h_node* new_h_node)
	{
		length++;
		int f = new_h_node->freq;
		h_list_node* new_node = (h_list_node*)malloc(sizeof(h_list_node));
		*new_node = h_list_node(new_h_node);
		h_list_node* cur_node = head;
		if (head == nullptr || (head->h_data->freq > f))
		{
			new_node->next = head;
			head = new_node;
			return;
		}
		while (cur_node->next != nullptr && cur_node->next->h_data->freq <= f)
		{
			cur_node = cur_node->next;
		}
		new_node->next = cur_node->next;
		cur_node->next = new_node;
	}
	h_node* operator[](int idx)
	{
		h_list_node* cur_node = head;
		for (int i = 0; i < length-1 && i < idx; i++)
			cur_node = cur_node->next;
		if (cur_node == nullptr)
			return nullptr; // !!
		return cur_node->h_data; 
	}
	const h_node* operator[](int idx) const
	{
		h_list_node* cur_node = head;
		for (int i = 0; i < length-1 && i < idx; i++)
			cur_node = cur_node->next;
		if (cur_node == nullptr)
			return nullptr; // !!
		return cur_node->h_data; 
	}
};

#endif