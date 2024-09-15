//finds longest palindromic substring in the given string in O(n)
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
vector<ll> manacher_odd(string s) {
    ll n = s.size();
    s = "$" + s + "^";
    vector<ll> p(n + 2);
    ll l = 1, r = 1;
    for(ll i = 1; i <= n; i++) {
        p[i] = max(0LL, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]]==s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    for(ll i=1;i<=n;i++){
        p[i]*=2;
        p[i]-=1;
    }
    return vector<ll>(begin(p) + 1, end(p) - 1);
}
int main(){
    string s;cin>>s;
    ll n=s.length();
    string t;
    for(auto x:s){
        t+="#";
        t.push_back(x);
    }
    t.push_back('#');
    vector<ll>dp=manacher_odd(t);
    ll ans=0,f=0,indx=-1;
    //for odd palindrome centred at index i, (dp[2*i+1]-1)/2 gives the length of the palindrome 
    //for even palindrome centred at index i and i+1, (dp[2*i+2]-1)/2 gives the length of the palindrome 
    for(ll i=0;i<n;i++){
        ll eve=((dp[2*i+2]-1)/2);
        ll odd=((dp[2*i+1]-1)/2);
        if(odd>=eve){
            if(odd>=ans){
                ans=odd;
                f=0;
                indx=i;
            }
        }
        else{
            if(eve>ans){
                ans=eve;
                f=1;
                indx=i;
            }
        }
    }
    cout<<ans<<endl;
}
