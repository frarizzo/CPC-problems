/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Code description
*/
#include<iostream>
#include <vector>
#include <fstream>

using namespace std;

ofstream out("input.csv");

int main(){
    int N;
    cin >> N;
    
    int n;
    for(int i=0; i<N; i++){
        cin >> n;
        out << n <<endl;
    }
}
