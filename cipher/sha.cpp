#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);i++)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define pb push_back
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
typedef unsigned long long ull;
typedef unsigned int ui;
typedef unsigned char uc;
typedef vector<ui> block;
typedef vector<block> vb;

/*
ui Ch(ui x,ui y,ui z){return (x&y)^(~x&z);}//[0,19]
ui Parity(ui x,ui y,ui z){return x^y^z;}//[20,39][60,79]
ui Maj(ui x,ui y,ui z){return (x&y)^(x&z)^(y&z);}//[40,59]
ui Kt[4]={0x5a827999,0x6ed9eba1,0x8f1bbcdc,0xca62c1d6};//[0,19][20,39][40,59][60,79]
*/
ui f(ui x,ui y,ui z,int t){
	if(t<20)return (x&y)^((~x)&z);
	if(t<40)return x^y^z;
	if(t<60)return (x&y)^(x&z)^(y&z);
	if(t<80)return x^y^z;}
	
ui Kt(int t){
	if(t<20)return 0x5a827999;
	if(t<40)return 0x6ed9eba1;
	if(t<60)return 0x8f1bbcdc;
	if(t<80)return 0xca62c1d6;}
	
ui H0[5]={0x67452301,0xefcdab89,0x98badcfe,0x10325476,0xc3d2e1f0};

vb padding(string s){
	ull l=sz(s)*8;block b;vb v;ui t;
	s.pb((uc)(0x80));
	while(sz(s)*8%512!=448)s.pb((uc)(0x00));
	rep(i,0,8)s.pb((uc)(l>>((7-i)<<3)));
	rep(i,0,sz(s)/64){
		b.clear();
		rep(j,0,16){
			rep(k,0,4)((t<<=8)|=(uc)(s[i*64+j*8+k]));
			b.pb(t);}
		v.pb(b);}
	return v;}

ui rotl(int n,ui x){rep(i,0,n)x=(x<<n)|(x>>(32-n));return x;}

vector<ui> schedule(vb M){
	vector<ui> w,h;ui a,b,c,d,e,T;
	w.resize(80);rep(i,0,5)h.pb(H0[i]);
	rep(t,0,sz(M)){
		rep(i,0,16)w[i]=M[t][i];
		rep(i,16,80)w[i]=rotl(1,w[i-3]^w[t-8]^w[t-14]^w[t-16]);
		a=h[0],b=h[1],c=h[2],d=h[3],e=h[4];
		rep(i,0,80){
			T=rotl(5,a)+f(b,c,d,i)+e+Kt(i)+w[i];
			e=d;d=c;c=rotl(30,b);b=a;a=T;}
		rep(i,0,5)h[i]+=a;}
	return h;}


int main(){
	string s;vector<ui> md;
	cout<<"请输入需要哈希的数据:"<<endl;
	do getline(cin,s); while(sz(s)==0);
	md=schedule(padding(s));
	cout<<"160位的信息摘要为:"<<endl;
	rep(i,0,5)cout<<hex<<md[i]<<" ";cout<<endl;}
