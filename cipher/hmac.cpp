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
map<char,uc> M;

vb padding(string s){
	ull l=sz(s)*8;block b;vb v;ui t;
	s.pb((uc)(0x80));
	while(sz(s)*8%512!=448)s.pb((uc)(0x00));
	rep(i,0,8)s.pb((uc)(l>>((7-i)*8)));
	rep(i,0,sz(s)){
		t=(t<<8)|(uc)(s[i]);
		if((i+1)%4==0){
			b.pb(t);
			if(sz(b)==16){v.pb(b);b.clear();}}}
	return v;}

vb keypadding(string k){
	string s;ull l=sz(k)*4;block b;vb v;ui t;
	rep(i,0,sz(k)/2)s.pb(M[k[i<<1]]<<4|M[k[i<<1|1]]);
	if(sz(k)&1)s.pb(M[k.back()]<<4|(uc)(0x08)),s.pb((uc)(0x00));
	else s.pb((uc)(0x80));
	while(sz(s)*8%512!=448)s.pb((uc)(0x00));
	rep(i,0,8)s.pb((uc)(l>>((7-i)*8)));
	rep(i,0,sz(s)){
		t=(t<<8)|(uc)(s[i]);
		if((i+1)%4==0){
			b.pb(t);
			if(sz(b)==16){v.pb(b);b.clear();}}}
	return v;}


ui rotl(int n,ui x){return x=(x<<n)|(x>>(32-n));}

vector<ui> schedule(vb M){
	vector<ui> w,h;ui a,b,c,d,e,T;
	w.resize(80);rep(i,0,5)h.pb(H0[i]);
	rep(i,0,sz(M)){
		rep(t,0,16)w[t]=M[i][t];
		rep(t,16,80)w[t]=rotl(1,w[t-3]^w[t-8]^w[t-14]^w[t-16]);
		a=h[0],b=h[1],c=h[2],d=h[3],e=h[4];
		rep(t,0,80){
			T=rotl(5,a)+f(b,c,d,t)+e+Kt(t)+w[t];
			e=d;d=c;c=rotl(30,b);b=a;a=T;}
		h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;h[4]+=e;}
	return h;}

void init(){
	for(char i='0';i<='9';i++)M[i]=(uc)(i-'0');
	for(char i='a';i<='f';i++)M[i]=(uc)(i-'a'+10);
	for(char i='A';i<='F';i++)M[i]=(uc)(i-'A'+10);}

int main(){
	init();
	string s,k,im,om;vector<ui> t,md; block ok,ik;
	cout<<"请输入认证的数据:"<<endl;
	do getline(cin,s); while(sz(s)==0);
	cout<<"请输入密钥(任意长度16进制数):"<<endl;
	do getline(cin,k); while(sz(k)==0);
	if(sz(k)>128)t=schedule(keypadding(k));
	else{
		while(sz(k)<128)k.pb('0');t.resize(16);
		rep(i,0,16)rep(j,0,8)t[i]|=((ui)(M[k[(i<<3)+j]])<<(j<<2));}
	ok.resize(16);ik.resize(16);
	rep(i,0,sz(t))ok[i]=t[i]^0x5c,ik[i]=t[i]^0x36;
	rep(i,sz(t),16)ok[i]=0x5c,ik[i]=0x36;
	
	rep(i,0,16)rep(j,0,4)im.pb((uc)(ik[i]>>(j<<3)));im+=s;
	t=schedule(padding(im));
	
	rep(i,0,16)rep(j,0,4)om.pb((uc)(ok[i]>>(j<<3)));
	rep(i,0,sz(t))rep(j,0,4)om.pb((uc)(t[i]>>(j<<3)));

	md=schedule(padding(om));
	cout<<"密钥散列消息认证码为:"<<endl;
	rep(i,0,5)cout<<hex<<md[i]<<" ";cout<<endl;}
