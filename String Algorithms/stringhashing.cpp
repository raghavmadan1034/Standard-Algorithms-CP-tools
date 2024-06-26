#include <bits/stdc++.h>
using namespace std;
#define ll long long

//Hash function can be used to compare any 2 substrings of a string in O(1) time (O(|S|) preprocessing time)
//Often used in pattern matching algorithms
class HashedString {
  private:
	// change M and B if you want
	static const ll M = 1e9 + 9;
    static const ll B;//Let B be selected randomly to make your solution unhackable

	// pow[i] contains B^i % M
	static vector<ll> pow;

	// p_hash[i] is the hash of the first i characters of the given string
    vector<ll> p_hash;

  public:
	HashedString( string &s) : p_hash(s.size() + 1) {
		while (pow.size() <= s.size())pow.push_back((pow.back() * B) % M); 

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	ll get_hash(ll start,ll end){
		ll raw_val =(p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
};

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
vector<ll> HashedString::pow = {1};
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng); //to make code unhackable

//Usage- To hash create hash of string  use- HashedString hs.("input string" )
//To get hash values of substrings use - hs.get_hash(starting index,ending index)  (0 based indexing)
int main(){
    //Sample usage-
    //Sample submission-https://www.codechef.com/viewsolution/1067640690
    string s;cin>>s;
    HashedString hs(s);
    ll cnt=0;
    for(ll i=0;i<n;i++){
        if(i<n/2 && hs.get_hash(0,i)==hs.get_hash(i+1,2*i+1))cnt++;
    }
                    
            
}

