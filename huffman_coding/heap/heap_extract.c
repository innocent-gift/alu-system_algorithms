#include <stdlib.h>
#include "heap.h"

/**
 * get_last_node - Finds the last node in the heap using binary path
 * @heap: Pointer to the heap
 * Return: Pointer to the last binary tree node
 */
static binary_tree_node_t *get_last_node(heap_t *heap)
{
	size_t node = heap->size;
	unsigned int path = 0, mask = 1;
	binary_tree_node_t *curr;

	while (node > 1)
	{
		if (node & 1)
			path |= mask;
		mask <<= 1;
		node >>= 1;
	}

	curr = heap->root;
	mask >>= 1;
	while (mask > 0)
	{
		if (path & mask)
			curr = curr->right;
		else
			curr = curr->left;
		mask >>= 1;
	}
	return (curr);
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap
 * Return: Pointer to data stored in root node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *extracted_data;
	binary_tree_node_t *last;
	binary_tree_node_t *curr, *smallest;
	void *temp;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	extracted_data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (extracted_data);
	}

	last = get_last_node(heap);
	heap->root->data = last->data;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;
	free(last);
	heap->size--;

	curr = heap->root;
	while (curr && (curr->left || curr->right))
	{
		smallest = curr;
		if (curr->left && heap->data_cmp(curr->left->data, smallest->data) < 0)
			smallest = curr->left;
		if (curr->right && heap->data_cmp(curr->right->data, smallest->data) < 0)
			smallest = curr->right;
		if (smallest == curr)
			break;
		temp = curr->data;
		curr->data = smallest->data;
		smallest->data = temp;
		curr = smallest;
	}

	return (extracted_data);
}
