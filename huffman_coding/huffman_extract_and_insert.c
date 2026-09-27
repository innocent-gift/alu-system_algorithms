#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a new parent
 * @priority_queue: Pointer to the priority queue
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left, *right, *new_node;
	symbol_t *l_sym, *r_sym, *new_sym;
	size_t sum_freq;

	if (priority_queue == NULL || priority_queue->size < 2)
		return (0);

	left = heap_extract(priority_queue);
	right = heap_extract(priority_queue);
	if (left == NULL || right == NULL)
		return (0);

	l_sym = left->data;
	r_sym = right->data;
	sum_freq = l_sym->freq + r_sym->freq;

	new_sym = symbol_create('$', sum_freq);
	if (new_sym == NULL)
		return (0);

	new_node = binary_tree_node(NULL, new_sym);
	if (new_node == NULL)
	{
		free(new_sym);
		return (0);
	}

	new_node->left = left;
	new_node->right = right;
	left->parent = new_node;
	right->parent = new_node;

	if (heap_insert(priority_queue, new_node) == NULL)
	{
		free(new_node);
		free(new_sym);
		return (0);
	}

	return (1);
}
