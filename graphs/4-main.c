#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

void traverse_action(const vertex_t *v, size_t depth)
{
printf("%*s[%lu] %s\n", (int)depth * 4, "", v->index, v->content);
}

int main(void)
{
graph_t *graph;
size_t depth;

graph = graph_create();
if (!graph)
{
fprintf(stderr, "Failed to create graph\n");
return (EXIT_FAILURE);
}

graph_add_vertex(graph, "San Francisco");
graph_add_vertex(graph, "Seattle");
graph_add_vertex(graph, "New York");
graph_add_vertex(graph, "Miami");

graph_add_edge(graph, "San Francisco", "Seattle", BIDIRECTIONAL);
graph_add_edge(graph, "San Francisco", "New York", UNIDIRECTIONAL);
graph_add_edge(graph, "New York", "Miami", BIDIRECTIONAL);

printf("Depth-First Traversal:\n");
depth = depth_first_traverse(graph, &traverse_action);
printf("Max depth reached: %lu\n", depth);

graph_delete(graph);
return (EXIT_SUCCESS);
}
