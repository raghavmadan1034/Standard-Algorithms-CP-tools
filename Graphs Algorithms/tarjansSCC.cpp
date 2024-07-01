#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll timer;
stack<ll>st;
void dfs(vector<vector<ll>>&adjlist,vector<ll>&visited,ll start,vector<ll>&in,vector<ll>&low,vector<ll>&onStack,vector<vector<ll>>&scc){
    visited[start]=1;
    in[start]=low[start]=timer;
    timer++;
    onStack[start]=1;
    st.push(start);
    for(auto x:adjlist[start]){
        if(!visited[x]){
            dfs(adjlist,visited,x,in,low,onStack,scc);
            if(onStack[x]){
                low[start]=min(low[start],low[x]);//backtracking from dfs
            }
        }
        else{//x is already visited (=>some ancestor in dfs tree)
            if(onStack[x]==1){
                low[start]=min(low[start],in[x]);
            }
        }
    }
    if(in[start]==low[start]){//when we have done the whole dfs for a single SCC and backtracked completely
        ll u;
        vector<ll>temp;
        while(true){
            u=st.top();
            st.pop();
            onStack[u]=0;
            temp.push_back(u);
            if(u==start)break;//stop popping from stack (neeche kisi aur SCC ki nodes hai jinse bfs shuru kra)    
        }
        scc.push_back(temp);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;cin>>n>>m;
    vector<vector<ll>>adjlist(n+1);
    for(ll i=0;i<m;i++){
        ll a,b;cin>>a>>b;
        adjlist[a].push_back(b);
    }
    vector<ll>onStack(n+1);vector<ll>visited(n+1);
    vector<ll>in(n+1);vector<ll>low(n+1);
    vector<vector<ll>>scc;
    for(ll i=1;i<=n;i++){
        if(!visited[i]){
            dfs(adjlist,visited,i,in,low,onStack,scc);
        }
    }
    for(ll i=0;i<scc.size();i++){
        for(auto x:scc[i]){
            cout<<x<<" ";
        }
        cout<<endl;
    }

}
