#include<bits/stdc++.h>
using namespace std;

class SGTree{
    private:
        vector<int> seg;
    public:
        SGTree(int n){
            seg.resize(4*n + 1);
        }

        void build(int idx, int low, int high, vector<int> arr){
            // last segment
            if(low == high){
                seg[idx] = arr[low];
                return;
            }

            int mid = (low + high) >> 1;
            build(2*idx + 1, low, mid, arr);
            build(2*idx + 2, mid + 1, high, arr);
            seg[idx] = min(seg[2*idx+1], seg[2*idx+2]);
        }

        int query(int idx, int low, int high, int l, int r){
            // no overlapping case, i.e, low high l r or l r low high
            if(high<l || low>r) return INT_MAX;
            // complete overlap, i.e., l low high r
            if(l<=low && high<=r)   return seg[idx];
            // partial overlap
            int mid = (low + high) >> 1;
            int left = query(2*idx+1, low, mid, l, r);
            int right = query(2*idx + 2, mid+1, high, l, r);
            return min(left, right);
        }

        void update(int idx, int low, int high, int ind, int val){
            if(low == high){
                seg[idx] = val;
                return;
            }
            int mid = (low + high) >> 1;
            if(ind <= mid)  update(2*idx + 1, low, mid, ind, val);
            else    update(2*idx + 2, mid+1, high, ind, val);
            seg[idx] = min(seg[2*idx + 1], seg[2*idx + 2]);
        }
};

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++)  cin>>arr[i];
    SGTree seg(n);
    seg.build(0, 0, n-1, arr);
    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type == 1){
            int l, r;
            cin>>l>>r;
            cout<<seg.query(0, 0, n-1, l, r)<<endl;
        }
        else{
            int ind, val;
            cin>>ind>>val;
            seg.update(0, 0, n-1, ind, val);
        }
    }
    return 0;
}