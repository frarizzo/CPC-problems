/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
[I implemented this algorithm to solve Next Larger Element problem following the hint to use double end queue given at lesson]
 NLE function takes in input an array of elements and uses a duouble end queue to keep track of the index of the elements for which O haven't find the NLE yet, and store the NLE finded in an array.
For all indexes i form 0 to array.size() it does:
 - read element v[i]
 - remove from the back of the queue all indexes of elements smaller than v[i]: since they haven't been removed yet, their NLE is v[i] (and it adds this information to the solution array).
 - insert the index i in the back of the queue.
 */
#include<iostream>
#include <vector>
#include <deque>

using namespace std;

vector<int> NLE(vector<int>&);
template <typename T>
void Print(vector<T> &v){
    if (v.empty()) return;
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main()
{
    int T;
    cin >>T;
    for(int i =0; i<T; i++){
        int N, K;
        vector<int> v;
        
        cin >> N;
        
        for(int i =0; i<N; i++){
            int n;
            cin >> n;
            v.push_back(n);
        }
        vector<int> r = NLE(v);
        Print<int>(r);
    }
    return 0;
}

vector<int> NLE(vector<int> &v){
    int N = v.size();
    //Q is to stores indexes (that refers to vector v): it keeps the max element I find
    deque<int> Q;
    vector<int> NLE;
    NLE.resize(N, -1);
    
    for(int i=0; i<N; i++){
        // remove from the back of the queue all the elements j whose NLE is v[i] and puts NLE[j] = v[i]
        while(!(Q.empty())&&(v[Q.back()]<=v[i])) {
            NLE[Q.back()] = v[i];
            Q.pop_back();
        }
        
        //insert the index i in the back
        Q.push_back(i);
        
    }
    return NLE;
}


