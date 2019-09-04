/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Code description
*/
#include<iostream>
#include <vector>
#include<deque>


using namespace std;



using graph = vector < vector <int> >;

void compare(string const& o, string const& n, graph & G, vector<int> &indegree);
void topological_sort(graph &, vector<int> &);
int char_to_num(char);
char num_to_char(int);



int main(){
    int N;
    string old;
    graph G;
    G.resize(26);
    for(int i=0; i<26; i++) G[i].resize(26, 0);
    
    cin >> N;
    cin >> old;
    
    vector<int> indegree;
    indegree.resize(26, 0);
    
    for(int i=1; i<N; i++){
        string name;
        cin >> name;
        compare(old, name, G, indegree);
        old = name;
    }
    
    /*for(int i=0; i<26; i++){
        cout << num_to_char(i) << ": ";
        for(int j=0; j<26; j++){
            if (G[i][j]!= 0){
                cout << num_to_char(j) <<", ";
            }
        }
    }
    cout << endl;*/
    
    topological_sort(G, indegree);
    
}

void compare(string const& o, string const& n, graph & G, vector<int> &indegree){
    for(int i=0; (i<o.size())&&(i<n.size()); i++){
        if (o[i]!= n[i]){
            int a = char_to_num(o[i]), b = char_to_num(n[i]);
            if(G[a][b] == 0){
                indegree[b]++;
                G[a][b] = 1;
                return;
            }
        }
    }
}


int char_to_num(char ch){
    return int(ch)-int('a');
}

char num_to_char(int n){
    return char(n+int('a'));
}

vector<int> dist;
vector<int> f;
vector<char> color;


int DFS_visit(graph &G, int u, int &time, deque<int> &sort);

void topological_sort(graph &G, vector<int> &indegree){
    int N = G.size(), time=0;
    bool ris = 1;
    
    dist.resize(N,-1);
    f.resize(N,-1);
    color.resize(N,'w');
    
    deque<int> sort;
    
    for(int i=0; i<G.size(); i++){
        vector<int> v;
        if((color[i]=='w')&&(indegree[i]==0)) ris = DFS_visit(G, i,time, sort);
        /*if (!ris){
            cout << "Impossible" <<endl;
            return;
        }*/
    }
    
    for(int i=0; i<26; i++){
        if (color[i] == 'w'){
            cout << "Impossible" <<endl;
            return;
        }
    }
    
    for(int i=0; i<G.size(); i++){
        for(int j=0; j<G.size(); j++){
            if (G[j][i]!= 0){
                if ((dist[i]<dist[j])&&(f[j]<f[i])){
                    cout << num_to_char(i) << " back " << num_to_char(j) << endl;
                    cout << "Impossible" <<endl;
                    return;
                }
            }
        }
    }
    
    for(auto item: sort) cout << num_to_char(item);
    cout << endl;
}



int DFS_visit(graph &G, int u, int &time, deque<int> &sort){
    //cout << "considering " << num_to_char(u) <<endl;
    time++;
    dist[u] = time;
    color[u] = 'g';
    
    int counter = -1;
    for(int i=0; i<G.size();i++){
        if(G[u][i] != 0){
            counter = 0;
            if (color[i] == 'w'){
                //cout << num_to_char(u) << " and " << num_to_char(i) << endl;
                counter ++;
                DFS_visit(G, i, time, sort);
            }
        }
    }
    
    color[u] = 'b';
    time++;
    f[u] = time;
    sort.push_front(u);
    
    if (counter==0) return 0;
    return 1;
}


