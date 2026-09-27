#include <stdlib.h>
#include "heap.h"

/**
 * get_parent_path - Gets the path to the insertion node using binary representation
 * @size: Current size of the heap before insertion
 * Return: Bitmask representing the path (left = 0, right = 1)
 */
static unsigned int get_parent_path(size_t size)
{
	size_t node = size + 1;
	unsigned int path = 0;
	unsigned int mask = 1;

	while (node > 1)
	{
		if (node & 1)
			path |= mask;
		mask <<= 1;
		node >>= 1;
	}
	return (path);
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap
 * @data: Pointer to data to store
 * Return: Pointer to created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *curr;
	unsigned int path, mask;
	void *temp_data;

	if (heap == NULL || data == NULL)
		return (NULL);

	node = binary_tree_node(NULL, data);
	if (node == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = node;
		heap->size++;
		return (node);
	}

	path = get_parent_path(heap->size);
	curr = heap->root;
	mask = 1;
	while (mask < path)
		mask <<= 1;
	mask >>= 1;

	while (mask > 0)
	{
		if (path & mask)
			curr = curr->right;
		else
			curr = curr->left;
		mask >>= 1;
	}

	node->parent = curr;
	if (curr->left == NULL)
		curr->left = node;
	else
		curr->right = node;

	heap->size++;

	curr = node;
	while (curr->parent && heap->data_cmp(curr->data, curr->parent->data) < 0)
	{
		temp_data = curr->data;
		curr->data = curr->parent->data;
		curr->parent->data = temp_data;
		curr = curr->parent;
	}

	free(node);
	return (curr);
}
