/*
Francesca Rizzo
Competitive Programming and Contests
*/

/*
 To find the only missing number the function solveMissing calcolates
 the difference between the sum of the numbers from 1 to N
 and the sum of the numbers in input.
 */

#include<iostream>
using namespace std;

int solveMissing(int);

int main()
{
    int T;
    cin >> T;
    
    for(int i=0; i<T; i++) {
        int N;
        cin >> N;
        cout << solveMissing(N) <<endl;
    }
    return 0;
}

int solveMissing(int N){
    int tot = (N*(N+1))/2;
    int somma = 0;
    for(int i = 1; i<N; i++){
        int j;
        cin >> j;
        somma += j;
    }
    return tot - somma;
}
