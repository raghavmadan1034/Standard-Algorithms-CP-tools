#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;cin>>n>>m;
    vector<vector<ll>>v(n,vector<ll>(m));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++)cin>>v[i][j];
    }
    vector<vector<ll>>rowprefix(n+1,vector<ll>(m+1));
    for(ll j=1;j<=m;j++){
        for(ll i=1;i<=n;i++){
            rowprefix[i][j]=v[i-1][j-1]+rowprefix[i-1][j];
        }
    }
    ll ans=-9e7; 
    pair<ll,ll>end;pair<ll,ll>start;

    //O(n*m*n) extra space approach 
    // vector<vector<vector<ll>>>dp(n,vector<vector<ll>>(m,vector<ll>(n)));
    // //dp[i][j][k]==max sum of rectangle ending at (i,j) , startking at row k
    // for(ll i=0;i<n;i++){
    //     for(ll j=0;j<m;j++){
    //         for(ll k=0;k<=i;k++){
    //             if(j-1>=0 && dp[i][j-1][k]>=0){
    //                 dp[i][j][k]=dp[i][j-1][k]+rowprefix[i+1][j+1]-rowprefix[k][j+1];
    //             }
    //             else dp[i][j][k]=rowprefix[i+1][j+1]-rowprefix[k][j+1];
    //             if(dp[i][j][k]>ans){
    //                 ans=dp[i][j][k];
    //                 end={i,j};
    //                 start.first=k;
    //             }
    //         }
    //     }
    // }
    
    //O(n) extra space approach 
    //fix i(ending row of rectangle ) and k(starting row of rectangle)
    vector<ll>temp(m);
    vector<ll>dp(m);
    for(ll i=0;i<n;i++){
        for(ll k=0;k<=i;k++){
            for(ll j=0;j<m;j++){
                temp[j]=rowprefix[i+1][j+1]-rowprefix[k][j+1];
            }
            for(ll j=0;j<m;j++){
                if(j-1>=0 && dp[j-1]>=0){
                    dp[j]=dp[j-1]+temp[j];//dp[j]==maximum subarray sum ending at index j
                }
                else dp[j]=temp[j];
                if(dp[j]>ans){
                    ans=dp[j];
                    end={i,j};
                    start.first=k;
                }
            }
            for(ll j=0;j<m;j++){
                dp[j]=0;temp[j]=0;
            }

        }
    }
    ll tans=0;
    for(ll j=end.second;j>=0;j--){
        tans+=rowprefix[end.first+1][j+1]-rowprefix[start.first][j+1];
        if(tans==ans){
            start.second=j;
            break;
        }
    }
    cout<<ans<<endl;
    cout<<start.first+1<<" "<<start.second+1<<" "<<end.first+1<<" "<<end.second+1<<endl;  //1 indexed top left and bottom right corner of rectangle 
    
    return 0;
}
