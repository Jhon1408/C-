#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define infinite 2147483647;
int heapSize = 0;

struct prioridad {
  char name[20];
  int totalTime;
  int type;
  int inTime;
  int walkTime = 0;
};

int Parent(int i) {
  return (int) floor(i/2);
}

int Left(int i) {
    return (2 * i);
}

int Right(int i) {
  return ((2 * i) + 1);
}

void MinHeapify(struct prioridad Q[], int i) {
  int l = Left(i);
  int r = Right(i);
  int least;

  if ((l <= heapSize) && (Q[l].totalTime < Q[i].totalTime)) {
    least = l;
  } else {
    least = i;
  }

  if ((l <= heapSize) && (Q[l].totalTime == Q[i].totalTime)) {
    if (Q[l].inTime < Q[i].inTime) {
      least = l;
    } else {
      least = i;
    }

    if(Q[l].inTime == Q[i].inTime) {
      if(Q[l].type < Q[i].type) {
        least = l;
      } else {
        least = i;
      }
    }
  }

  if ((r <= heapSize) && (Q[r].totalTime < Q[least].totalTime)) {
    least = r;
  }

  if ((r <= heapSize) && (Q[r].totalTime == Q[least].totalTime)) {
    if (Q[r].inTime < Q[least].inTime) {
      least = r;
    }

    if(Q[r].inTime == Q[least].inTime) {
      if(Q[r].type < Q[least].type) {
        least = r;
      }
    }
  }

  if (least != i) {
    struct prioridad temp = Q[i];
    Q[i] = Q[least];
    Q[least] = temp;
    MinHeapify(Q, least);
  }
}

struct prioridad MinPQ_Minimum(struct prioridad Q[]) {
  return Q[1];
}

struct prioridad MinPQ_Extract(struct prioridad Q[]) {
  struct prioridad min;
  if(heapSize < 1) {
    printf("Error (Heap underflow!)\n");
  } else {
    min = Q[1];
    Q[1] = Q[heapSize];
    heapSize = heapSize - 1;
    MinHeapify(Q, 1);
  }
  return min;
}

void MinPQ_DecreaseKey(struct prioridad Q[], int i, struct prioridad key) {
  if (key.totalTime > Q[i].totalTime) {
    printf("Error (New key is higher than current key)");
  } else {
    Q[i] = key;
    struct prioridad temp;
    while ((i > 1) && (Q[Parent(i)].totalTime > Q[i].totalTime)) {
      temp = Q[i];
      Q[i] = Q[Parent(i)];
      Q[Parent(i)] = temp;
      i = Parent(i);
    }
  }
}

void MinPQ_Insert(struct prioridad Q[], struct prioridad key) {
  heapSize = heapSize + 1;
  struct prioridad p;
  p.totalTime = infinite;
  Q[heapSize] = p;
  MinPQ_DecreaseKey(Q, heapSize, key);
  MinHeapify(Q, 1);
}

int minutes(int time) {
  return time%60;
}

int hours(int time) {
  return time/60;
}

int main() {
  int n, r, tstart, troute, type, drop, walk, totalTime;
  char name[20];
  scanf("%d",&n);
  for(int i = 1; i <= n; i++) {
    heapSize = 0;
    scanf("%d %d", &r, &tstart);
    struct prioridad Q[r+5], q;
    for(int i = 1; i <= r; i++) {
      struct prioridad p;
      scanf("%s %d %d", name, &troute, &type);
      if(troute >= tstart) {
        //Insert in the structure
        strcpy(p.name,name);
        p.inTime = troute;
        p.type = type;
        if(type == 1) {
          scanf("%d", &drop);
          totalTime = (troute - tstart) + drop;
          p.totalTime = totalTime;
        } else {
          if(type == 2) {
            scanf("%d %d", &drop, &walk);
            totalTime = (troute - tstart) + drop + walk;
            p.totalTime = totalTime;
            p.walkTime = walk;
          }
        }
        MinPQ_Insert(Q,p);
      }
    }
    q = MinPQ_Extract(Q);
    printf("(%d): %s takes %d minutes, Harry reach hes home at %d:%02dpm.\n",i, q.name, q.totalTime, hours(q.totalTime+tstart), minutes(q.totalTime+tstart));
  }
  return 0;
}
