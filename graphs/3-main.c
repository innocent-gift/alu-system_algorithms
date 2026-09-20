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

graph_add_edge(graph, "San Francisco", "Seattle", BIDIRECTIONAL);
graph_add_edge(graph, "Seattle", "New York", UNIDIRECTIONAL);

printf("Before deletion:\n");
graph_display(graph);

graph_delete(graph);
printf("Graph successfully deleted!\n");

return (EXIT_SUCCESS);
}
