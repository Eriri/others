#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);i++)
#define sz(x) ((int)x.size())
#define pb push_back
#define x first
#define y second
#define fi first
#define se second
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
typedef long long ll;
typedef pair<ll,ll> pt;

bool isprime(ll p){for(ll b=2;b*b<=p;b++)if(p%b==0)return false;return true;}

ll A,B,P;
ll fpow(ll a,ll b){ll c=1;for(;b;b>>=1,(a*=a)%=P)if(b&1)(c*=a)%=P;return c;}
ll add(ll a,ll b){return (a+b)%P;}
ll sub(ll a,ll b){return ((a-b)%P+P)%P;}
ll mul(ll a,ll b){return a*b%P;}
ll divi(ll a,ll b){return a*fpow(b,P-2)%P;}

ll add(vector<ll> a){rep(i,1,sz(a))(a[0]+=a[i])%=P;return a[0];}
ll mul(vector<ll> a){rep(i,1,sz(a))(a[0]*=a[i])%=P;return a[0];}

pt inf={-1,0};
pt add(pt a,pt b){
	if(a==inf)return b;if(b==inf)return a;
	if(a.x==b.x&&add(a.y,b.y)==0)return inf;
	ll m,cx,cy;
	if(a.x!=b.x||a.y!=b.y)m=divi(sub(b.y,a.y),sub(b.x,a.x)),cx=sub(sub(mul(m,m),a.x),b.x);
	else m=divi(add(mul({3,a.x,a.x}),A),mul(2,a.y)),cx=sub(mul(m,m),mul(2,a.x));
	cy=sub(mul(m,sub(a.x,cx)),a.y);
	return pt(cx,cy);}

pt inv(pt a){
	if(a==inf)return inf;return {a.x,sub(P,a.y)};}

pt fpow(pt a,ll b){pt c=inf;for(;b;b>>=1,a=add(a,a))if(b&1)c=add(a,c);return c;}

int select_mode(vector<string> vs){
	int o;
	while(true){
		cout<<"请选择";rep(i,0,sz(vs))cout<<"["<<i<<"-"<<vs[i]<<"]";
		cout<<":";cin>>o;
		if(0<=o&&o<sz(vs)){
			cout<<"已选择:"<<vs[o]<<endl;
			return o;}}}

int main(){
	random_device rd;
	map<ll,vector<ll>> y2_y;
	map<pt,vector<pt>> pg;
	set<pt> pts;set<ll> allx;
	ll y2,k,s,r;pt b,t,G,K,C1,C2,D;int o,mx=0;
	while(true){
		o=select_mode({"加密","解密","退出"});
		if(o==0){
			cout<<"随机生成椭圆曲线与基点G"<<endl;
			do P=abs<ll>(rd())%1024+1024*256;while(!isprime(P));
			do A=rand()%P,B=rand()%P;while(add(mul({4,A,A,A}),mul({27,B,B}))==0);
			y2_y.clear();pts.clear();allx.clear();pg.clear();
			rep(y,1,P)y2_y[mul(y,y)].pb(y);
			rep(x,1,P){
				y2=add({mul({x,x,x}),mul(A,x),B});
				if(sz(y2_y[y2]))for(auto y:y2_y[y2])pts.insert({x,y}),allx.insert(x);}
			while(sz(pts)){
				b=t=*pts.begin();
				while(t!=inf)pg[b].pb(t),t=add(t,b);
				for(auto z:pg[b])pts.erase(z);}
			for(auto i:pg)if(sz(i.se)>mx)mx=sz(i.se),G=i.fi;
			cout<<"P="<<P<<" A="<<A<<" B="<<B<<" G=("<<G.x<<","<<G.y<<")"<<endl;
			cout<<"随机生成密钥对"<<endl;
			k=abs<ll>(rd())%sz(pg[G]);K=fpow(G,k);
			cout<<"私钥k="<<k<<",公钥K=("<<K.x<<","<<K.y<<")"<<endl;
			do{
				cout<<"输入明文数字(<P[="<<P<<"]):";cin>>s;
				if(allx.count(s))break;
				cout<<"无法编码至曲线"<<endl;
			}while(true);
			r=abs<ll>(rd())%P;
			C1=fpow(G,r);
			C2=add(pt(s,y2_y[add({mul({s,s,s}),mul(A,s),B})][0]),fpow(K,r));
			cout<<"密文点对为C1("<<C1.x<<","<<C1.y<<"),C2("<<C2.x<<","<<C2.y<<")"<<endl;}
		if(o==1){
			cout<<"依次输入P,A,B:";cin>>P>>A>>B;
			cout<<"输入基点坐标:";cin>>G.x>>G.y;
			cout<<"输入私钥k:";cin>>k;K=fpow(G,k);
			cout<<"输入密文点对C1点:";cin>>C1.x>>C1.y;
			cout<<"输入密文点对C2点:";cin>>C2.x>>C2.y;
			D=add(C2,inv(fpow(C1,k)));
			cout<<"明文数字为:"<<D.x<<endl;
		}
		if(o==2)break;
	}
			
	
}
