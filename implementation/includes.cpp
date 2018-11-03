#include <bits/stdc++.h>


using namespace std;

# define EPS 1.0E-12
# define INF 1E18
# define MOD 1000000007
# define MAX_SIZE 100000
# define PI 3.14159265358979

typedef long long ll;
typedef unsigned long long ull;
typedef double dl;

ll sqr(ll x) {
	return x*x;
}

ll lcm(ll a, ll b) {
	return (a*b) / __gcd(a, b);
}

int sign(ll d) {
	if (d == 0LL) return 0;
	return d > 0LL ? 1 : -1;
}

int fsign(dl d) {
	if (d - EPS > 0.0)return 1;
	if (d + EPS < 0.0)return -1;
	return 0;
}

int fequal(dl a, dl b){
	cout << fsign(a - b) << '\n';
	return !fsign(a - b);
}

ll getRand(){
    ll A = (ll)rand();
    ll B = (ll)rand();
    return (((A*B)%MOD)+MOD)%MOD;
}

double radToDegree(double angle){
    return (angle * 180.0) / PI;
}

ll root(ll x) {
	ll l = 0, r = 1E009;
	while (l < r - 1) {
		ll m = (l + r) / 2;
		if (m * m > x)
			r = m;
		else
			l = m;
	}
	return l;
}

bool isInteger(double d){
	return !(fabs(d - floor(d)) > EPS);
}



// int main () {
// 	double a = 0.1;
//
// }
