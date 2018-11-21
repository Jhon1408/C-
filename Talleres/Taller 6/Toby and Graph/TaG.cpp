#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXV 1005
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1
#define myInfinite 2147483647

struct edge
{
  int vertex;
  /*    int weight; */
  struct edge *next;
};

struct graph
{
  int n_vertex;
  int n_edges;
  struct edge *Adj[MAXV];
};

struct graph *ReadGraph(int vertexes, int edges)
{
  int idVertex, idEdge, v, u;
  struct graph *G;
  struct edge *tempEdge;

  G = (struct graph *) malloc(sizeof(struct graph));

  G->n_vertex = vertexes;
  G->n_edges = edges;

  for (idVertex = 0; idVertex <= G->n_vertex; idVertex++)
  {
    G->Adj[idVertex] = NULL;
  }

  for (idEdge = 1; idEdge <= G->n_edges; idEdge++)
  {
    scanf("%d %d", &v, &u);

    tempEdge = (struct edge *)malloc(sizeof(struct edge));
    tempEdge->vertex = u;
    tempEdge->next = G->Adj[v];
    G->Adj[v] = tempEdge;

    if (v != u)
    {
      tempEdge = (struct edge *)malloc(sizeof(struct edge));
      tempEdge->vertex = v;
      tempEdge->next = G->Adj[u];
      G->Adj[u] = tempEdge;
    }
  }
  return G;
}

void PrintGraph(struct graph *G)
{
  int idVertex;
  struct edge *tempEdge;
  if (G != NULL)
  {
    printf("Representation for graph's adjacent lists: \n");
    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    {
      printf("[%d]: ", idVertex);
      tempEdge = G->Adj[idVertex];
      while (tempEdge != NULL)
      {
        printf(" -> %d", tempEdge->vertex);
        tempEdge = tempEdge->next;
      }
      printf(" -> NULL\n");
    }
  }
  else
    printf("Empty Graph.\n");
}

struct graph *DeleteGraph(struct graph *G)
{
  int idVertex;
  struct edge *ActualEdge, *NextEdge;

  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
  {
    ActualEdge = G->Adj[idVertex];
    while (ActualEdge != NULL)
    {
      NextEdge = ActualEdge->next;
      free(ActualEdge);
      ActualEdge = NextEdge;
    }
  }
  free(G);
  G = NULL;
  return G;
}

void BFS(struct graph *G, int s, int color[], int d[], int pi[])
{
  struct edge *tempEdge;
  int idVertex, u, v, Queue[MAXV], head = 1, tail = 1;

  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
  {
    color[idVertex] = WHITE;
    d[idVertex] = myInfinite;
    pi[idVertex] = NIL;
  }

  color[s] = GRAY;
  d[s] = 0;
  Queue[tail] = s;
  tail++;

  while (head < tail)
  {
    u = Queue[head];
    head++;
    tempEdge = G->Adj[u];
    while (tempEdge != NULL)
    {
      v = tempEdge->vertex;
      if (color[v] == WHITE)
      {
        color[v] = GRAY;
        d[v] = d[u] + 1;
        pi[v] = u;
        Queue[tail] = v;
        tail++;
      }
      tempEdge = tempEdge->next;
    }
    color[u] = BLACK;
  }
}

void Path(int u, int pi[])
{
  if (pi[u] == NIL)
    printf("%d", u);
  else
  {
    Path(pi[u], pi);
    printf(" -> %d", u);
  }
}

void Solver(struct graph *G, int source)
{
  int color[MAXV], d[MAXV], pi[MAXV], f[MAXV], idVertex;
  BFS(G, source, color, d, pi);
  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    printf("d[%d]: %d\n", idVertex, d[idVertex]);
  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    printf("pi[%d]: %d\n", idVertex, pi[idVertex]);
  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
  {
    if (color[idVertex] == WHITE)
      printf("color[%d]: WHITE\n", idVertex);
    if (color[idVertex] == GRAY)
      printf("color[%d]: GRAY\n", idVertex);
    if (color[idVertex] == BLACK)
      printf("color[%d]: BLACK\n", idVertex);
  }

  printf("\n");
  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
  {
    Path(idVertex, pi);
    printf("\n");
  }
}

int main()
{
  int vertexes, edges, a, b, i, v, u, T;
  struct graph *G;
  struct edge *tempEdge;
  scanf("%d", &T);
  for(i = 1; i <= T; i++) {
    scanf("%d %d", &vertexes, &edges);
    G = ReadGraph(vertexes, edges);
    PrintGraph(G);
    G = DeleteGraph(G);
  }
  return 0;
}