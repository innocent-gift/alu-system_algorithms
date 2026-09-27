#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a new parent node
 * @priority_queue: Pointer to the priority queue
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left, *right, *new_tree_node, *wrapper_node;
	symbol_t *left_sym, *right_sym, *new_symbol;
	size_t new_freq;

	if (priority_queue == NULL || priority_queue->size < 2)
		return (0);

	left = (binary_tree_node_t *)heap_extract(priority_queue);
	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (left == NULL || right == NULL)
		return (0);

	left_sym = (symbol_t *)left->data;
	right_sym = (symbol_t *)right->data;
	new_freq = left_sym->freq + right_sym->freq;

	new_symbol = symbol_create(-1, new_freq);
	if (new_symbol == NULL)
		return (0);

	new_tree_node = binary_tree_node(NULL, new_symbol);
	if (new_tree_node == NULL)
	{
		free(new_symbol);
		return (0);
	}

	new_tree_node->left = left;
	new_tree_node->right = right;
	left->parent = new_tree_node;
	right->parent = new_tree_node;

	wrapper_node = binary_tree_node(NULL, new_tree_node);
	if (wrapper_node == NULL)
	{
		free(new_symbol);
		free(new_tree_node);
		return (0);
	}

	if (heap_insert(priority_queue, wrapper_node) == NULL)
	{
		free(wrapper_node);
		free(new_tree_node);
		free(new_symbol);
		return (0);
	}

	return (1);
}
