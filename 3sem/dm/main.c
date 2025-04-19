#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Edge {
    int src, dest;
} Edge;

typedef struct EdgeSet {
    Edge* edges;
    int size;
} EdgeSet;

EdgeSet* createEdgeSet(int size) {
    EdgeSet* set = (EdgeSet*)malloc(sizeof(EdgeSet));
    set->edges = (Edge*)malloc(size * sizeof(Edge));
    set->size = size;
    return set;
}

void destroyEdgeSet(EdgeSet* set) {
    free(set->edges);
    free(set);
}

int find(int* parent, int x) {
    while (parent[x] != x) {
        x = parent[x];
    }
    return x;
}

int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return (edgeA->src - edgeB->src) || (edgeA->dest - edgeB->dest);
}

void unionFind(int* parent, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

bool isConnected(EdgeSet* set, int excludeIndex, int* parent) {
    for (int i = 0; i < set->size; ++i) {
        if (i != excludeIndex) {
            int x = find(parent, set->edges[i].src);
            int y = find(parent, set->edges[i].dest);
            if (x != y) {
                unionFind(parent, x, y);
            }
        }
    }

    for (int i = 0; i < set->size; i++) {
        if (find(parent, i) != find(parent, 0)) {
            return false;
        }
    }

    return true;
}

void findArticulationPoints(EdgeSet* set, int numVertices) {
    int* parent = (int*)calloc(numVertices, sizeof(int));
    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
    }

    bool* isArticulationPoint = (bool*)calloc(numVertices, sizeof(bool));

    for (int i = 0; i < set->size; i++) {
        for (int j = 0; j < numVertices; j++) {
            parent[j] = j;
        }

        if (!isConnected(set, i, parent)) {
            isArticulationPoint[set->edges[i].src] = true;
            isArticulationPoint[set->edges[i].dest] = true;
        }
    }

    printf("Точки сочленения:\n");

    for (int i = 0; i < numVertices; ++i) {
        if (isArticulationPoint[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    free(isArticulationPoint);
    free(parent);
}

int main() {
    int numVertices, numEdges;
    printf("Введите число вершин: ");
    scanf("%d", &numVertices);
    printf("Введите число рёбер: ");
    scanf("%d", &numEdges);

    int** adjacencyMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        adjacencyMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }

    printf("Введите матрицу смежности (0/1):\n");
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }

    EdgeSet* set = createEdgeSet(numEdges);
    int edgeCount = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                set->edges[edgeCount].src = i;
                set->edges[edgeCount].dest = j;
                edgeCount++;
            }
        }
    }

    qsort(set->edges, set->size, sizeof(Edge), compare);

    findArticulationPoints(set, numVertices);

    for (int i = 0; i < numVertices; ++i) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);
    
    destroyEdgeSet(set);

    return 0;
}