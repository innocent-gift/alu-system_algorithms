#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds the Huffman tree
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of arrays
 * Return: Pointer to root node of Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *pq;
	binary_tree_node_t *wrapper, *root;

	if (data == NULL || freq == NULL || size == 0)
		return (NULL);

	pq = huffman_priority_queue(data, freq, size);
	if (pq == NULL)
		return (NULL);

	while (pq->size > 1)
	{
		if (!huffman_extract_and_insert(pq))
		{
			heap_delete(pq, NULL);
			return (NULL);
		}
	}

	wrapper = (binary_tree_node_t *)heap_extract(pq);
	if (wrapper == NULL)
	{
		heap_delete(pq, NULL);
		return (NULL);
	}

	root = (binary_tree_node_t *)wrapper->data;
	root->parent = NULL;
	free(wrapper);
	heap_delete(pq, NULL);

	return (root);
}
