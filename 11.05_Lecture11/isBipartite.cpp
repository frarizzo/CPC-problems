/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Code description
*/
#include<iostream>
#include <vector>

using namespace std;

using graph = vector < vector <bool > >;

int isBipartite(int );
int DFS_trees(graph &);

int main(){
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        int N;
        cin >> N;
        cout << isBipartite(N) << endl;
    }
}

int isBipartite(int N){
    graph G;
    G.resize(N);
    for(int i=0; i<N; i++){
        G.reserve(N);
        for(int j=0;j<N; j++){
            bool b;
            cin >> b;
            if (b) G[i].push_back(j);
            //G[i][j] = b;
        }
    }
    if (DFS_trees(G) == 2) return 1;
    return 0;
}

void DFS_visit(graph &, int, vector<bool> &);

//G is a adjacent list
int DFS_trees(graph & G){
    int N = G.size();
    vector<bool> visited;
    
    visited.resize(N, 0);
    
    int trees = 0;
    
    for(int i=0; i<N; i++){
        if (visited[i] == 0){
            trees ++;
            DFS_visit(G, i, visited);
        }
    }
    
    return trees;
}

void DFS_visit(graph &G, int v, vector<bool> &visited){
    visited[v] = 1;
    if (G[v].size() == 0) return;
    for(int i=0; i<G[v].size(); i++){
        if (visited[i] == 0){
            DFS_visit(G, i, visited);
        }
    }
    return;
}



