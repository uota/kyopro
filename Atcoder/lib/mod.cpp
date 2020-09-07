ll mod=1000000007;

ll modinv(ll a, ll m){
    ll b=m,u=1,v=0;
    while(b){
        ll t=a/b;
        a-=t*b; swap(a,b);
        u-=t*v; swap(u,v);
    }
    u%=m;
    if(u<0){ u+=m; }
    return u;
}

ll modpow(ll a, ll n, ll m){
    ll ret=1;
    while(n>0){
        if(n&1){ ret=ret*a%m; }
        a=a*a%m;
        n>>=1;
    }
    return ret;
}

ll modC(ll n, ll k){
    const ll L=1e6;
    static ll fact[L], rfact[L];
    if(k==0) return 1;
    if(fact[0]==0){
        fact[0]=1;
        REP(i,1,L){                                                     
            fact[i]=(i*fact[i-1])%mod;
        }
    }
    return ((fact[n]*modinv(fact[n-k],mod))%mod*modinv(fact[k],mod))%mod;
}

ll modH(ll n, ll k){
    return modC(n+k-1,n-1);
}

class mll {
public:
	ll val;
    mll(int v){val=v;}
    mll operator + (mll m) { return mll((val + m.val + mod) % mod); } 
    mll operator - (mll m) { return mll((val - m.val + mod) % mod); }
    mll operator * (mll m) { return mll((val * m.val + mod) % mod); }
    mll operator / (mll m) { return mll((val * modinv(m.val, mod)) % mod); }
    void operator = (mll m) { val = m.val; }
    explicit operator ll() { return val; }

private:
    ll modinv(ll a, ll m){
        ll b=m,u=1,v=0;
        while(b){
            ll t=a/b;
            a-=t*b; swap(a,b);
            u-=t*v; swap(u,v);
        }
        u%=m;
        if(u<0){ u+=m; }
        return u;
    }
};
