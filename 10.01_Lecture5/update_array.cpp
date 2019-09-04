/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*

 */
#include<iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T>
void PrefixSum(vector<T> &v){
    for(int i=1; i<v.size(); i++){
        v[i] += v[i-1];
    }
}

int main(){
    int T;
    cin >> T;
    
    for(int i=0; i<T; i++){
        int N, U;
        cin >> N >> U;
        
        vector<int64_t> v;
        v.resize(N,0);
        
        for(int i=0; i<U; i++){
            int l, r, u;
            cin >> l >> r >> u;
            v[l] += u;
            v[r+1] -= u; //first element i don't update
        }
        
        PrefixSum<int64_t>(v);
        
        int Q;
        cin >> Q;
        for(int i=0; i<Q; i++){
            int q;
            cin >> q;
            cout << v[q] <<endl;
        }
    }
    
    
    
    return 0;
}


