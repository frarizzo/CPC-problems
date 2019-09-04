/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 The program check if the input could be a ore order traversal of a BST tree.
 
 [I implemented the code following the given solution]
 While reading the input, we want to mantain the invariant of being in a right subtree.
 At the beginning our tree root is $-\infty$, then very time we read a new number $n$ :
 - if $n<root$ the tree cannot be a BST (because we in the right subtree), so we return 0
 - else it can be a BST: if the new elements is smaller that the elements read before, we keep him as the next greater of the root (so it is in a right subtree), else we need to update the root with the father of $n$.
 */

/*
 IN REALTÀ NON MI TORNA QUESTO PROGRAMMA:
 1
 4
 40 30 70 35 risponde 1 
 */


#include<iostream>
#include <vector>
#include <stack>
#include <climits>


using namespace std;

int pre_order(int);

int main(){
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        int N;
        cin >> N;
        cout << pre_order(N) << endl;;
    }
}

int pre_order(int N){
    int r = INT_MIN, n;
    stack<int> s;
    
    for (int i =0; i<N; i++){
        cin >> n;
        
        if (n< r) return 0;
        
        while (!s.empty()){
            if (n < s.top()) s.pop();
            else{
                r = s.top();
                break;
            }
        }
        
        s.push(n);
    }
    return 1;
}
*/
