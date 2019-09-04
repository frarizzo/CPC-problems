/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
if k-1=xN+y, then the k-th pair of the lexicographical ordered list is (a_x, a_y)
 */
#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, k;
    cin >> N >> k;
    k = k-1;
    int y = k%N;
    int x = (k-y)/N;
    
    vector<int> v;
    v.reserve(N);
    
    for(int i=0; i<N; i++){
        int n;
        cin >> n;
        v.push_back(n);
    }
    
    sort(v.begin(), v.end());
    
    cout << x << " " << y << endl;
    cout << v[x] << " " << v[y] << endl;
}


