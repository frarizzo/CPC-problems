/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
After reading the vector v in input the program computes the sum of c.
 Using Prefix Sum it finds the first element i in which PrefixSum(v[0:i])> sum - PrefixSum(v[0:i]).
 
 Then it checks whether prefixSum-v[i]> sum - prefixSum  or not. If so, it means that when Bob finished the last n - i - 1 chocolate table, Alice hadn't finished her i-th chocolate table, so it's up to Bob to eat the last one. In this case it updates i = i-1 and prefixSum = prefixSum - v[i].
*/
#include<iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> v;
    v.reserve(N);
    
    int sum = 0;
    
    for(int i =0; i<N; i++){
        int t;
        cin >> t;
        v.push_back(t);
        sum += t;
    }
    
    int prefixSum = 0;
    int i =0;
    while ((i<N)&&(prefixSum<sum)){
        sum -= v[i];
        prefixSum += v[i];
        i++;
    }
    
    i--;
    
    if (prefixSum-v[i] > sum){
        prefixSum -= v[i];
        sum += v[i];
        i--;
    }
    
    cout << i+1 << " " << N - (i+1) << endl;
}
