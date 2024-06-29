#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll timer;
void dfs(vector<vector<ll>>&adjlist,vector<ll>&visited,vector<ll>&parent,ll start,vector<ll>&in,vector<ll>&low,set<ll>&ap){
    visited[start]=1;
    in[start]=low[start]=timer;
    timer++;
    ll cntchild=0;
    for(auto x:adjlist[start]){
        if(x==parent[start])continue;
        if(!visited[x]){
            cntchild++;
            parent[x]=start;
            dfs(adjlist,visited,parent,x,in,low,ap);
            low[start]=min(low[start],low[x]);
            if(low[x]>=in[start] && parent[start]!=-1)ap.insert(start);
            //difference from bridges -> low[x]>=in[start] here instead of low[x]>in[start]

        }
        else{//x is already visited=>x is some ancestor
            low[start]=min(low[start],in[x]);
        }
    }
    //check if root is AP (alag se ,as using low in method root is always ap)
    if(parent[start]==-1 && cntchild>1)ap.insert(start);
}
int main(){
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);vector<ll>visited(n+1);vector<ll>parent(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    //Nodes labelled from 1 to N (not 0 to n)
    vector<ll>in(n+1);vector<ll>low(n+1);
    set<ll>ap;//set used coz same node might be calculated as AP twice
    //bcz unlike bridges algorithm we see low[x]>=in[start] for each child and push only start
    //So start can be pushed multpile times if for multiple childs low[x]>=in[start]
    for(ll i=1;i<=n;i++){
        if(!visited[i]){
            parent[i]=-1;
            dfs(adjlist,visited,parent,i,in,low,ap);
        }
    }
    //SET ap stores all the articulation points
}
