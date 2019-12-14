#include <bits/stdc++.h>
#define rep(i,s,t) for(int i=(s);i<(t);i++)
#define per(i,s,t) for(int i=((t)-1);i>=s;i--)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;

using ull=unsigned long long;
using vu=vector<ull>;
using vi=vector<int>;

vi IP[2]={
	{58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7},
	{40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25}};
vi E={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,
	12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
	22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
vi PC_1={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,
	59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,
	31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,
	29,21,13,5,28,20,12,4};
vi PC_2={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
vi P={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
vi S_BOX[8]={
	{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
	{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
	{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
	{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
	{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
	{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
	{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
	{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

ull permutation(ull x,vi p){
	ull y=0;rep(i,0,sz(p))y|=((x>>(p[i]-1))&1ull)<<i;return y;}

ull substitution(ull x,vi sb){
	return sb[16*(((x&32ull)>>4)+(x&1ull))+((x&30ull)>>1)];}

ull leftshift(ull x){
	return ((x<<1)&((1ull<<28)-1))|(x>>27);}

ull feistel(ull x,ull k){
	x=permutation(x,E)^k;ull y=0;
	rep(i,0,8)y|=substitution((x>>(6*i))&63ull,S_BOX[i])<<(4*i);
	return permutation(y,P);}

ull enciphering(ull x,vector<vu> k,int o){
	x=permutation(x,IP[0]);pair<ull,ull> lr=mp(x&((1ull<<32)-1),x>>32);
	rep(i,0,16)lr=mp(lr.se,lr.fi^feistel(lr.se,k[o][i]));
	return permutation(lr.se|(lr.fi<<32),IP[1]);}

vector<vu> schedule(ull k){
	k=permutation(k,PC_1);vu t,s;pair<ull,ull> cd=mp(k&((1ull<<28)-1),k>>28);
	rep(i,0,16){
		cd=mp(leftshift(cd.fi),leftshift(cd.se));
		t.pb(permutation(cd.fi|(cd.se<<28),PC_2));}
	s=t;reverse(all(s));return {t,s};}

vu input_text(){
    string s;vu t;ull x;
    while(sz(s)==0)getline(cin,s);s+=string(8-sz(s)%8,0);
    rep(i,0,sz(s)/8){x=0;rep(j,0,8)x|=((ull)s[i*8+j])<<(8*j);t.pb(x);}
	return t;}

vu input_data(){
	string s;stringstream ss;vu t;ull x;
	while(sz(s)==0)getline(cin,s);
	ss.clear();ss<<s;while(ss>>hex>>x)t.pb(x);
	return t;}

void output_text(vu s){
	string t;
	rep(i,0,sz(s))rep(j,0,8)t+=(char)((s[i]>>(8*j))&255ull);
	cout<<t<<endl;}

void output_data(vu s){
	rep(i,0,sz(s))cout<<hex<<s[i]<<" ";cout<<endl;}

int select_mode(vector<string> vs){
	int o;
	while(true){
		cout<<"请选择";rep(i,0,sz(vs))cout<<"["<<i<<"-"<<vs[i]<<"]";
		cout<<":";cin>>o;
		if(0<=o&&o<sz(vs)){
			cout<<"已选择:"<<vs[o]<<endl;
			return o;}}}
	
	

int main(){
	ull key,iv;vu x;vector<vu> ks;int o;
	random_device rd;uniform_int_distribution<ull> dis(0ull,~0ull);key=dis(rd);
	while(true){
		o=select_mode({"加密","解密","退出"});
		if(o==0){
			cout<<"输入明文:";x=input_text();
			cout<<"明文为:";output_text(x);
			if(select_mode({"随机生成密钥","手动输入密钥"})==0){key=dis(rd);}
			else{cout<<"输入密钥(16位16进制数):";cin>>hex>>key;}
			cout<<"密钥为(16位16进制数):"<<hex<<key<<endl;
			ks=schedule(key);
			if(select_mode({"ECB","CBC"})==0){rep(i,0,sz(x))x[i]=enciphering(x[i],ks,0);}
			else{
				if(select_mode({"随机生成初始化向量","手动输入初始化向量"})==0){iv=dis(rd);}
				else{cout<<"输入初始化向量(16位16进制数):";cin>>hex>>iv;}
				cout<<"初始化向量(16位16进制数)为:"<<hex<<iv<<endl;
				x[0]=enciphering(x[0]^iv,ks,0);rep(i,1,sz(x))x[i]=enciphering(x[i]^x[i-1],ks,0);}
			cout<<"加密后密文为(分组16位16进制数):";output_data(x);}
		if(o==1){
			cout<<"输入分组密文(分组16位16进制数):";x=input_data();
			cout<<"分组密文(分组16位16进制数)为:";output_data(x);
			cout<<"输入密钥(16位16进制数):";cin>>hex>>key;
			cout<<"密钥(16位16进制数)为:"<<hex<<key<<endl;
			ks=schedule(key);
			if(select_mode({"ECB","CBC"})==0){rep(i,0,sz(x))x[i]=enciphering(x[i],ks,1);}
			else{
				cout<<"输入初始化向量(16位16进制数):";cin>>hex>>iv;
				cout<<"初始化向量(16位16进制数)为:"<<hex<<iv<<endl;
				per(i,1,sz(x))x[i]=x[i-1]^enciphering(x[i],ks,1);x[0]=iv^enciphering(x[0],ks,1);}
			cout<<"解密后明文为:";output_text(x);}
		if(o==2)break;}}



