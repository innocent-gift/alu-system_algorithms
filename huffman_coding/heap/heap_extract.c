#include <stdlib.h>
#include "heap.h"

/**
 * get_last_node - Finds the last node of the heap
 * @root: Root of the heap
 * @size: Size of the heap
 * Return: Pointer to the last node
 */
static binary_tree_node_t *get_last_node(binary_tree_node_t *root, size_t size)
{
	size_t mask;
	binary_tree_node_t *curr;

	if (root == NULL || size <= 1)
		return (root);

	mask = 1;
	while (mask <= size)
		mask <<= 1;
	mask >>= 2;

	curr = root;
	while (mask > 0)
	{
		if (size & mask)
			curr = curr->right;
		else
			curr = curr->left;
		mask >>= 1;
	}
	return (curr);
}

/**
 * sift_down - Restores the min-heap property by sifting down
 * @node: Root node to sift down
 * @data_cmp: Comparison function
 */
static void sift_down(binary_tree_node_t *node, int (*data_cmp)(void *, void *))
{
	binary_tree_node_t *smallest;
	void *tmp;

	while (node && (node->left || node->right))
	{
		smallest = node;
		if (node->left && data_cmp(node->left->data, smallest->data) < 0)
			smallest = node->left;
		if (node->right && data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;
		if (smallest == node)
			break;
		tmp = node->data;
		node->data = smallest->data;
		smallest->data = tmp;
		node = smallest;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap
 * Return: Pointer to the data stored in the root node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last = get_last_node(heap->root, heap->size);
	heap->root->data = last->data;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	free(last);
	heap->size--;

	sift_down(heap->root, heap->data_cmp);
	return (data);
}
