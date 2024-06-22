#include<bits/stdc++.h>
using namespace std;
#define ll long long
//dijkstra's Algorithm uses Priority Queues (min heap)
//We will store negative elements (distances) in priority queue coz C++ PQ is max heap so minimum abs distance is on the top, (maximum element among all)
void dijkstra(vector<vector<pair<ll,ll>>>&adjlist,vector<ll>&distance,ll source,vector<ll>&processed){
    distance[source]=0;
    priority_queue<pair<ll,ll>>pq;
    pq.push({0,source});
    while(pq.size()){
        ll a=pq.top().second;
        pq.pop();
        if(processed[a])continue; //->This is important otherwise chance of TLE(if initially a is not processed and before calling 'a' it gets processed)
        processed[a]=1;
        for(auto y:adjlist[a]){
            ll b=y.first;
            ll w=y.second;
            if(processed[b]==0 && distance[a]+w<distance[b]){
                distance[b]=distance[a]+w;
                pq.push({-distance[b],b});
            } 
            //if distance[a]+w>distance[b] => this implies that the node b has already been selected
            //Property of Dijkstra :-Once a node has been selected,its distance is FINAL.
            //so if distance[a]+w>distance[b] =>you found its min distace already=> no need of pushing it back...
        }
    }
}
int main(){
    //The graph is stored as adjlists so that adj[a] contains pair (b,w) always when there is edge from a to b with weight W
    ll n,m;
    cin>>n>>m;
    vector<vector<pair<ll,ll>>>adjlist(n+1);//1 based indexing of nodes
    for(ll i=0;i<m;i++){
        ll a,b,w;
        cin>>a>>b>>w;
        adjlist[a].push_back({b,w});
        adjlist[b].push_back({a,w});//DONT WRITE THIS LINE IF GRAPH IS DIRECTED!!!!
    }
    vector<ll>distance(n+1,LLONG_MAX);
    vector<ll>processed(n+1,0);
    //There is difference between visited of BFS and processed of dijsktra
    //in dijkstra you can push same node multiple times in pq,but process vo ek hi baar hogi
    dijkstra(adjlist,distance,1,processed);
    for(ll i=1;i<=n;i++){
        cout<<distance[i]<<" ";
    }

}
