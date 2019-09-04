/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 The program reads the string of number s, then decode the string and uses counting sort to order a vector whit the same digit as the imput number.
 While decoding digits from the string, it keeps track of the smallest even number in the number.
*/
#include<iostream>
#include <vector>

using namespace std;

vector<int> LEN(string &);

template <typename T>
void Print(vector<T> &v){
    if (v.empty()) return;
    for(int i=0; i<v.size(); i++){
        cout << v[i];
    }
    cout << endl;
}

int main(){
    int T;
    
    cin >>T;
    for(int i=0; i<T; i++){
        string s;
        cin >> s;
        vector<int> v = LEN(s);
        Print(v);
    }
    return 0;
}


int counting_sort(string &s, vector<int>& c){
    int min_even = 10;
    for(int i=0; i<s.size(); i++){
        int digit = s[i] -'0'; //digits are consecutive
        c[digit]++;
        if((digit%2==0)&&(digit<min_even)) min_even = digit;
    }
    return min_even;
}

vector<int> LEN(string & s){
    //vector c will store in c[i] the number of digits equal to i in N
    vector<int> c;
    c.resize(10, 0);
    //min_even will store the smallest even digit
    int min_ev = counting_sort(s,c);
    
    int last = 0;
    if (min_ev != 10){
        c[min_ev] --;
        last = 1;
    }
    
    vector<int> v;
    for(int i=9; i>=0; i--){
        if (c[i] != 0){
            for(int j=0; j<c[i]; j++){
                v.push_back(i);
            }
        }
    }
    if (last) v.push_back(min_ev);
    
    return v;
}
