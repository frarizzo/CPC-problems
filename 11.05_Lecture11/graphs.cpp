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

using graph = vector < vector < int > >;


void Enque(queue<int> & Q, int &v){
    Q.push_back(v);
}
int Deque(queue<int> & Q, int &v){
    int v = Q.top();
    Q.pop_front();
    
    return v;
}


//G is a adjacent list
vector<int> BFS_distance(graph & G, node &s){
    int N= G.size();
    vector<int> dist;
    vector<int> parent;
    vector<char> color;
    queue<int> Q;
    
    dist.resize(N, INFTY);
    parent.resize(N, -2);
    color.resize(N, 'w');
    
    dist[s] = 0;
    parent[s] = -1;
    color[s] = 'g';
    Enque(Q,s);
    
    
    while (!Q.empty()){
        v = Deque(Q);
        for(int i=0; i<G[v].size(); i++){
            u = G[v][i];
            if (color[u] == 'w'){ //(dist[u] == INFTY)
                dist[u] = dist[v]+1;
                parent[u] = v;
                color[u] = 'g';
                Enque(Q,u);
            }
            color[v] = 'b';
        }
    }
}


vector<int> dist;
vector<int> f;
vector<char> color;
vector<int> parent;

//G is a graph
int DFS(graph &G){
    int N = G.size(), time=0;
    
    dist.resize(N,-1);
    f.resize(N,-1);
    color.resize(N,'w');
    
    for(int i=0; i<G.size(); i++){
        vector<int> v;
        if(color[i]=='w') DFS_visit(G, i, time);
    }
}

void DFS_visit(graph &G, int u, int &time){
    time++;
    distance(u) = time;
    color(u) = 'g';
    for(int i=0; i<G.size();i++){
        if(G[u][i] != 0){
            if (color[i] == 'w'){
                parent(i) = u;
                DFS_visit(G, i, time);
            }
        }
    }
    color[u] = 'b';
    time++;
    f[u] = time;
    
}



