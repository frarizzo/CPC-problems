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

/*********** C'è un off by one mi sa perchè trova male gli indici degli elementi ****************/

#define LEFT(i)    2*i + 1
#define RIGHT(i)   2*i + 2
#define PARENT(i)  (i-1)/2

std::ofstream out("output.txt");
std::ofstream out2("output2.csv");
std::ofstream out3("output3.csv");

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

template< typename T>
struct tree_el{
    T val;
    range r;
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
vector< tree_el<T> > builtRMQ_implicit(int N){
    /*if (N == 1){
        vector<T> rmq_tree;
        T n;
        cin >> n;
        rmq_tree.push_back(n);
        
        return rmq_tree;
    }*/
    
    vector< tree_el<T> > rmq_tree;
    rmq_tree.resize(2*N-1, {query_t.invalid, {-1,-1}});
    
    int h = ceil(log2(N));
    //Except for the last level, the three is full so the parent of the first leaf (starting from the left) has index 2^{h-1} - 1.
    int p =(1<<(h-1))-1;
    int first_leaf = LEFT(p);
    
    //read input int two times (first go forward, then return back)
    int i = 0;
    for(int j = first_leaf; j<2*N-1; j++, i++){
        T n;
        cin >> n;
        rmq_tree[j] = {n, {i, i+1}};
    }
    //I have to store N - (2N-1-first_leaft) numbers, so I start from
    //start = first_leaf - N - (2N-1-first_leaft) = N-1
    int start = N-1;
    for(int j = 0; j < first_leaf-start; j++, i++){
        T n;
        cin >> n;
        rmq_tree[start + j] = {n, {i, i+1}};
    }
    
    //fill with minimum
    for(int i=2*N-2; i>0; i-=2) rmq_tree[PARENT(i)] = {min(rmq_tree[i].val, rmq_tree[i-1].val), {rmq_tree[i-1].r.lo, rmq_tree[i].r.hi}};
    
    
    
    /*print in out2
    for(int j = first_leaf; j<2*N-1; j++){
        out2 <<j << ";" << rmq_tree[j] << endl;
    }
    for(int j = 0; j < first_leaf-start; j++){
        out2 <<start + j << ";" <<  rmq_tree[start +j] << endl;
    }*/
    
    for(int j = 0; j<2*N-1; j++){
        out2 << j << ";" << rmq_tree[j].val << ";" << rmq_tree[j].r.lo << ";" << rmq_tree[j].r.hi << endl;
    }
    
    
    return rmq_tree;
}

template <typename T>
void update(vector< tree_el<T> > &rmq, range const& q, T const h, int pos){
    range segment = rmq[pos].r;
    
    //no overlap
    if ((q.lo >= segment.hi)||(q.hi <= segment.lo)) return;
    
    //leaf
    if (segment.lo == segment.hi - 1){
        rmq[pos].val += h;
        return;
    }
    
    update(rmq, q, h, LEFT(pos));
    update(rmq, q, h, RIGHT(pos));
    rmq[pos].val = query_t.func(rmq[LEFT(pos)].val,rmq[RIGHT(pos)].val);
    return;
}

template <typename T>
void lazy_update(vector< tree_el<T> > &rmq, vector<T> &lazy, range const& q, T const h, int pos){
    //if lazy[pos] != 0, updatre rmq[pos]
    if (lazy[pos] != 0){
        rmq[pos].val += lazy[pos];
        lazy[LEFT(pos)] += lazy[pos];
        lazy[RIGHT(pos)] += lazy[pos];
        lazy[pos] = 0;
    }
    
    range segment = rmq[pos].r;
    
    //no overlap
    if ((q.lo >= segment.hi)||(q.hi <= segment.lo)) return;
    
    //total overlap
    if((q.lo <= segment.lo)&&(q.hi >= segment.hi)){
        //update rmq[pos]
        rmq[pos].val +=h;
        //update lazy[LEFT(pos)], lazy[RIGHT(pos)]
        lazy[LEFT(pos)] += h;
        lazy[RIGHT(pos)] += h;
        return;
    }
    
    update(rmq, q, h, LEFT(pos));
    update(rmq, q, h, RIGHT(pos));
    rmq[pos].val = query_t.func(rmq[LEFT(pos)].val,rmq[RIGHT(pos)].val);
    return;
}

template <typename T>
T findMin(vector<tree_el<T> > &rmq, range const& q, int pos){
    range segment = rmq[pos].r;

    //total overlap
    if ((q.lo <= segment.lo)&&(q.hi >= segment.hi)) return rmq[pos].val;
    
    //no overlap
    if ((q.hi<= segment.lo)||(q.lo >= segment.hi)) return query_t.invalid;
    
    //partial overlap
    return query_t.func(findMin(rmq, q, LEFT(pos)), findMin(rmq, q, RIGHT(pos)));
}

template <typename T>
T lazy_findMin(vector<tree_el<T> > &rmq, vector<T> &lazy, range const& q, int pos){
    //if lazy[pos] != 0, updatre rmq[pos]
    if (lazy[pos] != 0){
        rmq[pos].val += lazy[pos];
        lazy[LEFT(pos)] += lazy[pos];
        lazy[RIGHT(pos)] += lazy[pos];
        lazy[pos] = 0;
    }
    
    range segment = rmq[pos].r;
    
    //out << segment.lo << " - " << segment.hi << "in pos" << pos << endl;
    
    //total overlap
    if ((q.lo <= segment.lo)&&(q.hi >= segment.hi)) {
        //out << rmq[pos] << " in " << pos << endl;
        return rmq[pos].val;
    }
    
    //no overlap
    if ((q.hi<= segment.lo)||(q.lo >= segment.hi)) return query_t.invalid;
    
    //partial overlap
    return query_t.func(lazy_findMin(rmq, lazy, q, LEFT(pos)), lazy_findMin(rmq,lazy, q, RIGHT(pos)));
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
template <typename T>
void print_rmq(vector<tree_el<T> > &rmq, int pos){
    range segment = rmq[pos].r;
    
    if (segment.lo +1 == segment.hi){
        out3 << pos <<";"<< segment.lo <<";"<< segment.hi << ";"<< rmq[pos].val << endl;
        return;
    }

    print_rmq(rmq, LEFT(pos));
    out3 << pos <<";"<<segment.lo <<";"<< segment.hi << ";" << rmq[pos].val << endl;
    print_rmq(rmq, RIGHT(pos));
}

int main(){
    int N, M;
    cin >> N;
    
    if (N == 1) {
        linear_code();
        return 0;
    }
    
    vector<tree_el<int64_t> > rmq = builtRMQ_implicit<int64_t>(N);
    vector<int64_t> lazy;
    lazy.resize(2*N -1 , 0);
    
    print_rmq<int64_t>(rmq, 0);
    
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
                cout << lazy_findMin<int64_t><< endl;
            } else {
                int m1 = lazy_findMin<int64_t>(rmq, lazy, {input[0], N}, 0);
                int m2 = lazy_findMin<int64_t>(rmq, lazy, {0, input[1]+1}, 0);
                cout << min (m1, m2) <<endl;
            }
        }
        else if (input.size() == 3){
            //segments are circular
            if (input[0]<= input[1]){
                lazy_update<int64_t>(rmq, lazy, {input[0], input[1]+1}, input[2], 0);
            } else {
                lazy_update<int64_t>(rmq, lazy, {input[0], N}, input[2], 0);
                lazy_update<int64_t>(rmq, lazy, {0, input[1]+1}, input[2], 0);
            }
        }
    }
}


