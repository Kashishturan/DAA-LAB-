6#include <stdio.h>
#include <stdlib.h>

int comparator(const void* p1, const void* p2)
{
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[], int n, int parentInfo[][2])
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
        parentInfo[v][0] = u;
        parentInfo[v][1] = rank[u];
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
        parentInfo[u][0] = v;
        parentInfo[u][1] = rank[v];
    }
    else {
        parent[v] = u;
        rank[u]++;
        parentInfo[v][0] = u;
        parentInfo[v][1] = rank[u];
    }
}

// Function to perform Depth-First Search (DFS) traversal and print the path
void printPath(int n, int matrix[n][n], int start, int end, int parentInfo[][2])
{
    if (start == end) {
        printf("%d ", start);
        return;
    }

    printPath(n, matrix, start, parentInfo[end][0], parentInfo);
    printf("%d ", end);
}

// Function to find the Minimum Spanning Tree (MST) using Kruskal's algorithm
void kruskalAlgo(int n, int matrix[n][n])
{
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

    // Parent information to store the MST structure
    int parentInfo[n][2];

    // Initialize the parentInfo array
    for (int i = 0; i < n; i++) {
        parentInfo[i][0] = -1;  // Parent
        parentInfo[i][1] = 0;   // Rank
    }

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < edgeCount; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n, parentInfo);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);

    // Perform DFS to find the path from vertex 0 to vertex 5 in the MST
    int start = 0;
    int end = 5;

    // Call the DFS function
    printf("Path from %d to %d in MST: ", start, end);
    printPath(n, matrix, start, end, parentInfo);
    printf("\n");
}

// Function to read the adjacency matrix from a file
void readAdjacencyMatrix(int n, int matrix[n][n])
{
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

int main()
{
    int n;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int matrix[n][n];

    readAdjacencyMatrix(n, matrix);

    // Call the Kruskal's algorithm with user input to find the shortest path
    kruskalAlgo(n, matrix);

    return 0;
}
