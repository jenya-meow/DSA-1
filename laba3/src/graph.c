#include "graph.h"


struct graph *graph_create(int nvertices)
{
    struct graph *g;
    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->visited = malloc(sizeof(int) * nvertices);
    g->m = (int **) malloc(nvertices * sizeof(int *));
    if (g->m != NULL) {
        for (int i = 0; i < nvertices; i++) {
            g->m[i] = (int *) malloc(nvertices * sizeof(int));
        }
    }
    else {
        printf("Can't create buffer!\n");
    }
    graph_clear(g); // Опционально, O(n^2)
    return g;
}

void graph_clear(struct graph *g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++) {
	g->visited[i] = 0;
	for (j = 0; j < g->nvertices; j++) {
	    g->m[i][j] = 0;
	}
    }
}

void graph_free(struct graph *g)
{
    for (int i = 0; i < g->nvertices; i++)
	free(g->m[i]);
    free(g->m);
    free(g);
}

void graph_set_edge(struct graph *g, int i, int j, int w)
{
    g->m[i - 1][j - 1] = w;
    g->m[j - 1][i - 1] = w;
}

int graph_get_edge(struct graph *g, int i, int j)
{
    return g->m[i - 1][j - 1];
}

void graph_dfs(struct graph *g, int v)
{
    int i;
    g->visited[v - 1] = 1;
    printf("Vertex %d\n", v);
    for (i = 0; i < g->nvertices; i++) {
	if (g->m[v - 1][i] > 0 && g->visited[i] == 0) {
	    graph_dfs(g, i + 1);
	}
    }
}

void graph_bfs(struct graph *g, int v)
{
    int i, j;
    struct queue *q;
    for (i = 0; i < g->nvertices; i++)
	g->visited[i] = 0;
    // Создаем очередь
    q = queue_create();
    // Обрабатываем стартовую вершину
    g->visited[v - 1] = 1;
    printf("Vertex %d\n", v);
    queue_enqueue(q, v - 1);
    while (queue_size(q) > 0) {
	i = queue_dequeue(q);
	for (j = 0; j < g->nvertices; j++) {
	    if (g->m[i][j] > 0 && g->visited[j] == 0) {
		queue_enqueue(q, j);
		g->visited[j] = 1;
		printf("Vertex %d\n", j + 1);
	    }
	}
    }
    queue_free(q);
}
