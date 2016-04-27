// #include <iostream>
// #include <vector>

// using namespace std;

// A C / C++ program for Dijkstra's single source shortest
// path algorithm. The program is for adjacency matrix
// representation of the graph.
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <vector> 
using namespace std;
// Number of vertices in the graph
#define V 25
#define height 5
#define width 5

#define NORTH(pt)(pt-width)
#define VALID_NORTH(pt) (NORTH(pt) <= 0)
#define SOUTH(pt)(pt-width)
#define VALID_SOUTH(pt) (SOUTH(pt) > (V-1) )

 
// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j]==-1)
        return;
 
    printPath(parent, parent[j]);
 
    printf("%d ", j);
}
 
// A utility function to print the constructed distance
// array
int printSolution(int dist[], int n, int parent[])
{
    int src = 0;
    printf("Vertex\t\t\t  Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}
 
// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];
 
    // Parent array to store shortest path tree
    int parent[V];
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
 
    // print the constructed distance array
    printSolution(dist, V, parent);
}

int main() {
    const int h = 5; const int w = 5;
	int a[V][V] = {0};

    for (int row = 0; row < V-2 ; ++row){
        //set north
        a[row][row-width] = (row-width > 0) ? 1 : 0;

        //set south
        a[row][row+width] = (row+width < V-1 ) ? 1 : 0;
        
        //set east
        a[row][row+1] = ( ((row+1)%width !=0 ) && (row+1<V-2) ) ? 1 : 0;

        //set west 
        a[row][row-1] = ( (row-1 > 0) && ( row%width != 0) ) ? 1 : 0;

        //set north-east
        a[row][row-width+1] = ( (row-width > 0) && ((row+1)%width !=0 ) && (row+1<V-2) ) ? 2 : 0;

        //set north-west
        a[row][row-width-1] = ( (row-width > 0) && (row-1 > 0) && ( row%width != 0) ) ? 2 : 0;

        //set south-east
        a[row][row+width+1] = ( (row+width < V-1 ) && ((row+1)%width !=0 ) && (row+1<V-2) ) ? 2 : 0;

        //set south-west
        a[row][row+width-1] = ( (row+width < V-1 ) &&  (row-1 > 0) && ( row%width != 0) )? 2 : 0;
    }
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++){
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
    dijkstra(a, 0);
 	cout << endl;
    return 0;
}