#include <stdlib.h>
#include "graphs.h"

/**
 * dfs_helper - Recursive helper for depth-first traversal
 * @v: Current vertex
 * @depth: Current depth
 * @visited: Array tracking visited vertices
 * @action: Action function to call on each visited vertex
 *
 * Return: Biggest depth reached
 */
static size_t dfs_helper(const vertex_t *v, size_t depth, int *visited,
 void (*action)(const vertex_t *v, size_t depth))
{
edge_t *edge;
size_t max_depth = depth;
size_t sub_depth;

visited[v->index] = 1;
action(v, depth);

edge = v->edges;
while (edge)
{
if (!visited[edge->dest->index])
{
sub_depth = dfs_helper(edge->dest, depth + 1, visited, action);
if (sub_depth > max_depth)
max_depth = sub_depth;
}
edge = edge->next;
}

return (max_depth);
}

/**
 * depth_first_traverse - Goes through a graph using depth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Pointer to function called for each visited vertex
 *
 * Return: Biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
    void (*action)(const vertex_t *v, size_t depth))
{
int *visited;
size_t max_depth = 0;

if (!graph || !graph->vertices || !action)
return (0);

visited = calloc(graph->nb_vertices, sizeof(int));
if (!visited)
return (0);

max_depth = dfs_helper(graph->vertices, 0, visited, action);

free(visited);
return (max_depth);
}
