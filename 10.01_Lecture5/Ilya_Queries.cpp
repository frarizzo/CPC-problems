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

using namespace std;

template <typename T>
vector<int> Equality(T &s){
    vector<int> v;
    for(int i=0; i<s.size()-1; i++){
        if (s[i]==s[i+1]) v.push_back(1);
        else v.push_back(0);
    }
    return v;
}

void PrefixSum(vector<int> &v){
    
    for(int i=1; i<v.size(); i++){
        v[i] = v[i-1] + v[i];
    }
}


int main(){
    string s;
    cin >> s;
    
    vector<int> v = Equality(s);
    PrefixSum(v);
    
   
    int Q;
    cin >> Q;
    for(int i=0; i<Q; i++){
        int l, r;
        cin >> l >> r;
        int sol = v[r-2];
        sol -= (l>1) ? v[l-2] : 0 ;
        cout << sol <<endl;
    }
    
    return 0;
}
