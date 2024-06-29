#include<bits/stdc++.h>
using namespace std;
#define ll long long 
//Condition for topological sorting to exist=>Graph must be DAG
//Kahns algo kuch nhi Bas BFS lagana hai ,har node with indeg=0 ke neighbours pe jake indegree kam krni hai
void toposort(vector<vector<ll>>&adjlist,vector<ll>&indeg,ll n,vector<ll>&ans){
    // queue<ll>q; use Priority Queue instead of Normal Queue to print the lexographically smallest topo sort
    priority_queue<ll,vector<ll>,greater<ll>>pq;//Min heap
    for(ll i=1;i<=n;i++)if(indeg[i]==0)pq.push(i);
    while(pq.size()){
        ll curr=pq.top();
        ans.push_back(curr);
        pq.pop();
        for(auto x:adjlist[curr]){
            indeg[x]--;
            if(indeg[x]==0)pq.push(x);
        }
    }
}
int main(){
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    vector<ll>indeg(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;
        cin>>a>>b;
        adjlist[a].push_back(b);//directed graph
        indeg[b]++;
    }
    //No need of maintaing visited array since topsort means that graph is DAG
    //for DAG =>No cycles =>no visited array needed (like a directed tree it is)
    vector<ll>ans;
    toposort(adjlist,indeg,n,ans);
    if(ans.size()==n){
        for(auto x:ans)cout<<x<<" ";
    }
    else cout<<"No Topological Sorting Exists";
    
}
