/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Implementetion of the variant of merge sort that finds all the inversions of an array explained at lesson.
*/
#include <vector>
#include <iostream>

using namespace std;

int MS(vector<int> &, int , int );

int main(){
    int T;
    
    cin >> T;
    for (int t=0; t<T; t++){
        int N;
        vector<int> a;
        cin >> N;
        for (int i=0; i<N; i++){
            int n;
            cin >> n;
            a.push_back(n);
        }
        cout << MS(a, 0, a.size()-1) << endl;
    }
}

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}


void copy(vector<int> b, vector<int>& a, int f, int t){
    for(int i=f; i<=t; i++){
        a[i] = b[i-f];
    }
}

long long int M(vector<int>& a, int f, int t, int m){
    long long int inv = 0;
    int i = f, j=m+1;
    vector  <int> b;
    //while merging, it counts the number of inversion at this level
    while ((i<=m)&&(j<=t)){
        if (a[i]<=a[j]){
            b.push_back(a[i]);
            i++;
        } else{
            inv = inv + (m + 1 - i );
            b.push_back(a[j]);
            j++;
        };
    }
    
    while (i<= m){
        b.push_back(a[i]);
        i++;
    }
    while (j<=t){
        b.push_back(a[j]);
        j++;
    }
    copy(b, a, f, t);
    
    return inv;
}

int MS(vector<int> &a, int f, int t){
    if(t > f){
        int m = (t + f )/2;
        return MS(a,f, m) + MS(a,m+1,t) + M(a, f, t, m);
    }
    
    else return 0;
}
