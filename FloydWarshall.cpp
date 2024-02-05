#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//FLOYD WARSHALL ALGORITHM
//This algorithm computes distance between any 2 nodes in O(n^3)
int main(){
    //The graph is stored as adjlists so that adj[a] contains pair (b,w) always when there is edge from a to b with weight W
    ll n,m,q;
    cin>>n>>m>>q;
    vector<vector<pair<ll,ll>>>adjlist(n+1);//1 based indexing of nodes
    vector<vector<ll>>distance(n+1,vector<ll>(n+1,1e14));//we have 2.5*10^5 edges =>max distance 2.5*10^14 
    for(ll i=1;i<=n;i++)distance[i][i]=0;
    for(ll i=0;i<m;i++){
        ll a,b,w;
        cin>>a>>b>>w;
        distance[a][b]=min(distance[a][b],w);
        distance[b][a]=distance[a][b];
        adjlist[a].push_back({b,w});
        adjlist[b].push_back({a,w});
    }
    for(ll k=1;k<=n;k++){
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
                distance[i][j]=min(distance[i][j],distance[i][k]+distance[k][j]);
            }
        }
    }
    for(ll i=0;i<q;i++){
        ll x,y;
        cin>>x>>y;
        if(distance[x][y]==1e14)cout<<-1<<endl; //may overflow
        else cout<<distance[x][y]<<endl;
    }

}
