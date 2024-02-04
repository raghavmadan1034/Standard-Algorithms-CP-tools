#include<bits/stdc++.h>
using namespace std;
#define ll long long
void bfs(vector<vector<ll>>&adjlist,vector<ll>&visited,ll source, vector<ll>&distance,vector<ll>&parent){
    queue<ll>q;
    q.push(source);
    visited[source]=1;
    while(q.size()){
        ll x=q.front();
        q.pop();
        for(ll y:adjlist[x]){
            if(!visited[y]){
                q.push(y);
                visited[y]=1;
                parent[y]=x;
                distance[y]=distance[x]+1;
            }
        }
    }
}
int main(){
    ll n,m;
    cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;
        cin>>a>>b;
        adjlist[a].pb(b);
        adjlist[b].pb(a);
    }
    vector<ll>visited(n+1);
    vector<ll>distance(n+1);
    vector<ll>parent(n+1);
    bfs(adjlist,visited,1,distance,parent);
    return 0;
}
