#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * add_edge_to_vertex - Helper to append an edge to a vertex's edge list
 * @vertex: Pointer to the vertex
 * @dest_v: Pointer to the destination vertex
 * Return: 1 on success, 0 on failure
 */
static int add_edge_to_vertex(vertex_t *vertex, vertex_t *dest_v)
{
edge_t *new_edge, *temp;

new_edge = malloc(sizeof(edge_t));
if (!new_edge)
return (0);
new_edge->dest = dest_v;
new_edge->next = NULL;

if (!vertex->edges)
{
vertex->edges = new_edge;
}
else
{
temp = vertex->edges;
while (temp->next)
temp = temp->next;
temp->next = new_edge;
}
vertex->nb_edges++;
return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices to a graph
 * @graph: Pointer to the graph
 * @src: Content of the source vertex
 * @dest: Pointer to the destination vertex content
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
   edge_type_t type)
{
vertex_t *src_v = NULL, *dest_v = NULL, *temp;

if (!graph || !src || !dest)
return (0);

temp = graph->vertices;
while (temp)
{
if (strcmp(temp->content, src) == 0)
src_v = temp;
if (strcmp(temp->content, dest) == 0)
dest_v = temp;
temp = temp->next;
}

if (!src_v || !dest_v)
return (0);

if (!add_edge_to_vertex(src_v, dest_v))
return (0);

if (type == BIDIRECTIONAL)
{
if (!add_edge_to_vertex(dest_v, src_v))
return (0);
}

return (1);
}
