#include <stdlib.h>
#include "graphs.h"

/**
 * graph_delete - Completely deletes a graph
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
vertex_t *v_curr, *v_next;
edge_t *e_curr, *e_next;

if (!graph)
return;

v_curr = graph->vertices;
while (v_curr)
{
v_next = v_curr->next;

e_curr = v_curr->edges;
while (e_curr)
{
e_next = e_curr->next;
free(e_curr);
e_curr = e_next;
}

free(v_curr->content);
free(v_curr);
v_curr = v_next;
}

free(graph);
}
