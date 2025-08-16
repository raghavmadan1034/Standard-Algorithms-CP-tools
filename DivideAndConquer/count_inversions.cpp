#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll cnt_inv(vector<ll>&v,ll st,ll ed){
    if(st>=ed)return 0;
    ll mid=(st+ed)/2;
    ll l=cnt_inv(v,st,mid);
    ll r=cnt_inv(v,mid+1,ed);
    //if the function returns sorted array, then work is done 
    vector<ll>left;
    vector<ll>right;
    for(ll i=st;i<=mid;i++){
        left.push_back(v[i]);
    }
    for(ll i=mid+1;i<=ed;i++)right.push_back(v[i]);
    ll ls=left.size();ll rs=right.size();
    ll i=0,j=0,k=st;
    ll cnt=0;
    while(i<ls && j<rs){
        if(left[i]<=right[j]){
            v[k]=left[i];
            i++;k++;
        }
        else{
            cnt+=ls-i;
            v[k]=right[j];
            j++;k++;
        }
    }
    while(i<ls){
        v[k]=left[i];
        i++;k++;
    }
    while(j<rs){
        v[k]=right[j];
        k++;j++;
    }
    return cnt+l+r;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;cin>>n;
    vector<ll>v(n);
    for(ll i=0;i<n;i++)cin>>v[i];
    ll inv=cnt_inv(v,0,n-1);
    cout<<inv<<endl;
    return 0;
}
