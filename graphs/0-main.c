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
printf("Graph created successfully!\n");
free(graph);
return (EXIT_SUCCESS);
}
