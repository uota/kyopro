// 最大公約数
ll gcd(ll a, ll b){
    return (a%b)?gcd(b,a%b):b;
}

// 最小公倍数
ll lcm(ll a, ll b){
    return a/gcd(a,b)*b;
}

// 素因数分解
void fp(ll N, map<ll,ll> &d){
    if(N==1){ return; }
    ll n=N;
    for(ll i=2;;i++){
        while(n%i==0){ n/=i; d[i]++; }
        if(n==1){ break; }
        if(i*i>=N){ d[n]++; break; }
    }
}

// 階乗
ll F(ll n, ll stop=1){
    if(n==0) return 1;
    return n==stop?n:n*F(n-1,stop);
}

// 順列
ll P(ll n, ll r){
    return F(n)/F(n-r);
}

// 組合せ
ll C(ll n, ll r){
    return F(n,r+1)/F(n-r);
}

