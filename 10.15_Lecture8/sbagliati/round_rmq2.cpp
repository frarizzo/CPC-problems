/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
 Segment tree for rmq
 */
#include<iostream>
#include <vector>
#include <limits>           //numeric_limits
#include <algorithm>        //min
#include <cmath>            //log2, ceil
#include <fstream>

#define LEFT(i)    2*i + 1
#define RIGHT(i)   2*i + 2
#define PARENT(i)  (i-1)/2


using namespace std;

// NON VALE PIù//range.hi is the first one I am NOT considering
struct range{
    range(int l, int h): lo(l), hi(h)
    {}
    int lo, hi;
};

template <typename T, typename BinaryFunct>
struct type_traits{
    T invalid;
    BinaryFunct func;
};

template<typename T>
struct minimum{
    T operator()(T x, T y) {
        return std::min<T>(x, y);
    }
};

int INFTY = numeric_limits<int>::max();

type_traits<int, minimum<int> > query_t = {INFTY, minimum<int>()};



template <typename T>
void buildRMQ_ric(vector<T> &rmq, vector<T> input, range r, int pos){
    if (r.lo == r.hi){
        rmq[pos] = input[r.lo];
        return;
    }
    
    int m = (r.lo + r.hi)/2;
    buildRMQ_ric(rmq, input, {r.lo, m}, LEFT(pos));
    buildRMQ_ric(rmq, input, {m+1, r.hi}, RIGHT(pos));
    rmq[pos] = query_t.func(rmq[LEFT(pos)], rmq[RIGHT(pos)]);

}

template <typename T>
void update(vector<T> &rmq, range const& q, range segment, T const val, int pos){
    //no overlap
    if ((q.lo >= segment.hi)||(q.hi <= segment.lo)) return;
    
    //leaf
    if (segment.lo == segment.hi){
        rmq[pos] += val;
        return;
    }
    
    int m = (segment.lo + segment.hi)/2;
    
    update(rmq, q, {segment.lo, m}, val, LEFT(pos));
    update(rmq, q, {m+1, segment.hi}, val, RIGHT(pos));
    rmq[pos] = query_t.func(rmq[LEFT(pos)],rmq[RIGHT(pos)]);
    return;
}

template <typename T>
void lazy_update(vector<T> &rmq, vector<T> &lazy, range const& q, range segment, T const val, int pos){
    //if lazy[pos] != 0, updatre rmq[pos]
    if (lazy[pos] != 0){
        rmq[pos] += lazy[pos];
        lazy[LEFT(pos)] += lazy[pos];
        lazy[RIGHT(pos)] += lazy[pos];
        lazy[pos] = 0;
    }
    
    //no overlap
    if ((q.lo > segment.hi)||(q.hi < segment.lo)) return;
    
    //total overlap
    if((q.lo <= segment.lo)&&(q.hi >= segment.hi)){
        //update rmq[pos]
        rmq[pos] +=val;
        //update lazy[LEFT(pos)], lazy[RIGHT(pos)]
        lazy[LEFT(pos)] += val;
        lazy[RIGHT(pos)] += val;
        return;
    }
    
    int m = (segment.lo + segment.hi)/2;
    update(rmq, q, {segment.lo, m}, val, LEFT(pos));
    update(rmq, q, {m+1, segment.hi}, val, RIGHT(pos));
    rmq[pos] = query_t.func(rmq[LEFT(pos)],rmq[RIGHT(pos)]);
    return;
}

template <typename T>
T findMin(vector<T> &rmq, range const& q, range segment, int pos){
    //total overlap
    if ((q.lo <= segment.lo)&&(q.hi >= segment.hi)) return rmq[pos];
    
    //no overlap
    if ((q.hi< segment.lo)||(q.lo > segment.hi)) return query_t.invalid;
    
    //partial overlap
    int m = (segment.lo + segment.hi)/2;
    return query_t.func(findMin(rmq, q, {segment.lo, m}, LEFT(pos)), findMin(rmq, q, {m+1, segment.hi}, RIGHT(pos)));
}

template <typename T>
T lazy_findMin(vector<T> &rmq, vector<T> &lazy, range const& q, range segment, int pos){
    //if lazy[pos] != 0, updatre rmq[pos]
    if (lazy[pos] != 0){
        rmq[pos] += lazy[pos];
        lazy[LEFT(pos)] += lazy[pos];
        lazy[RIGHT(pos)] += lazy[pos];
        lazy[pos] = 0;
    }
    
    //total overlap
    if ((q.lo <= segment.lo)&&(q.hi >= segment.hi)) {
        return rmq[pos];
    }
    
    //no overlap
    if ((q.hi< segment.lo)||(q.lo > segment.hi)) return query_t.invalid;
    
    //partial overlap
    int m = (segment.lo + segment.hi)/2;
    return query_t.func(lazy_findMin(rmq, lazy, q, {segment.lo, m}, LEFT(pos)), lazy_findMin(rmq,lazy, q, {m+1, segment.hi}, RIGHT(pos)));
}

void linear_code(){
    int val, M;
    cin >> val;
    
    cin >> M;
    for(int i=0; i<M; i++){
        int n;
        char temp = ' ';
        vector<int> input;
        while (temp != '\n'){
            scanf("%d%c", &n, &temp);
            input.push_back(n);
        }
        if (input.size() == 2){
            cout << val << endl;
        }
        else if (input.size() == 3){
            val += input[2];
        }
    }
}

int main(){
    size_t N, M;
    cin >> N;
    
    if (N == 1) {
        linear_code();
        return 0;
    }
    
    vector<int64_t> input;
    for(int i=0; i<N; i++){
        int64_t n;
        cin >> n;
        input.push_back(n);
    }
    
    vector<int64_t> rmq;
    rmq.resize(2*N-1);
    buildRMQ_ric<int64_t>(rmq, input, {0, N}, 0);
    
    vector<int64_t>().swap(input);
    
    vector<int64_t> lazy;
    lazy.resize(2*N -1 , 0);
    
    
    cin >> M;
    for(int i=0; i<M; i++){
        int n;
        char temp = ' ';
        vector<int> input;
        while (temp != '\n'){
            scanf("%d%c", &n, &temp);
            input.push_back(n);
        }
        if (input.size() == 2){
            //segments are circular
            if (input[0]<= input[1]){
                cout << lazy_findMin<int64_t>(rmq, lazy, {input[0], input[1]}, {0, N-1}, 0)<< endl;
            } else {
                int m1 = lazy_findMin<int64_t>(rmq, lazy, {input[0], N-1}, {0, N-1}, 0);
                int m2 = lazy_findMin<int64_t>(rmq, lazy, {0, input[1]}, {0, N-1}, 0);
                cout << min (m1, m2) <<endl;
            }
        }
        else if (input.size() == 3){
            //segments are circular
            if (input[0]<= input[1]){
                lazy_update<int64_t>(rmq, lazy, {input[0], input[1]}, {0, N-1}, input[2], 0);
            } else {
                lazy_update<int64_t>(rmq, lazy, {input[0], N-1}, {0, N-1}, input[2], 0);
                lazy_update<int64_t>(rmq, lazy, {0, input[1]}, {0, N-1}, input[2], 0);
            }
        }
    }
}



