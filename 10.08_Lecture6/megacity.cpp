/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Using a priority queue the program sorts the cities by distance.
Then it increase the raidius untill the popolation reach 10e6.
*/
#include<iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <queue>



using namespace std;
using pq_pair = priority_queue < pair <double, int> >  ;

const int M=1000000;

int main(){
    int N, s;
    cin >> N >> s;
    
// vector < pair<int, int > > pos;
    pq_pair DIST;
    
    for(int i =0; i<N;i++){
        int x, y, k;
        cin >> x >> y >> k;
        double d = sqrt(x*x+y*y);
        DIST.push(make_pair(-d, k));
    }
    
    int left = M - s;
    double radius = 0;
    while (left > 0){
        if (DIST.empty()){
            cout << -1 <<endl;
            return 0;
        }
        radius = - DIST.top().first;
        left -= DIST.top().second;
        DIST.pop();
    }
    
    cout.precision(8);
    cout << radius << endl;
}
