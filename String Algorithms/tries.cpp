#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll SIZE=26;
struct Node{
    Node*links[SIZE];
    Node(){
        for(ll i=0;i<SIZE;i++)links[i]=NULL;
    }
    bool flag=false;//tells about the end of the word
    ll cntPrefix=0;//tells the number of strings having a prefix equal to the string made from root till reaching that node
    ll end_words=0;//tells the number of proper strings ending on that node
    //if we insert the word multiple times in trie ,end_words increases 
    //Also helps in deletion, eg abab is presnt in trie but you are asked to delete aba ,end_words=0=>cant delete
    bool containsKey(char c){
        return (links[c-'a']!=NULL);
    }
    Node* get(char c){
        return links[c-'a'];
    }
    void put(char c,Node*node){
        links[c-'a']=node;
    }
};
class Trie{
    private:Node*root;
    public:
    Trie(){
        root=new Node();
    }
    void insert(string s){
        Node* node=root;
        for(ll i=0;i<s.length();i++){
            if(!node->containsKey(s[i])){
                node->put(s[i],new Node());
            }
            node=node->get(s[i]);//moves to the reference trie 
            node->cntPrefix++;
        }
        node->end_words++;
    }
    bool search(string s){
        Node*node=root;
        for(ll i=0;i<s.length();i++){
            if(!node->containsKey(s[i]))return false;
            else node=node->get(s[i]);//move the node to reference trie
        }
        return node->end_words>0;
    }
    bool startsWith(string prefix){
        Node*node=root;
        for(ll i=0;i<prefix.length();i++){
            if(!node->containsKey(prefix[i]))return false;
            else node=node->get(prefix[i]);
        }
        return true;
    }
    ll countWordsEqualTo(string s){
        Node* node=root;
        for(ll i=0;i<s.length();i++){
            if(node->containsKey(s[i]))node=node->get(s[i]);
            else return 0;
        }
        return node->end_words;
    }
    ll countWordsStartingWith(string s){
        Node* node=root;
        for(ll i=0;i<s.length();i++){
            if(node->containsKey(s[i]))node=node->get(s[i]);
            else return 0;
        }
        return node->cntPrefix;
    }
    void deleteString(string s){
        if(!search(s))return;//agar string present hi nhi hai toh kuch nhi hoga delete

        Node*node=root;
        for(ll i=0;i<s.length();i++){
            if(node->containsKey(s[i])){
                node=node->get(s[i]);
                node->cntPrefix--;
            }
            else return;
        }
        node->end_words--;
    }
    string maxXOR(string s){
        //string s is Binary representation of number such that i=0 contains the highest bit
        //and i=s.length()-1 contains the lowest bit
        Node*node=root;
        string ans;
        //WARNING-BEFORE USING THIS CHANGE SIZE=2 to AVOID MLE 
        //CHANGE the containsKey ,get and put function from links[c-'a'] to links[c-'0']
        for(ll i=0;i<s.length();i++){
            char reqd=(s[i]-'0')^1+'0';
            if(node->containsKey(reqd)){
                ans.push_back(reqd);
                node=node->get(reqd);
            }
            else{
                ans.push_back(s[i]);
                node=node->get(s[i]);
            }
        }
        //returns the binary string among the all strings with whom we should take this XOR to maximize it 
        return ans;
    }

};
int main(){
    Trie trie;
    trie.insert("hello");
    trie.insert("hey");
    trie.deleteString("h");
    trie.deleteString("h");
    cout<<trie.search("hello")<<endl;
    cout<<trie.countWordsStartingWith("he")<<endl;
}
