#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * build_codes - Recursive helper to traverse tree and print codes
 * @node: Pointer to current node
 * @buffer: Buffer storing current code string
 * @depth: Current depth/length of code
 */
static void build_codes(binary_tree_node_t *node, char *buffer, int depth)
{
	symbol_t *sym;

	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL)
	{
		sym = (symbol_t *)node->data;
		buffer[depth] = '\0';
		printf("%c: %s\n", sym->data, buffer);
		return;
	}

	if (node->left)
	{
		buffer[depth] = '0';
		build_codes(node->left, buffer, depth + 1);
	}
	if (node->right)
	{
		buffer[depth] = '1';
		build_codes(node->right, buffer, depth + 1);
	}
}

/**
 * free_huffman_tree - Frees the Huffman tree nodes and symbols
 * @node: Pointer to root of tree
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
 * @freq: Array of associated frequencies
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

	build_codes(root, buffer, 0);
	free_huffman_tree(root);
	return (1);
}
