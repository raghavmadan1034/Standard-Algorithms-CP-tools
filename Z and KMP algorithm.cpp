#include<bits/stdc++.h>
using namespace std;
#define ll long long 
vector<ll> createZarray(string s){//returns the Z array for a given string (Z[i] is length of longest substring starting from s[i] equal to the prefix of s)
    ll n=s.size();
    vector<ll>z(n);
    ll x=0,y=0;
    for(ll i=1;i<n;i++){
        z[i]=max((ll)0,min(z[i-x],y-i+1));
        while(i+z[i]<n && s[z[i]]==s[i+z[i]]){
            x=i;
            y=i+z[i];
            z[i]++;
        }
    }
    return z;
}
int main(){
  
}
