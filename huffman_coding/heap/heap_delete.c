#include <stdlib.h>
#include "heap.h"

/**
 * free_tree - Recursively frees binary tree nodes and their data
 * @node: Root of the tree/subtree
 * @free_data: Function to free node data
 */
static void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node == NULL)
		return;
	free_tree(node->left, free_data);
	free_tree(node->right, free_data);
	if (free_data != NULL && node->data != NULL)
		free_data(node->data);
	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: Pointer to the heap to delete
 * @free_data: Pointer to function to free node content
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;
	free_tree(heap->root, free_data);
	free(heap);
}
