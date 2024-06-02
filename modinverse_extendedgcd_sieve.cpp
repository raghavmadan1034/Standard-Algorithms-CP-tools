#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll mod=1e9+7;
bool is_square(float x){
    if(x>= 0){
        ll sr = sqrt(x);
        if(sr*sr==x) return true;
    }
    return false;
}
ll extended_gcd(ll a, ll b, ll &x, ll &y){  //ax + by = gcd(a,b)
    //this algorithm finds a way to represent gcd(a,b) in form of equation -ax+by=gcd(a,b)
    //finds x and y for them 
    vector<ll>r;
    x=0,y=1;
    ll rem=a%b;
    while(rem!=0){
        r.push_back(a/b);
        a=b;
        b=rem;
        rem=a%b;
    }
    reverse(r.begin(),r.end());
    for(ll i=0;i<r.size();i++){
        ll temp=x;
        x=y;
        y=temp-y*(r[i]);
    }
    return rem;
}
ll exp(ll x,ll y,ll p){//x^y %p ,returns exponent of x^y with mod p
    ll res=1;
    x%=p;
    while(y){
        if(y&1){
            res*=x;
            res%=p;
        }
        x*=x;
        x%=p;
        y>>=1;
    }
    return res;
}
ll modInverse(ll a,ll modulo){
    //for modInverse to exist gcd(a,modulo)=1 ,dw generally modulo is prime (1e9+7)
    return exp(a,modulo-2,modulo);//only if modulo is a prime number
    //if modulo is NOT prime
    ll x, y;
    ll g=extended_gcd(a,modulo,x,y);
    ll res=(x%modulo+modulo)%modulo;
    return res;
}
const ll N=2e5+5;
////////////////////////////////////////Seive Algorithm////////////////////////////////////////////////////////////////////////
vector<bool>Prime(N,1);						//calculates is_prime from 1 to N in O(Nlog(logN))
vector<ll>lp(N),hp(N);
vector<ll> prime_factors;
vector<ll>divisors[N];
 
void sieve(ll N){ 
    Prime[0]=Prime[1]=false;
    for(int i=2;i<N;i++){
        if(Prime[i]==true){
            lp[i]=hp[i]=i;
            for(int j=2*i;j<N;j+=i){
                Prime[j]=false;
                hp[j]=i;
                if(lp[j]==0){
                    lp[j]=i;
                }
            }
        }
    }
    for(int i=2;i<N;i++){        //Calculates divisors of all numbers from 1 to N in O(NlogN) (imp piece of code in reducing time complexity)
        for(int j=i;j<N;j+=i){
            divisors[j].pb(i);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //Note-If mod is different than 1e9+7 ,change the mod on the 4th line of this code
    //If mod is different than 1e9+7,before using modInverse(a,mod) check if mod is prime or NOT
    //If prime no problem ,if not prime comment out the first line of modInverse fxn and use extended gcd algorithm 
}
