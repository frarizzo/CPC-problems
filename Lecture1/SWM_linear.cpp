/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 Implementation of the linear time solution for sliding window maximum problem shown at lesson.
 */
#include<iostream>
#include <vector>
#include <deque>

using namespace std;

vector<int> SWM(vector<int>&, int);
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
        
        cin >> N >> K;
        
        for(int i =0; i<N; i++){
            int n;
            cin >> n;
            v.push_back(n);
        }
        vector<int> r = SWM(v,K);
        Print<int>(r);
    }
    return 0;
}

vector<int> SWM(vector<int> &v, int K){
    int N = v.size();
    //Q is to stores indexes (that refers to vector v)
    deque<int> Q;
    vector<int> maxs;
    
    for(int i=0; i<N; i++){
        
        
        //remove from the front of the queue element that are no longer in the window
        while ((!Q.empty())&&(Q.front()<=i-K)) Q.pop_front();
        
        // remove from the back of the queue unuseful elements (all the elements that are smaller than or equal to v[i])
        while(!(Q.empty())&&(v[Q.back()]<=v[i])) Q.pop_back();
        
        //insert the index i in the back
        Q.push_back(i);        
        
        if (i >= K-1) maxs.push_back(v[Q.front()]);
    }
    return maxs;
}

