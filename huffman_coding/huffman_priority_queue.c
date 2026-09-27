#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * symbol_cmp - Compares frequencies of two symbols stored in nested nodes
 * @p1: Pointer to first nested node
 * @p2: Pointer to second nested node
 * Return: Negative if p1 < p2, positive if p1 > p2, 0 if equal
 */
int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	n1 = (binary_tree_node_t *)p1;
	n2 = (binary_tree_node_t *)p2;
	s1 = (symbol_t *)n1->data;
	s2 = (symbol_t *)n2->data;

	if (s1->freq < s2->freq)
		return (-1);
	if (s1->freq > s2->freq)
		return (1);
	return (0);
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of arrays
 * Return: Pointer to created min heap (priority queue), or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *tree_node;
	symbol_t *symbol;
	size_t i;

	if (data == NULL || freq == NULL || size == 0)
		return (NULL);

	heap = heap_create(symbol_cmp);
	if (heap == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (symbol == NULL)
		{
			heap_delete(heap, NULL);
			return (NULL);
		}
		tree_node = binary_tree_node(NULL, symbol);
		if (tree_node == NULL)
		{
			free(symbol);
			heap_delete(heap, NULL);
			return (NULL);
		}
		if (heap_insert(heap, tree_node) == NULL)
		{
			free(tree_node);
			free(symbol);
			heap_delete(heap, NULL);
			return (NULL);
		}
	}
	return (heap);
}
