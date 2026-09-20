#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

int main(void)
{
graph_t *graph;

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

if (!graph_add_edge(graph, "San Francisco", "Seattle", BIDIRECTIONAL))
{
fprintf(stderr, "Failed to add edge\n");
return (EXIT_FAILURE);
}
if (!graph_add_edge(graph, "San Francisco", "New York", UNIDIRECTIONAL))
{
fprintf(stderr, "Failed to add edge\n");
return (EXIT_FAILURE);
}
if (!graph_add_edge(graph, "New York", "Miami", BIDIRECTIONAL))
{
fprintf(stderr, "Failed to add edge\n");
return (EXIT_FAILURE);
}

graph_display(graph);

return (EXIT_SUCCESS);
}
