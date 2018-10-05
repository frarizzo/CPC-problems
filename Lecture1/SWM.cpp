/*
Francesca Rizzo
Competitive Programming and Contests
*/

/*
 Given an array v of size N we can call v(i, i+k-1) the subarray v[i]v[i+1]..v[i+1-k].
 This subarray has size k.
 Observe that if we now the maximum m of v(i, i+k-1) and the index j such as i<=j<=i+k-1 and v[j]=m, then we can easily
 find the maximum M of v(i+1, i+k) in this way:
 - if v[i+k] > m then M = v[i+k];
 - if j !=i and v[i+k] < m then M = m;
 - otherwise we have to find manually the maximum of v(i, i+k-1)
 
 So the program works in this way:
 while scanning the firt K elements of the imput it computes and print m = v(0, k-1) and memorize max(m, j).
 For K <= i < N:
 - if v[i] > m: max = (v[i],i);
 - if j = i-k: it computes the maximum m = v(i+1-k, i) and the index j and memorize max(m, j);
 - otherwise there is nothing to do
 then it prints max.first.
 */
#include<iostream>
#include <vector>

using namespace std;

void max_subK(int, int);

int main()
{
    int T;
    cin >>T;
    for(int i =0; i<T; i++){
        int N, K;
        cin >> N >>K;
        max_subK(N,K);
    }
    return 0;
}

pair<int, int> max_range(vector<int> v, int b, int e){
    pair<int, int> max = make_pair(v[b], b);
    for(int i=b+1; i<=e; i++){
        if (v[i]>max.first) max = make_pair(v[i], i);
    }
    return max;
}

void max_subK(int N, int K){
    pair<int, int> Lmax=make_pair(0,-1);
    vector<int> v;
    v.resize(N);
    
    for(int i =0; i<K; i++){
        cin >> v[i];
        if(v[i]>=Lmax.first) Lmax = make_pair(v[i], i);
    }
    cout << Lmax.first << " ";
    
    for(int i=K; i<N; i++){
        cin >> v[i];
        if(v[i] > Lmax.first) Lmax = make_pair(v[i], i);
        else if (Lmax.second == i-K)  Lmax = max_range(v,i+1-K,i);
        cout << Lmax.first << " ";
    }
    cout << endl;
}
