#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll reportMin(ll i,ll j,vector<ll>&A,ll n){
    i+=n-1;
    j+=n-1;
    ll ans=A[i];
    if(j>i){
        ans=min(ans,A[j]);
        while(floor((i-1)*1.0/2)!=floor((j-1)*1.0/2)){
            if(i%2==1)ans=min(ans,A[i+1]);//A[i] is the left child
            if(j%2==0)ans=min(ans,A[j-1]);//A[j] is the right child
            i=floor((i-1)*1.0/2);//move upwards towards parents
            j=floor((j-1)*1.0/2);
        }
    }
    return ans;
}
ll dynamicSum(ll i,ll j,vector<ll>&A,ll n){
    i+=n-1;
    j+=n-1;
    ll sum=A[i];
    if(j>i){
        sum+=A[j];
        while(floor((i-1)*1.0/2)!=floor((j-1)*1.0/2)){
            if(i%2==1)sum+=A[i+1];//A[i] is the left child
            if(j%2==0)sum+=A[j-1];//A[j] is the right child
            i=floor((i-1)*1.0/2);//move upwards towards parents
            j=floor((j-1)*1.0/2);
        }
    }
    return sum;
}
void update(ll k,ll a,vector<ll>&A,ll n){
    ll i=n-1+k;
    A[i]=a;
    i=floor((i-1)*1.0/2);
    while(i>=0){
        A[i]=min(A[2*i+1],A[2*i+2]);
        // A[i]=A[2*i+1]+A[2*i+2];
        i=floor((i-1)*1.0/2);
    }
}
int main(){
    ll n,q;
    cin>>n>>q;
    vector<ll>v(n);
    for(ll i=0;i<n;i++)cin>>v[i];

    vector<ll>A(2*n-1);
    for(ll i=n-1;i<2*n-1;i++){
        A[i]=v[i-n+1];
    }
    for(ll i=2*n-2;i>0;i-=2){
        A[(i-1)/2]=min(A[i],A[i-1]); //parent is minimumm of 2 children
        A[(i-1)/2]=A[i]+A[i-1];
    }
    //leaf node corresponding to v[i]=A[n-1+i], if index of A[i] is odd => then left child,else right 
    for(ll i=0;i<q;i++){
        ll c,a,b;
        cin>>c>>a>>b;
        ll ans;
        if(c==2){
            ans=dynamicSum(a-1,b-1,A,n);
            cout<<ans<<endl;
        }
        else if(c==1){
            update(a-1,b,A,n);
        }
    }
    // for(ll i=0;i<2*n-1;i++){
    //     cout<<A[i]<<" ";
    // }
}
