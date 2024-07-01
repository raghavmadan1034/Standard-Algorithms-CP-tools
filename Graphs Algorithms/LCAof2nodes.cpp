#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll Log(ll m){
    return ceil(log2(m));
}
void bfs(vector<vector<ll>>&adjlist,vector<ll>&visited,ll start,vector<ll>&dist,vector<ll>&parent){
    visited[start]=1;
    parent[start]=-1;
    queue<ll>q;
    q.push(start);
    while(q.size()){
        ll node=q.front();
        q.pop();
        for(auto x:adjlist[node]){
            if(!visited[x]){
                visited[x]=1;
                parent[x]=node;
                dist[x]=dist[node]+1;
                q.push(x);
            }
        }
    }

}
ll findLCA(vector<vector<ll>>&lca,vector<ll>&dist,ll node1,ll node2,ll maxN){
    if(dist[node1]>dist[node2])swap(node1,node2);
    ll d=dist[node2]-dist[node1]; //node 2 is lower than node1 (dist[node2]>dist[node1])
    while(d>0){
        ll i=floor(log2(d));
        node2=lca[node2][i];
        d-=(1LL<<i);
    }
    if(node1==node2)return node1;
    //after this level of node1 and node2 is same

    for(ll i=maxN;i>=0;i--){
        if(lca[node1][i]!=-1 && lca[node1][i]!=lca[node2][i]){
            // cout<<i<<endl;
            node1=lca[node1][i];
            node2=lca[node2][i];
        }
    }
    return lca[node1][0];

}
ll finddist(vector<vector<ll>>&lca,vector<ll>&dist,ll node1,ll node2,ll maxN){
    //tells dist between any 2 nodes in trees
    ll lcanode=findLCA(lca,dist,node1,node2,maxN);
    return dist[node1]+dist[node2]-2*dist[lcanode];
}
int main(){
    ll n;cin>>n;
    vector<vector<ll>>adjlist(n+1);
    //level array is nothing but the distance array from root(level and distance are same things)
    for(ll i=0;i<n-1;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    vector<ll>dist(n+1);vector<ll>visited(n+1);vector<ll>parent(n+1);
    bfs(adjlist,visited,1,dist,parent);
    ll maxN=Log(n);
    vector<vector<ll>>lca(n+1,vector<ll>(maxN+1,-1));
    //lca[i][j] ->2^j th parent of i th node 
    for(ll i=1;i<=n;i++){
        lca[i][0]=parent[i];
    }
    for(ll j=1;j<=maxN;j++){//j wala loop hamesha upar ayega
        //coz for lca[i][j] you need to find the j-1th parent and usa Lca lena hai 
        //So you should have completely filled the j-1th column for all nodes
        for(ll i=1;i<=n;i++){
            if(lca[i][j-1]!=-1)lca[i][j]=lca[lca[i][j-1]][j-1];
        }
    }
    ll q;cin>>q;
    for(ll i=0;i<q;i++){
        ll a,b;cin>>a>>b;
        cout<<finddist(lca,dist,a,b,maxN)<<endl;
    }

}
