/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 The program sort the couples (i,j) by a_{i,j} (using a priority queue).
 
 Then it selects pair (i,j) starting from the strongest:
 - if i or j has already in a team, the couple is rejected;
 - otherwise the team (i,j) is formed
 
*/
#include<iostream>
#include <vector>
#include <queue>

using namespace std;


template <typename T>
void Print(vector<T> &v){
    if (v.empty()) return;
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(){
    priority_queue < pair < int, pair <int,int> > > PQ;
    vector <int> v;
    int N;
    cin >> N;
    v.resize(2*N, -1);
    for(int i=1; i<2*N; i++){
        for(int j=0; j<i; j++){
            pair <int, int> c = make_pair(i,j);
            int a;
            cin >> a;
            PQ.push(make_pair(a, c));
        }
    }
    
    while (!PQ.empty()){
        pair <int, int> c = PQ.top().second;
        int a = c.first;
        int b = c.second;
        PQ.pop();
        while ((!PQ.empty())&&((v[a]!=-1)||(v[b]!=-1))){
            c =PQ.top().second;
            a = c.first;
            b = c.second;
            PQ.pop();
        }
        if ((v[a]==-1)&&(v[b]==-1)){
            v[a] = b+1;
            v[b] = a+1;
        }
    }
    Print(v);
    return 0;
}
