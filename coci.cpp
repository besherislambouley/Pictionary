/* 
 * we iterate over days from m to 1 adding edges between the i th node and its multiples 2*i , 3*i .. with value m-i+1
 * we only add edges if those to nodes are in different components , then we only add n-1 edges forming a tree 
 * now the answer of nodes a,b is the maximum value on the path from a to b , use sparce table to answer that in O (log n ) 
*/
    #define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
    #include <bits/stdc++.h>
    using namespace std;
    #define sqr 500
    #define mid (l+r)/2
    #define pb push_back
    #define ppb pop_back
    #define fi first
    #define se second
    #define lb lower_bound
    #define ub upper_bound
    #define ins insert
    #define era erase
    #define C continue
    #define mem(dp,i) memset(dp,i,sizeof(dp))
    #define mset multiset
    typedef long long ll;
    typedef short int si;
    typedef long double ld;
    typedef pair<int,int> pi;
    typedef pair<ll,ll> pll;
    typedef vector<int> vi;
    typedef vector<ll> vll;
    typedef vector<pi> vpi;
    typedef vector<pll> vpll;
    const ll inf=1e18;
    const ll mod=1e9+7;
    const ld pai=acos(-1);
    int n , m , q ;
    //
    vpi v[100009] ;
    int dp[100009][20] , w[100009] , Mx[100009][20] ;
    void dfs ( int node , int p ) {
            dp [node][0] = p ;
            w [node] = w[p] + 1 ;
            for ( auto U : v[node] ) {
                    int u = U.fi ;
                    int x = U.se ;
                    if ( u == p ) C ;
                    Mx [u][0] = x ;
                    dfs ( u , node ) ;
            }
    }
    void build () {
            dfs( 0 , 0 ) ;
            for ( int j = 1 ; j < 20 ; j ++ ) {
                    for ( int i = 0 ; i < n ; i ++ ) {
                            dp [i][j] = dp [ dp[i][j-1] ][ j-1 ] ;
                            Mx [i][j] = max ( Mx [ i ][ j-1 ] , Mx  [ dp[i][j-1] ][ j-1 ] ) ;
                    }
            }
    }
    int query ( int a , int b ) {
            int ans = 0 ;
            if ( w[a] < w[b] ) swap ( a , b ) ;
            int l = w[a] - w[b] ;
            for ( int i = 0 ; i < 20 ; i ++ ) {
                    if ( ( l & ( 1<<i ) ) ) {
                            ans = max ( ans , Mx[a][i] ) ;
                            a = dp [a][i] ;
                    }
            }
            if ( a == b ) return ans ;
            for ( int i = 19 ; i >= 0 ; i -- ) {
                    if ( dp [a][i] != dp [b][i] ) {
                            ans = max ( ans , Mx[a][i] ) ;
                            ans = max ( ans , Mx[b][i] );
                            a = dp [a][i] ;
                            b = dp [b][i] ;
                    }
            }
            ans = max ( ans , Mx [a][0] ) ;
            ans = max ( ans , Mx [b][0] ) ;
            return ans ;
    }

    //
    int p[100009] ;
    int get ( int node ) {
            if ( node == p[node] ) return node ;
            return p[node] = get ( p [node] ) ;
    }
    void merge ( int a , int b , int len ) {
            int A = get ( a ) ;
            int B = get ( b ) ;
            if ( A == B ) return ;
            v[a] .pb ( { b , len } ) ;
            v[b] .pb ( { a , len } ) ;
            p [B] = A ;
    }
    int main () {
            cin >> n >> m >> q ;
            for ( int i = 0 ; i < n ; i ++ ) {
                    p[i] = i ;
            }
            for ( int i = m ; i >= 1 ; i -- ) {
                    vi nodes ;
                    for ( int j = i ; j <= n ; j += i ) {
                            nodes .pb ( j -1 ) ;
                    }
                    for ( int j = 1 ; j < nodes.size() ; j ++ ) {
                            merge ( nodes[0] , nodes[j] , m-i+1 ) ;
                    }
            }
            build () ;
            while ( q -- ) {
                    int a , b ;
                    cin >> a >> b ;
                    a -- , b -- ;
                    cout << query ( a , b ) << endl ;
            }
    }
