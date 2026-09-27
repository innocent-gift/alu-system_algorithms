#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * print_codes_recursive - Recursively traverses tree to print Huffman codes
 * @node: Current node
 * @buffer: Buffer to store code
 * @depth: Current depth in tree
 */
static void print_codes_recursive(binary_tree_node_t *node, char *buffer, int depth)
{
	symbol_t *symbol;

	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL)
	{
		symbol = (symbol_t *)node->data;
		buffer[depth] = '\0';
		printf("%c: %s\n", symbol->data, buffer);
		return;
	}

	if (node->left)
	{
		buffer[depth] = '0';
		print_codes_recursive(node->left, buffer, depth + 1);
	}
	if (node->right)
	{
		buffer[depth] = '1';
		print_codes_recursive(node->right, buffer, depth + 1);
	}
}

/**
 * free_huffman_tree - Frees Huffman tree nodes and symbol structures
 * @node: Root node
 */
static void free_huffman_tree(binary_tree_node_t *node)
{
	if (node == NULL)
		return;
	free_huffman_tree(node->left);
	free_huffman_tree(node->right);
	if (node->data)
		free(node->data);
	free(node);
}

/**
 * huffman_codes - Builds Huffman tree and prints codes for each symbol
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of arrays
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char buffer[256];

	root = huffman_tree(data, freq, size);
	if (root == NULL)
		return (0);

	print_codes_recursive(root, buffer, 0);
	free_huffman_tree(root);
	return (1);
}
