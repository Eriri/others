#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);i++)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define pb push_back
typedef long long ll;

ll fpow(ll b,ll p,ll m){
	ll r=1;for(;p;p>>=1,(b*=b)%=m)if(p&1)(r*=b)%=m;return r;}

bool miller_rabin(ll n){
	if(n==1||n%2==0)return false;
	ll t,u;vector<ll> base={2,3,5,7,11,13,17,19,23,29,31,37,41};
	for(ll& b:base)if(b<n){
		for(t=__builtin_ctz(n-1),u=fpow(b,(n-1)>>t,n);t;t-=1,u=fpow(u,2,n)){
			if(fpow(u,2,n)==1&&u!=1&&u!=n-1)return false;}
		if(u!=1)return false;}
	return true;}

ll exgcd(ll a,ll b,ll& x,ll& y){
	if(!b){x=1;y=0;return a;}
	ll c=exgcd(b,a%b,y,x);
	y-=x*(a/b);return c;}

void generate_key_pair(){
	random_device rd;mt19937 gen(rd());
	uniform_int_distribution<ll> prime(2,1e5);
	ll p,q,r,n,e,d;
	do{
		do p=prime(gen); while(!miller_rabin(p));
		do q=prime(gen); while(!miller_rabin(q));
	}while(p==q);
	r=(p-1)*(q-1);n=p*q;
	uniform_int_distribution<ll> key(2,r);
	do e=key(gen); while(__gcd(e,r)!=1);
	exgcd(e,r,d,*new ll());d=(d%r+r)%r;
	cout<<"公钥(N,e)= "<<n<<" "<<e<<endl;
	cout<<"密钥(N,d)= "<<n<<" "<<d<<endl;}

int select_mode(vector<string> vs){
	int o;
	while(true){
		cout<<"请选择";rep(i,0,sz(vs))cout<<"["<<i<<"-"<<vs[i]<<"]";
		cout<<":";cin>>o;
		if(0<=o&&o<sz(vs)){
			cout<<"已选择:"<<vs[o]<<endl;
			return o;}}}

vector<ll> trans(string s,ll N){
	ll t=0;vector<ll> v;
	for(auto c:s){
		if((t<<8|c)>=N)v.pb(t),t=0;
		t=t<<8|c;}
	if(!t)v.pb(t);return v;}

string trans(vector<ll> v){
	string s,u;
	for(auto t:v){
		for(u.clear();t;u+=char(t&((1ll<<8)-1)),t>>=8);
		reverse(all(u));s+=u;}
	return s;}

vector<ll> ciphering(vector<ll> v,ll N,ll k){
	rep(i,0,sz(v))v[i]=fpow(v[i],k,N);return v;}


int main(){
	int o;string s;stringstream ss;ll N,e,d,t;vector<ll> v;
	while(1){
		o=select_mode({"生成密钥对","加密","解密","退出"});
		if(o==0)generate_key_pair();
		else if(o==1){
			cout<<"输入明文:";
			s.clear();while(!sz(s))getline(cin,s);
			cout<<"输入公钥(N,e):";cin>>N>>e;
			v=ciphering(trans(s,N),N,e);
			cout<<"加密后密文为:";
			for(auto t:v)cout<<t<<" ";cout<<endl;}
		else if(o==2){
			cout<<"输入密文组:";
			s.clear();while(!sz(s))getline(cin,s);
			ss.clear();ss<<s;v.clear();
			while(ss>>t)v.pb(t);
			cout<<"输入密钥(N,d):";cin>>N>>d;
			s=trans(ciphering(v,N,d));
			cout<<"解密后明文为:"<<s<<endl;}
		else break;}}
