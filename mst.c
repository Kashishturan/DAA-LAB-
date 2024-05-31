#include <stdio.h>
#include <stdlib.h>

// Function to compare edges for sorting
int comparator(const void* p1, const void* p2) {
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

// Function to initialize disjoint set
void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Function to find the parent of a component in the disjoint set
int findParent(int parent[], int component) {
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

// Function to perform union operation in the disjoint set
void unionSet(int u, int v, int parent[], int rank[], int n) {
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

// Function to perform Depth-First Search (DFS) traversal
void DFS(int n, int matrix[n][n], int visited[], int start, int end) {
    printf("%d", start);
    visited[start] = 1;

    if (start == end) {
        printf("\n");
        return;
    }

    printf(" -> ");

    for (int i = 0; i < n; i++) {
        if (matrix[start][i] != 0 && !visited[i]) {
            DFS(n, matrix, visited, i, end);
            if (visited[end]) {
                return; // Stop the DFS if the destination is reached
            }
        }
    }
}

// Function to find the Minimum Spanning Tree (MST) using Kruskal's algorithm
void kruskalAlgoWithPath(int n, int matrix[n][n], int start, int end) {
    // Convert the adjacency matrix to an edge list
    int edgeCount = 0;
    int edge[n * n][3];

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != 0) {
                edge[edgeCount][0] = i;
                edge[edgeCount][1] = j;
                edge[edgeCount][2] = matrix[i][j];
                edgeCount++;
            }
        }
    }

    // Sort the edge list
    qsort(edge, edgeCount, sizeof(edge[0]), comparator);

    int parent[n];
    int rank[n];

    makeSet(parent, rank, n);

    int minCost = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < edgeCount; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);

    // Initialize the visited array for DFS
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Perform DFS from start to end
    printf("Path from %d to %d in MST:\n", start, end);
    DFS(n, matrix, visited, start, end);
}

// Function to read the adjacency matrix from a file
void readAdjacencyMatrix(int n, int matrix[n][n]) {
    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        perror("Error opening the file for reading.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
}

int main() {
    int n;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int matrix[n][n];

    readAdjacencyMatrix(n, matrix);

    // Specify the two vertices for which you want to find the path
    int start, end;
    printf("Enter the start vertex: ");
    scanf("%d", &start);
    printf("Enter the end vertex: ");
    scanf("%d", &end);

    // Call the function to find and print the path between the specified vertices in the MST
    kruskalAlgoWithPath(n, matrix, start, end);

    return 0;
}