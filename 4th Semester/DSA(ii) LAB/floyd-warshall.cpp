#include <iostream>
#define INF 99999

using namespace std;

int main(){
    int n, e; // n = number of nodes, e = number of edges

    cout << "Number of Nodes: ";
    cin >> n;

    int graph[n][n]; // Creating the graph as 2D array

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            graph[i][j] = (i==j)?0:INF;

    cout << "Number of Edges: ";
    cin >> e;
    for(int i=0;i<e;i++){
        // u = First node, v = second node, w = weight
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = graph[v][u] = w;
    }

    // Here k is the intermediate node
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                graph[i][j] = min(graph[i][j],
                            graph[i][k]+graph[k][j]);
            }
        }
    }

    cout << "Shortes Path Matrix: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

}
