#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * add_single_edge - Adds a directed edge from src to dest
 * @src: Source vertex
 * @dest: Destination vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int add_single_edge(vertex_t *src, vertex_t *dest)
{
edge_t *new_edge, *tmp;

tmp = src->edges;
while (tmp)
{
if (tmp->dest == dest)
return (1);
tmp = tmp->next;
}

new_edge = malloc(sizeof(edge_t));
if (!new_edge)
return (0);

new_edge->dest = dest;
new_edge->next = src->edges;
src->edges = new_edge;
src->nb_edges++;
return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices to an existing graph
 * @graph: Pointer to the graph
 * @src: String identifying source vertex
 * @dest: String identifying destination vertex
 * @type: UNIDIRECTIONAL or BIDIRECTIONAL
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
   edge_type_t type)
{
vertex_t *v_src = NULL, *v_dest = NULL, *v;

if (!graph || !src || !dest)
return (0);

v = graph->vertices;
while (v && (!v_src || !v_dest))
{
if (strcmp(v->content, src) == 0)
v_src = v;
if (strcmp(v->content, dest) == 0)
v_dest = v;
v = v->next;
}

if (!v_src || !v_dest)
return (0);

if (!add_single_edge(v_src, v_dest))
return (0);

if (type == BIDIRECTIONAL)
{
if (!add_single_edge(v_dest, v_src))
return (0);
}

return (1);
}
