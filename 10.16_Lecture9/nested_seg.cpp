/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Implementation of the code explained at lesson
*/
#include<iostream>
#include <vector>

using namespace std;

int main(){
    int S;
    cin >> S;
    
    priority_queue<pair<int, int> > pq;
    
    for(int i =0; i<S; i++){
        int l, r,
        cin >> l >> r;
        pq.push_back(make_pair(l,r));
    }
    
    while (!pq.empty()){
        
    }
}
