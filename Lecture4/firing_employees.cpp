/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
The program keep an implicite tree-structure in an array where in v[i] there is a list of subordinates of i
Then, starting form the root, find recursively and for all sub tree the number of emplyees in the black list (the recursive method let me know the distance of the employee from the root which is the number of his seniors).
*/
#include<iostream>
#include <vector>

using namespace std;

int firing_employees(int);

int main(){
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        int N;
        cin >> N;
        cout << firing_employees(N) << endl;;
    }
}

int prime(int h, int r){
    //(*) to check whether the sum of rank + number of seniors is prime I need to fix the off by 1 on the rank
    int n = h + r+1;
    if (n==2) return 1;
    if(n%2==0) return 0;
    int i=3;
    while (i*i<=n){
        if (n%i==0) return 0;
        i+=2;
    }
    return 1;
}

int SearchPrimeRec(vector < vector < int > > & v, int root, int h){
    if (v[root].empty()) return 0;
    int ris = 0;
    for(int j=0; j<v[root].size(); j++){
        if (prime(h,v[root][j])) ris++;
        ris += SearchPrimeRec(v, v[root][j], h+1);
    }
    return ris;
}

int firing_employees(int N){
    vector< vector < int > > v;
    v.resize(N);
    int mr_alfred;
    //I put in v[i] the (i-1)'s immediate subordinate's rank minus 1 (i is the immediate senior of v[i])
    for(int i=0;i<N; i++){
        int senior;
        cin >> senior;
        if (senior == 0) mr_alfred = i;
        else v[senior-1].push_back(i);
    }
    
    //There is an off by 1 on all ranks (I am using 0....n-1) (*)
    return SearchPrimeRec(v, mr_alfred, 1);
}
