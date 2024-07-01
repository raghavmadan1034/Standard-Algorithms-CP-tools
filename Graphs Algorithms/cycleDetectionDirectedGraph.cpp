#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pb push_back
bool dfs(vector<vector<ll>>&adjlist,vector<ll>&visited,ll start,vector<ll>&parent,vector<ll>&active){
    visited[start]=1;
    active[start]=1;
    for(auto x:adjlist[start]){
        if(!visited[x]){
            parent[x]=start;
            if(dfs(adjlist,visited,x,parent,active))return 1;
        }
        else if(visited[x] && active[x]){
            return 1; 
        }
    }
    active[start]=0;//dfs complete ,And abhi tak cycle nhi mili toh backtracking ke samay nodes ko deactive krte jao 
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].pb(b);

    }
    vector<ll>visited(n+1);vector<ll>parent(n+1);
    vector<ll>active(n+1);
    //Why maintaining active node is necessary ?
    //for eg path from 1->3->5 exists and 1->2->3 exist .But no path from 3->1
    //So if we dfs 1,3,5 first ,3 will be already visited and will give us false answer that there is cycle
    //even tho there isn't .So deativate 3rd and 5th node and then continue dfs
    //agar 3->1 back path hota toh backtracking ke samay deactivate nhi hota fir 
    ll ans=0;
    for(ll i=1;i<=n;i++){
        if(!visited[i]){
            if(dfs(adjlist,visited,i,parent,active))ans=1;
        }
    }
    cout<<ans<<endl;//ans=1 if cycle exits in directed graph
}
