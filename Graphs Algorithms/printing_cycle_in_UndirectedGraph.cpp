//detect and print any cycle in an undirectred graph
//Not possible to print all cycles (as cycles may overlap,not a polynomial time algo)
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
bool dfs(vector<vector<ll>>&adjlist,vector<ll>&visited,ll start,vector<ll>&parent,vector<ll>&list){
    visited[start]=1;
    list.push_back(start);
    for(auto x:adjlist[start]){
        if(!visited[x]){
            parent[x]=start;
            if(dfs(adjlist,visited,x,parent,list))return 1;
        }
        else if(x!=parent[start]){
            list.push_back(x);
            return 1;
        }
    }
    list.pop_back();//dead end aa gya ,and ab backtrack karenge so remove the unnessary nodes
    //so that they dont interfere with the cycle .Eg- 3 ke saath ek cycle thi and ek branch 
    //so branch pe dfs karte gye and then cycle pe ayenge toh mix ho jayega
    //So remove nodes while backtracking 
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    vector<ll>visited(n+1);vector<ll>parent(n+1);
    vector<ll>list;
    ll f=0;
    for(ll i=1;i<=n;i++){
        if(!visited[i]){
            if(dfs(adjlist,visited,i,parent,list)){
                f=1;
                break;
            } 
        }
    }
    if(f){
        vector<ll>cycle;
        ll e=list.back();list.pop_back();cycle.push_back(e);
        while(list.back()!=e){
            cycle.push_back(list.back());
            list.pop_back();
        }
        cycle.push_back(e);
        cout<<cycle.size()<<endl;
        for(auto x:cycle)cout<<x<<" ";
    }
    else cout<<"NO CYCLE";
}
