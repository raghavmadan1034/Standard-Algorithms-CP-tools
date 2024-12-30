#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pb push_back
ll mod=1e9+7;
ll floor_custom(ll a,ll b){
    if((a>=0 && b>0)||(a<=0 && b<0))return a/b;
    else{
        if(a%b){
            return a/b-1;
        }
        else return a/b;
    }
}
ll ceil_custom(ll a,ll b){//ceil a/b
    if(a%b){
        return floor_custom(a,b)+1;
    }
    else return a/b;
}
bool is_square(float x){
    if(x>= 0){
        ll sr = sqrt(x);
        if(sr*sr==x) return true;
    }
    return false;
}
ll gcd(ll a, ll b){
    if (a == 0) return b;
    return gcd(b % a, a);
}
bool isprime(ll x){
    for(ll i=2;i*i<=x;i++){
        if(x%i==0)return false;
    }
    return true;
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
    if(gcd(a,modulo)!=1)return -1;
    if(isprime(modulo))return exp(a,modulo-2,modulo);//only if modulo is a prime number
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
vector<ll> spf(N + 1, 1);//Gives the smallest Prime factor of a number 
void sieve(ll N){ 
    Prime[0]=Prime[1]=false;
    for (ll p=2;p*p<=N;p++){
        if (Prime[p]) {
            for (ll i =p*p; i<=N;i+=p){
                Prime[i] = false;
            }
        }
    }
    spf[0]=0;
    for (ll i=2;i<=N;i++) {
        if(spf[i]==1){
            for (ll j=i;j<=N;j+=i){
                if (spf[j]==1)spf[j]=i;
            }
        }
    }
    for(int i=2;i<=N;i++){        //Calculates divisors of all numbers from 1 to N in O(NlogN) (imp piece of code in reducing time complexity)
        for(int j=i;j<=N;j+=i){
            divisors[j].pb(i);
        }
    }
}
void primeFactorsSieve(ll n,map<ll,ll>&m){ //PS-Call sieve() in Main before calling this function 
    while (n!=1){ 
        m[spf[n]]++;
		n/=spf[n]; 
	} 
}
//PS-The below 2 functions are copied from cp-algorithms.com ,Never tested in a contest yet.
ll blocksieveing(ll n) {//count no of primes till n in same complexity as SIEVE but space shortened to O(sqrt(n)+S)=O(sqrt(n)+1e4)
    const ll S = 10000;

    vector<ll> primes;
    ll nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 2, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    ll result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i])
                result++;
        }
    }
    return result;
}
vector<char> segmentedSieve(long long L, long long R) {//For finding Primes between range L to R
    // generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<char> isPrime(R - L + 1, true);
    for (long long i : primes)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    return isPrime;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //Note-If mod is different than 1e9+7 ,change the mod on the 4th line of this code
    //If mod is different than 1e9+7,before using modInverse(a,mod) check if mod is prime or NOT
    //If prime no problem ,if not prime comment out the first line of modInverse fxn and use extended gcd algorithm 
}
