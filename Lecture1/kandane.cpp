/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 Implementation of the Kandane's algorithm to find the
 contiguous sub-array with maximum sum.
 */
#include<iostream>

using namespace std;

int KandaneAlg(int);

int main()
{
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        int N;
        cin >> N;
        cout<< KandaneAlg(N) <<endl;
    }
    return 0;
}

int KandaneAlg(int N){
    int somma, max;
    cin >> somma;
    max = somma;
    for(int i=1; i<N; i++){
        int n;
        cin >> n;
        if(somma>0) somma +=n;
        else somma = n;
        
        if(somma > max) max = somma;
    }
    return max;
}
