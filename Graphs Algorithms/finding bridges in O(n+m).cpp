#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll timer;//variable defined globally is initialized to 0

void dfs(vector<vector<ll>>&adjlist,vector<ll>&visited,vector<ll>&parent,ll start,vector<pair<ll,ll>>&bridges,vector<ll>&in,vector<ll>&low){
    visited[start]=1;
    in[start]=low[start]=timer;
    timer++;
    for(auto x:adjlist[start]){
        if(x==parent[start])continue;
        if(!visited[x]){
            parent[x]=start;
            dfs(adjlist,visited,parent,x,bridges,in,low);
            //back track karne ke baad hi toh dekh paoge ki x aur start ki edge bridge hai ya nhi 
            if(low[x]>in[start]){//if (low[x]<=in[start]) means x se koi ancestor connected hai through backedge (so not a bridge,(otherwise its a bridge)) 
                bridges.push_back({min(x,start),max(x,start)});
            }
            low[start]=min(low[start],low[x]);//backtrack karne ke baad hi toh start ka low time update kroge
        }
        else{// x has already been visited =>x is some ancestor
            low[start]=min(low[start],in[x]);//update the low time of start as intime of ancestor (x is the ancestor in this case)
        }
    }
}
int main(){
    ll n,m;
    cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    //PS-Here nodes are labelled from 1 to N ,not from 0 to N-1 
    vector<ll>visited(n+1);vector<ll>in(n+1);vector<ll>low(n+1);vector<ll>parent(n+1);vector<pair<ll,ll>>bridges;
    for(ll i=1;i<=n;i++)if(!visited[i])dfs(adjlist,visited,parent,i,bridges,in,low);
    sort(bridges.begin(),bridges.end());
    cout<<bridges.size()<<endl;
    for(auto x:bridges){
        cout<<x.first<<" "<<x.second<<endl;
    }

}
