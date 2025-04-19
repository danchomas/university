import heapq

def kruskal(graph):
    """Находит минимальное остовное дерево с помощью алгоритма Краскала."""
    parent = {node: node for node in graph}
    rank = {node: 0 for node in graph}
    edges = []
    for u in graph:
        for v, weight in graph[u]:
            edges.append((weight, u, v))
    heapq.heapify(edges)
    mst = []
    total_weight = 0
    def find(i):
        if parent[i] == i:
            return i
        parent[i] = find(parent[i])
        return parent[i]
    def union(i, j):
        root_i = find(i)
        root_j = find(j)
        if root_i != root_j:
            if rank[root_i] < rank[root_j]:
                parent[root_i] = root_j
            elif rank[root_i] > rank[root_j]:
                parent[root_j] = root_i
            else:
                parent[root_j] = root_i
                rank[root_i] += 1
            return True
        return False
    for weight, u, v in edges:
        if union(u, v):
            mst.append((u, v, weight))
            total_weight += weight
    return mst


def find_articulation_points_indirect(graph):
    """Находит точки сочленения косвенным методом с использованием Краскала."""
    mst = kruskal(graph)
    articulation_points = set()
    mst_graph = {node: [] for node in graph}
    for u, v, w in mst:
        mst_graph[u].append(v)
        mst_graph[v].append(u)

    def count_connected_components(g):
        visited = set()
        count = 0
        def dfs(node):
            visited.add(node)
            for neighbor in g.get(node, []):
                if neighbor not in visited:
                    dfs(neighbor)
        for node in g:
            if node not in visited:
                dfs(node)
                count += 1
        return count

    for node in graph:
        temp_graph = {k: v[:] for k, v in mst_graph.items() if k != node}  #Создаем копию, удаляя узел
        for u in list(temp_graph): #удаляем все ребра, смежные с удаленным узлом
            if node in temp_graph[u]:
                temp_graph[u].remove(node)

        if count_connected_components(temp_graph) > count_connected_components(mst_graph):
            articulation_points.add(node)

    return list(articulation_points)


# Пример использования:
graph = {
    'A': [('B', 1), ('C', 3)],
    'B': [('A', 1), ('C', 1), ('D', 5)],
    'C': [('A', 3), ('B', 1), ('D', 2)],
    'D': [('B', 5), ('C', 2), ('E', 4)],
    'E': [('D', 4)]
}

articulation_points = find_articulation_points_indirect(graph)
print("Точки сочленения:", articulation_points)

