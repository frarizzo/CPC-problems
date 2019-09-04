/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
While reading the input the function Tower keeps track of how many different numbers there are, of how many copies there are for each number, and of the current maximum number of copies of the same number.
 */
#include<iostream>
#include <vector>
using namespace std;

const int MAX = 1000;

pair<int, int> Towers(int);


int main()
{
    int N;
    cin >> N;
    
    pair<int,int> T = Towers(N);
    cout << T.first <<" " <<T.second<<endl;
    
    return 0;
}

pair<int, int> Towers(int N){
    //In lenght[i] there is the number of blocks of lenght i already seen (that can form a single tower)
    vector<int> lenght;
    lenght.resize(MAX, 0);
    
    //In max I keep track of the current maximum of vector lenght;
    int max = 0;
    //In num I keep the number of towers already builted;
    int num = 0;
    
    for(int i=0; i<N; i++){
        int h;
        cin >> h;
        
        //If there are other block of height h, I can unify them in the same tower
        //Otherwise, i create a new tower
        if (lenght[h] > 0) {
            lenght[h] ++;
            if (lenght[h] > max) max = lenght[h];
        } else{
            num ++;
            lenght[h] = 1;
            if (lenght[h] > max) max = lenght[h];
        }
    }
    
    return make_pair(max, num);
}

