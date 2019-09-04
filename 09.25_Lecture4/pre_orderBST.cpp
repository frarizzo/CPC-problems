/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 The program check if the input could be a ore order traversal of a BST tree.
 
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

