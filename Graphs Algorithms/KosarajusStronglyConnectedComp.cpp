//This algorithm prints list of strongly connected components in a directed graph
#include<bits/stdc++.h>
using namespace std;
#define ll long long
void dfs(vector<vector<ll>>&adjlist,vector<ll>&visited,ll start,vector<ll>&order){
    visited[start]=1;
    for(auto x:adjlist[start]){
        if(!visited[x])dfs(adjlist,visited,x,order);
    }
    order.push_back(start);//list of nodes with increasing out time 
}
void dfs1(vector<vector<ll>>&tradjlist,vector<ll>&visited,ll start,vector<ll>&temp){
    visited[start]=1;
    for(auto x:tradjlist[start]){
        if(!visited[x]){
            dfs1(tradjlist,visited,x,temp);
        }
    }
    temp.push_back(start);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    vector<vector<ll>>tradjlist(n+1);//transposed graph adjacency list
    for(ll i=0;i<m;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].push_back(b);//in the question edge from a->b is given
        tradjlist[b].push_back(a);//transposed graph me edge ki direction ulti kar do 
    }
    vector<ll>order;//list of nodes with increasing out time 
    vector<ll>visited(n+1);
    for(ll i=1;i<=n;i++)if(!visited[i])dfs(adjlist,visited,i,order);
    visited.clear();visited.resize(n+1);
    vector<vector<ll>>scc;
    for(ll i=n-1;i>=0;i--){
        if(!visited[order[i]]){
            vector<ll>temp;
            dfs1(tradjlist,visited,order[i],temp);
            scc.push_back(temp);
        }
    }
    for(ll i=0;i<scc.size();i++){
        for(auto x:scc[i]){
            cout<<x<<" ";
        }
        cout<<endl;
    }
}
