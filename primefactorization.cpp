#include<bits/stdc++.h>
using namespace std;
#define ll long long
void primefactors(ll n,map<ll,ll>&m){
    while(n%2==0){
        m[2]++;
        n/=2;
    }
    for(ll i=3;i<=sqrt(n);i++){
        while(n%i==0){
            m[i]++;
            n/=i;
        }
    }
    if(n>2){//if the given number is prime number say,then this case is used
        m[n]++;
    }

}
int main(){
    ll n;
    cin>>n;
    map<ll,ll>m;
    primefactors(n,m);
    for(auto x:m){
        cout<<x.first<<" "<<x.second;
        cout<<endl;
    }
}
