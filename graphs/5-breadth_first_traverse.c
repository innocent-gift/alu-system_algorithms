#include <stdlib.h>
#include "graphs.h"

/**
 * struct queue_node_s - Queue node for BFS traversal
 * @vertex: Pointer to vertex
 * @depth: Depth of vertex
 * @next: Pointer to next node
 */
typedef struct queue_node_s
{
const vertex_t *vertex;
size_t depth;
struct queue_node_s *next;
} queue_node_t;

/**
 * breadth_first_traverse - Goes through a graph using breadth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Pointer to function called for each visited vertex
 *
 * Return: Biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
    void (*action)(const vertex_t *v, size_t depth))
{
int *visited;
queue_node_t *head = NULL, *tail = NULL, *new_node, *temp;
const vertex_t *curr_v;
edge_t *edge;
size_t max_depth = 0, curr_depth;

if (!graph || !graph->vertices || !action)
return (0);

visited = calloc(graph->nb_vertices, sizeof(int));
if (!visited)
return (0);

new_node = malloc(sizeof(queue_node_t));
if (!new_node)
{
free(visited);
return (0);
}
new_node->vertex = graph->vertices;
new_node->depth = 0;
new_node->next = NULL;
head = tail = new_node;
visited[graph->vertices->index] = 1;

while (head)
{
curr_v = head->vertex;
curr_depth = head->depth;

if (curr_depth > max_depth)
max_depth = curr_depth;

action(curr_v, curr_depth);

temp = head;
head = head->next;
free(temp);
if (!head)
tail = NULL;

edge = curr_v->edges;
while (edge)
{
if (!visited[edge->dest->index])
{
visited[edge->dest->index] = 1;
new_node = malloc(sizeof(queue_node_t));
if (!new_node)
{
while (head)
{
temp = head;
head = head->next;
free(temp);
}
free(visited);
return (0);
}
new_node->vertex = edge->dest;
new_node->depth = curr_depth + 1;
new_node->next = NULL;

if (!tail)
head = tail = new_node;
else
{
tail->next = new_node;
tail = new_node;
}
}
edge = edge->next;
}
}

free(visited);
return (max_depth);
}
