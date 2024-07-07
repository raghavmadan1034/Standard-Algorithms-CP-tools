#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll INF=1e10;
void bfs(vector<vector<pair<ll,ll>>>&adjlist,vector<ll>&dist,ll start,vector<ll>&processed){
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    pq.push({0,start});
    dist[start]=0;
    while(pq.size()){
        ll curr=pq.top().second;
        ll d=pq.top().first;
        pq.pop();
        if(processed[curr])continue;
        processed[curr]=1;
        for(auto x:adjlist[curr]){
            if(!processed[x.first] && d+x.second<dist[x.first]){
                dist[x.first]=d+x.second;
                pq.push({dist[x.first],x.first});
            }
        }
    }
}
int main(){
    ll n,m;cin>>n>>m;
    vector<vector<pair<ll,ll>>>adjlist(n+1);
    for(ll i=0;i<m;i++){
        ll a,b,w;cin>>a>>b>>w;
        adjlist[a].push_back({b,w});
        adjlist[b].push_back({a,w});//for directed graph comment out this line
    }
    vector<ll>dist(n+1,INF);vector<ll>processed(n+1);
    bfs(adjlist,dist,1,processed);
    for(ll i=1;i<=n;i++)cout<<dist[i]<<" ";

}
