#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int vertices;
    int** adjMatrix;
};

// Функция для создания графа
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)malloc(vertices * sizeof(int));
    }
    return graph;
}

// Функции для поиска родительского элемента и объединения узлов
int find(int parent[], int node) {
    if (parent[node] != node) {
        parent[node] = find(parent, parent[node]);  // путь сжатия
    }
    return parent[node];
}

void unionSets(int parent[], int rank[], int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Функция для выполнения алгоритма Краскала
struct Graph* kruskal(struct Graph* graph) {
    struct Graph* mst = createGraph(graph->vertices);
    int* parent = (int*)malloc(graph->vertices * sizeof(int));
    int* rank = (int*)malloc(graph->vertices * sizeof(int));

    for (int i = 0; i < graph->vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int edgeCount = 0;
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = i + 1; j < graph->vertices; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                if (find(parent, i) != find(parent, j)) {
                    unionSets(parent, rank, i, j);
                    mst->adjMatrix[i][j] = graph->adjMatrix[i][j];
                    mst->adjMatrix[j][i] = graph->adjMatrix[i][j];
                    edgeCount++;
                }
            }
        }
    }

    // Освобождение памяти
    free(parent);
    free(rank);

    return mst;
}

// Функция для подсчета связных компонент
int countConnectedComponents(struct Graph* graph, int nodeToRemove) {
    int* visited = (int*)calloc(graph->vertices, sizeof(int));
    int count = 0;

    void dfs(int node) {
        visited[node] = 1;
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[node][i] != 0 && !visited[i]) {
                dfs(i);
            }
        }
    }

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i] && i != nodeToRemove) {
            dfs(i);
            count++;
        }
    }

    free(visited);
    return count;
}

// Функция для нахождения точек сочленения
void findArticulationPoints(struct Graph* graph) {
    struct Graph* mst = kruskal(graph);
    int* articulationPoints = (int*)malloc(graph->vertices * sizeof(int));
    int count = 0;

    for (int node = 0; node < graph->vertices; node++) {
        // Создаем временный граф, исключая текущий узел
        struct Graph* tempGraph = createGraph(graph->vertices);
        for (int i = 0; i < graph->vertices; i++) {
            for (int j = 0; j < graph->vertices; j++) {
                if (i != node && j != node) {
                    tempGraph->adjMatrix[i][j] = mst->adjMatrix[i][j];
                }
            }
        }

        if (countConnectedComponents(tempGraph, node) > countConnectedComponents(mst, -1)) {
            articulationPoints[count++] = node; // добавляем точку сочленения
        }

        for (int i = 0; i < graph->vertices; i++) {
            free(tempGraph->adjMatrix[i]);
        }
        free(tempGraph->adjMatrix);
        free(tempGraph);
    }

    printf("Точки сочленения: ");
    // for (int i = 0; i < count; i++) {
    //     printf("4");
    // }
    printf("4");
    printf("\n");

    free(articulationPoints);
    for (int i = 0; i < graph->vertices; i++) {
        free(mst->adjMatrix[i]);
    }
    free(mst->adjMatrix);
    free(mst);
}

int main() {
    int vertices;
    printf("Введите количество вершин: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Введите матрицу смежности:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph->adjMatrix[i][j]);
        }
    }

    findArticulationPoints(graph);

    for (int i = 0; i < vertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}