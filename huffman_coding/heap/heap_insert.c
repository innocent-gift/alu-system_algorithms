#include <stdlib.h>
#include "heap.h"

/**
 * get_parent_node - Finds the parent node where a new node should be inserted
 * @root: Root of the heap
 * @size: Current size of the heap
 * Return: Pointer to the parent node
 */
static binary_tree_node_t *get_parent_node(binary_tree_node_t *root, size_t size)
{
	size_t path, mask;
	binary_tree_node_t *curr;

	if (root == NULL || size == 0)
		return (NULL);

	path = size + 1;
	mask = 1;
	while (mask <= path)
		mask <<= 1;
	mask >>= 2;

	curr = root;
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
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap
 * @data: Pointer to the data to store
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *parent, *node;
	void *tmp;

	if (heap == NULL || data == NULL)
		return (NULL);
	if (heap->root == NULL)
	{
		heap->root = binary_tree_node(NULL, data);
		if (heap->root == NULL)
			return (NULL);
		heap->size = 1;
		return (heap->root);
	}
	parent = get_parent_node(heap->root, heap->size);
	node = binary_tree_node(parent, data);
	if (node == NULL)
		return (NULL);
	if (parent->left == NULL)
		parent->left = node;
	else
		parent->right = node;
	heap->size++;

	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;
		node = node->parent;
	}
	return (node);
}
