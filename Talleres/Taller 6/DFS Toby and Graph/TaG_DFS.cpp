#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXV 10005
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1
#define myInfinite 2147483647
int cont;
/*
int time = 0;
*/
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

  G = (struct graph *)malloc(sizeof(struct graph));

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

void DFS_Visit(int u, struct graph *G, int color[], int d[],
               int f[], int pi[], int *time)
{
  struct edge *tempEdge;
  int v;

  color[u] = GRAY;
  *time = *time + 1;
  d[u] = *time;
  tempEdge = G->Adj[u];

  while (tempEdge != NULL)
  {
    v = tempEdge->vertex;
    if (color[v] == WHITE)
    {
      pi[v] = u;
      DFS_Visit(v, G, color, d, f, pi, &(*time));
    }
    tempEdge = tempEdge->next;
  }
  color[u] = BLACK;
  *time = *time + 1;
  f[u] = *time;
}

/*
void DFS_Visit(int u, struct graph *G, int color[], int d[],
               int f[], int pi[])
{
    struct edge *tempEdge;
    int v;

    color[u] = GRAY;
    time = time + 1;
    d[u] = time;
    tempEdge = G->Adj[u];

    while(tempEdge != NULL)
    {
        v = tempEdge->vertex;
        if(color[v] == WHITE)
        {
            pi[v] = u;
            DFS_Visit(v, G, color, d, f, pi);
        }
        tempEdge = tempEdge->next;
    }
    color[u] = BLACK;
    time = time + 1;
    f[u] = time;
}
*/

void DFS(struct graph *G, int color[], int d[], int f[], int pi[])
{
  int time, idVertex;

  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
  {
    color[idVertex] = WHITE;
    pi[idVertex] = NIL;
  }
  time = 0;

  for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
  {
    if (color[idVertex] == WHITE)
      DFS_Visit(idVertex, G, color, d, f, pi, &time);
  }
}

void Solver(struct graph *G)
{
  int color[MAXV], d[MAXV], f[MAXV], pi[MAXV], idVertex;
  DFS(G, color, d, f, pi);
  for(idVertex = 1; idVertex <= G->n_vertex; idVertex++) {
    if(pi[idVertex] == NIL) {
      cont++;
    }
  }
}

int Gauss() {
  int k, n;
  if(cont < 2) {
    return 0;
  }
  n = cont - 1;
  k = ((n*(n+1))/2);
  return k;
}

int main()
{
  int vertexes, edges, a, b, i, v, u, T;
  struct graph *G;
  struct edge *tempEdge;
  scanf("%d", &T);
  for (int j = 1; j <= T; j++)
  {
    scanf("%d %d", &vertexes, &edges);
    G = ReadGraph(vertexes, edges);
    cont = 0;
    Solver(G);
    printf("%d\n", Gauss());
    G = DeleteGraph(G);
  }
  return 0;
}
