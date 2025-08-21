#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll modify(vector<ll>&v,ll k){
    if(v.size()%5==0)return k;
    else{
        for(ll i=0;i<5-v.size()%5;i++){
            v.push_back(-1e9);
            k++;
        }
        return k;
    }
}
ll find_kth_rank(vector<ll>v, ll k){
    //ensure that v is multiple of 5 
    if(v.size()==1)return v[0];
    k=modify(v,k);
    vector<ll>med;
    vector<ll>temp;
    ll i=0;
    while(i<v.size()){
        while(i<v.size() && temp.size()!=5){
            temp.push_back(v[i]);
            i++;
        }
        // cout<<temp.size();
        sort(temp.begin(),temp.end());
        med.push_back(temp[2]);
        temp.clear();
        // cout<<temp.size();
    }
    ll x=find_kth_rank(med,med.size()/2+1);
    vector<ll>left;vector<ll>right;
    ll cntx=0;
    for(ll i=0;i<v.size();i++){
        if(v[i]<x)left.push_back(v[i]);
        else if(v[i]>x)right.push_back(v[i]);
        else cntx++;
    }
    if(k<=left.size()){
        return find_kth_rank(left,k);
    }
    else if(k>left.size()+cntx){
        return find_kth_rank(right,k-left.size()-cntx);
    }
    else return x;

    
}
double distance(ll x1,ll y1,ll x2,ll y2){
    ll dist=(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    return sqrt(dist);
}
ll distSquare(ll x1,ll y1,ll x2,ll y2){
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}
pair<ll,vector<pair<ll,ll>>> CPdist(vector<pair<ll,ll>>&P){
    // cout<<P.size()<<endl;
    if(P.size()<=1)return {LLONG_MAX,{{-1,-1},{-1,-1}}};
    else if(P.size()==2){
        if(P[1].second<=P[0].second)swap(P[0],P[1]);
        return {distSquare(P[0].first,P[0].second,P[1].first,P[1].second),{P[0],P[1]}};
    }
    else{
        vector<ll>xcord;
        for(auto x:P)xcord.push_back(x.first);
        ll pmed=find_kth_rank(xcord,xcord.size()/2+1);
        
        vector<pair<ll,ll>>Pl,Pr;
        for(auto x:P){
            if(x.first<pmed)Pl.push_back(x);
            else if(x.first>pmed)Pr.push_back(x);
        }
        for(auto x:P){
            if(x.first!=pmed)continue;
            if(Pl.size()<=Pr.size())Pl.push_back(x);
            else Pr.push_back(x);
        }
        pair<ll,vector<pair<ll,ll>>>t1=CPdist(Pl);
        double del_l=sqrt(t1.first);
        pair<ll,vector<pair<ll,ll>>>t2=CPdist(Pr);        
        double del_r=sqrt(t2.first);
        double del=min(del_l,del_r);
        pair<ll,vector<pair<ll,ll>>>currAns;
        if(del==del_l)currAns=t1;
        else currAns=t2;
        vector<pair<ll,ll>>Strip_left,Strip_right;
        for(auto x:Pl){
            if(x.first>=pmed-del)Strip_left.push_back(x);
        }
        for(auto x:Pr){
            if(x.first<=pmed+del)Strip_right.push_back(x);
        }
        P.clear();
        ll i=0,j=0;
        while(i<Pl.size() && j<Pr.size()){
            if(Pl[i].second<Pr[j].second){
                P.push_back(Pl[i]);
                i++;
            }
            else{
                P.push_back(Pr[j]);
                j++;
            }
        }
        // cout<<P.size()<<endl;
        while(i<Pl.size()){P.push_back(Pl[i]);i++;}
        while(j<Pr.size()){P.push_back(Pr[j]);j++;}
        i=0;j=0;
        while(i<Strip_left.size() && j<Strip_right.size()){
            pair<ll,ll>a=Strip_left[i];
            pair<ll,ll>b=Strip_right[j];
            if(a.second<=b.second){
                for(ll w=j;w<min(j+4,(ll)Strip_right.size());w++){
                    ll d=distSquare(a.first,a.second,Strip_right[w].first,Strip_right[w].second);
                    if(d<currAns.first){
                        del=sqrt(d);
                        currAns={d,{a,Strip_right[w]}};
                    }
                }
                i++;
            }
            else{
                for(ll w=i;w<min((i+4),(ll)Strip_left.size());w++){
                    ll d=distSquare(b.first,b.second,Strip_left[w].first,Strip_left[w].second);
                    if(d<currAns.first){
                        del=sqrt(d);
                        currAns={d,{b,Strip_left[w]}};
                    }
                }
                j++;
            }
        }
        return currAns;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(4);

    ll n;cin>>n;vector<pair<ll,ll>>P(n);
    for(ll i=0;i<n;i++){
        cin>>P[i].first>>P[i].second;
    }
    pair<ll,vector<pair<ll,ll>>>ans=CPdist(P);//returns square of min distance and those 2 points having min distance 
    cout<<ans.first<<endl;
    
    return 0;
}
