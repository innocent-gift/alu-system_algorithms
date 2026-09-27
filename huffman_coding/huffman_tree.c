#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds the Huffman tree
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of arrays
 * Return: Pointer to the root node of the Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *prio_queue;
	binary_tree_node_t *root;

	if (data == NULL || freq == NULL || size == 0)
		return (NULL);

	prio_queue = huffman_priority_queue(data, freq, size);
	if (prio_queue == NULL)
		return (NULL);

	while (prio_queue->size > 1)
	{
		if (!huffman_extract_and_insert(prio_queue))
		{
			heap_delete(prio_queue, (void (*)(void *))free);
			return (NULL);
		}
	}

	root = heap_extract(prio_queue);
	heap_delete(prio_queue, NULL);
	return (root);
}
