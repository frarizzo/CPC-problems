/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 Given the input array, the program lists
 the array backwards and saves a number iff it is greater
 than the actual maximum (at the beginning the maximum is the rightest element).
 Then it prints the saved numbers backwards.
 */
#include<iostream>
#include <vector>
using namespace std;

void PrintLeaders(int, vector<int> &);

int main()
{
    int T;
    cin >> T;
    for(int i=0; i<T; i++) {
        int N;
        cin >> N;
        vector<int> v;
        v.resize(N);
        for(int i=0; i<N; i++) cin >> v[i];
        
        PrintLeaders(N, v);
        v.clear();
    }
    return 0;
}

void ReversePrint(vector<int> &v){
    if (v.empty()) return;
    for(int i=v.size()-1; i>=1; i--) cout << v[i] << " ";
    cout << v[0] << endl;
}

void PrintLeaders(int N, vector<int> &v){
    vector<int> sol;
    
    sol.push_back(v[N-1]);
    for(int i=N-2; i>=0; i--) {
        if(v[i]>=sol[sol.size()-1]) sol.push_back(v[i]);
    }
    ReversePrint(sol);
}

