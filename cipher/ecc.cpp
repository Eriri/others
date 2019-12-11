#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long ll;
typedef pair<ll,ll> pt;

ll A,B,P;//8161 9871 5227 9109 2081 3557 887
ll fpow(ll a,ll b){ll c=1;for(;b;b>>=1,(a*=a)%=P)if(b&1)(c*=a)%=P;return c;}
ll add(ll a,ll b){return (a+b)%P;}
ll sub(ll a,ll b){return (a-b+P)%P;}
ll mul(ll a,ll b){return a*b%P;}
ll divi(ll a,ll b){return a*fpow(b,P-2);}

pt inf={-1,0};
pt add(pt a,pt b){
	if(a==inf)return b;if(b==inf)return a;
	if(a.x==b.x&&add(a.y,b.y)==0)return inf;
	ll m,cx,cy;
	if(a.x!=b.x||a.y!=b.y)m=divi(sub(b.y,a.y),sub(b.x,a.x)),cx=sub(sub(mul(m,m),a.x),b.x);
	else m=divi(add(mul(3,mul(a.x,a.x)),A),mul(2,a.y)),cx=sub(mul(m,m),mul(2,a.x));
	cy=sub(mul(m,sub(a.x,cx)),a.y);
	return pt(cx,cy);}

pt fpow(pt a,ll b){pt c=inf;for(;b;b>>=1,a=add(a,a))if(b&1)c=add(a,c);return c;}

int main(){
	cout<<"随机生成椭圆曲线与基点G......"<<endl;
	
}
