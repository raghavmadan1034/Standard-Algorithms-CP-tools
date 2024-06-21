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

//LPS[i] indicates the length of longest prefix (starting from 0 index) which is same as length of suffix ending at i
//suffix ending at i is basically suffix of string containing characters till index i
//eg- aacaaaac ,LPS - 0 1 0 1 2 2 2 3 , lps[6] denotes length of longest prefix=suffix of string of characters till index 6
//prefix=aa ,suffix ending at index 6 =aa , lps[7]=3 (aac=aac)
vector<ll> createLPS(string &s){
    ll n=s.length();
    vector<ll>lps(n);
    lps[0]=0;
    ll j=0;
    ll i=1;
    while(i<n){
        if(s[i]==s[j]){
            j++;
            lps[i]=j;
            i++;
        }
        else{
            if(j==0){
                lps[i]=0;
                i++;
            }
            else{
                j=lps[j-1];
            }
        }
    }
    return lps;
}
bool KMPmatching(string &s,string &pattern){
    vector<ll>lps=createLPS(pattern);
    ll i=0,j=0;
    ll n=s.length();ll m=pattern.length();
    while(i<n && j<m){
        if(s[i]==pattern[j]){
                i++;j++;
        }
        else{
            if(j!=0){
                j = lps[j-1];
            }
            else{
                i++;
            }
        }
    }
    if(j==m)return true;
    return false;

}
int main(){
  
}
