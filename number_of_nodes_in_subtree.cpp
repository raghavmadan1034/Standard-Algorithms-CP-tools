#include<bits/stdc++.h>
using namespace std;
#define ll long long 
void dfs(vector<vector<ll>>&adjlist,vector<ll>&count,ll source,vector<ll>&visited){//count stores nodes in subtree for each node in the tree
    count[source]=1;
    visited[source]=1;
    for(auto x:adjlist[source]){
        if(!visited[x]){
            dfs(adjlist,count,x,visited);
            count[source]+=count[x]; //dp on trees 
        }
    }
}
int main(){
    ll n;
    cin>>n;
    vector<vector<ll>>adjlist(n+1);
    //input tree in adjacency list format
    vector<ll>visited(n+1);
    vector<ll>count(n+1); //All are 1-indexed
    dfs(adjlist,count,1,visited);
    for(ll i=1;i<=n;i++){
        cout<<count[i]<<" ";
    }

}
