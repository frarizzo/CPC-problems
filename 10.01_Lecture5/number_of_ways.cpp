/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Prefix sum.
Implementation of the code explained at lesson.
*/
#include<iostream>
#include <vector>
#include <iterator>

using namespace std;

//
void PrefixSumBack(vector<int64_t> &p){
    int N =p.size();
    for(int i = N-2; i>=0; i--) p[i] += p[i+1];
}


template <typename T>
vector<int64_t> SumEqualityBackwards(vector<T> &v, T sum){
    int N = v.size();
    vector<int64_t> c;
    c.resize(N, 0);
    
    int64_t s = 0;
    for(int i = N-1; i>=0; i--){
        s += v[i];
        if (s == sum) c[i] = 1;
    }
    
    return c;
}

template <typename T>
int64_t Split3_vector(vector<T> &v, T &sum){
    if (sum %3!= 0) return 0;
    
    if (sum!= 0) sum = sum/3;
    int64_t counter = 0, s = 0;
    
    vector<int64_t> c = SumEqualityBackwards(v, sum);
    
    PrefixSumBack(c);
    
    
    for(int i=0; i<v.size()-2; i++){
        s += v[i];
        if (s == sum) counter += c[i+2];
    }
    
    return counter;
}

int main(){
    int64_t N;
    cin >> N;
    
    vector<int64_t> v;
    v.reserve(N);
    
    int64_t sum = 0;
    
    for(int i =0; i<N; i++){
        int n;
        cin >> n;
        sum += n;
        v.push_back(n);
    }
    
    cout << Split3_vector<int64_t>(v, sum) << endl;
}


