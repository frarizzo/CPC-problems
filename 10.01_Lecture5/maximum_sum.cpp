/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Prefix Sum.
Implementation of the code explained at lesson.
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
    int64_t N, Q;
    cin >> N >> Q;
    
    
    vector<int64_t> v;
    v.reserve(N);
    
    for(int i=0; i<N; i++){
        int n;
        cin >> n;
        v.push_back(n);
    }
    
    sort(v.begin(), v.end());
    
    vector<int64_t> q;
    q.resize(N+1,0);
    
    for(int i=0; i<Q; i++){
        int a,b;
        cin >> a >> b;
        q[a-1]++;
        q[b]--; //first element not in the querie
    }
    
    PrefixSum<int64_t>(q);
    sort(q.begin(), q.end()-1);
    
    int64_t sum = 0;
    for(int i=0; i<N; i++){
        sum += q[i] * v[i];
        
    }
    
    cout << sum << endl;
    return 0;
}

