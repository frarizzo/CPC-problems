/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Given the array with the height of the block,
the algorithm compute the quantity of trapped water.
 */
#include<iostream>

using namespace std;

int TrapedWater(int);

int main()
{
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        int N;
        cin >> N;
        cout<< TrapedWater(N) <<endl;
    }
    return 0;
}

int TrapedWater(int N){
    int max, w;
    cin >> max;
    w = 0;
    for(int i=1; i<N; i++){
        int h;
        cin >> h;
        if (h<max) w += max -h;
        else max = h;
    }
    return w;
}
