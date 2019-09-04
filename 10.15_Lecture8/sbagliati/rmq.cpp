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



#define LEFT(i)    2*i + 1
#define RIGHT(i)   2*i + 2
#define PARENT(i)  (i-1)/2


using namespace std;

//range.hi is the first one I am NOT considering
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
vector<T> builtRMQ_implicit(int N){
    vector<T> rmq_tree;
    rmq_tree.resize(2*N-1, query_t.invalid);
    
    int h = ceil(log2(N));
    //Exempt for the last level, the three is full so the parent of the first leaf (starting from the left) has index 2^{h-1} - 1.
    int p =(1<<(h-1))-1;
    int first_leaf = LEFT(p);
    
    //read input int two times (first go forward, then return back)
    for(int j = first_leaf; j<2*N-1; j++){
        T n;
        cin >> n;
        rmq_tree[j] = n;
    }
        //I have to store N - (2N-1-first_leaft) numbers, so I start from
        //start = first_leaf - N - (2N-1-first_leaft) = N-1
    int start = N-1;
    for(int j = 0; j < first_leaf-start; j++){
        T n;
        cin >> n;
        rmq_tree[start + j] = n;
    }
    
    //fill with minimum
    for(int i=2*N-2; i>0; i-=2) rmq_tree[PARENT(i)] = min(rmq_tree[i], rmq_tree[i-1]);
    
    return rmq_tree;
}

template <typename T>
void update(vector<T> &rmq, range const& q, range segment, T const val, int pos){
    //no overlap
    if ((q.lo >= segment.hi)||(q.hi <= segment.lo)) return;
    
    //leaf
    if (segment.lo == segment.hi - 1){
        rmq[pos] += val;
        return;
    }
    
    int m = (segment.lo + segment.hi+1)/2;
    
    update(rmq, q, {segment.lo, m}, val, LEFT(pos));
    update(rmq, q, {m, segment.hi}, val, RIGHT(pos));
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
    if ((q.lo >= segment.hi)||(q.hi <= segment.lo)) return;
    
    //total overlap
    if((q.lo <= segment.lo)&&(q.hi >= segment.hi)){
        //update rmq[pos]
        rmq[pos] +=val;
        //update lazy[LEFT(pos)], lazy[RIGHT(pos)]
        lazy[LEFT(pos)] += val;
        lazy[RIGHT(pos)] += val;
        return;
    }
    
    int m = (segment.lo + segment.hi+1)/2;
    update(rmq, q, {segment.lo, m}, val, LEFT(pos));
    update(rmq, q, {m, segment.hi}, val, RIGHT(pos));
    rmq[pos] = query_t.func(rmq[LEFT(pos)],rmq[RIGHT(pos)]);
    return;
}

template <typename T>
T findMin(vector<T> &rmq, range const& q, range segment, int pos){
    //total overlap
    if ((q.lo <= segment.lo)&&(q.hi >= segment.hi)) return rmq[pos];
    
    //no overlap
    if ((q.hi<= segment.lo)||(q.lo >= segment.hi)) return query_t.invalid;

    //partial overlap
    int m = (segment.lo + segment.hi+1)/2;
    return query_t.func(findMin(rmq, q, {segment.lo, m}, LEFT(pos)), findMin(rmq, q, {m, segment.hi}, RIGHT(pos)));
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
    if ((q.lo <= segment.lo)&&(q.hi >= segment.hi)) return rmq[pos];
    
    //no overlap
    if ((q.hi<= segment.lo)||(q.lo >= segment.hi)) return query_t.invalid;
    
    //partial overlap
    int m = (segment.lo + segment.hi+1)/2;
    return query_t.func(findMin(rmq, q, {segment.lo, m}, LEFT(pos)), findMin(rmq, q, {m, segment.hi}, RIGHT(pos)));
}



int main(){
    int N;
    cin >> N;
    
    vector<int> rmq = builtRMQ_implicit<int>(N);
    vector<int> smq = rmq;
    vector<int> lazy;
    lazy.resize(2*N -1 , 0);
    
    for(auto item: rmq) cout << item << " ";
    cout << endl;
    
    cout << findMin<int>(rmq, {0,4}, {0, N}, 0)<< endl;
    cout << lazy_findMin<int>(smq, lazy, {0,4}, {0, N}, 0)<< endl;
    
    update<int>(rmq, { 2, 3}, {0, N}, 3, 0);
    lazy_update<int>(smq, lazy, { 2, 3}, {0, N}, 3, 0);
    
    for(auto item: rmq) cout << item << " ";
    cout << endl;
    cout << findMin<int>(rmq, {0,4}, {0, N}, 0)<< endl;
    cout << lazy_findMin<int>(smq, lazy, {0,4}, {0, N}, 0)<< endl;
    
    
    
}

