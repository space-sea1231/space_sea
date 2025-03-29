#include <bits/stdc++.h>
#define int long long
using namespace std;
#define Re char y_y
#define rint register int
#define tam cerr << 1e3 * clock ( ) / CLOCKS_PER_SEC << 'm' << 's' << ' ' << ( &y_y - &x_x ) / 1024.0 / 1024.0 << 'M' << 'B' << '\n' , 0
char x_x;
const int N = 16 + 1 , mod = 998442353 , M = 1e6 + 5;
char buf[ 1 << 23 ] , *p1 = buf , *p2 = buf , obuf[ 1 << 23 ] , *p3 = obuf;
#define getchar( ) ( p1 == p2 && ( p2 = ( p1 = buf ) + fread( buf , 1 , 1 << 23 , stdin ) , p1 == p2 ) ? EOF : *p1 ++ )
#define putchar( x ) ( p3 - obuf < 1 << 23 ) ? ( *p3 ++ = x ) : ( fwrite ( obuf , p3 - obuf , 1 , stdout ) , p3 = obuf , * p3 ++ = x )
template < class T >
inline void read ( T & s )
{
  s = 0; 
  bool q = false;
  char c = getchar ();
  while ( ! isdigit ( c ) ) { if (c == '-') q = true; c = getchar (); }
  while (isdigit (c) ) { s = (s << 1) + (s << 3) + (c ^ 48); c = getchar (); }
  if (q) s = -s;
}
template < class T , class ...Args >
inline void read ( T &s , Args &...x ) { read ( s ) , read ( x... ); }
#define pc putchar
stack < char > so;
template <class S>
inline void print ( S x )
{
  if ( x == 0 ) return pc ( '0' ) , pc ( ' ' ) , void ();
  if ( x < 0 ) x = - x , pc ( '-' );
  while ( x ) { so. push ( x % 10 + 48 ) , x /= 10; }
  while ( ! so. empty () ) pc ( so. top () ) , so. pop ();
  putchar ( ' ' );
}
template <class S , class ...Args>
inline void print ( S x , Args ...y ) { print ( x ) , print ( y ... ); }
#undef pc
inline void flush ( ) { fwrite ( obuf , p3 - obuf , 1 , stdout ) , p3 = obuf; }
#define endl putchar ( '\n' )
int t , n , m , p[ N ][ N ] , num[ N ][ N ] , dis[ N ][ N ]; int s[ N ];
int f[ 1 << N ];
int fac[ M ] , inv[ M ];
int ksm ( int x , int k , int res = 1 )
{
  while ( k )
  {
    if ( k & 1 )
      ( res *= x ) %= mod;
    ( x *= x ) %= mod;
    k >>= 1;
  }
  return res;
} 
int A ( int x , int y ) { return fac[ y ] * inv[ y - x ] % mod; }
int C ( int x , int y ) { return fac[ y ] * inv[ y - x ] % mod * inv[ x ] % mod; }
void solve ( )
{
  read ( n , m );
  for ( rint i = 1 ; i <= m ; i ++ )
  {
    for ( rint j = 1 ; j <= n ; j ++ )
    {
      read ( p[ i ][ j ] );
    }
  }
  for ( rint i = 1 ; i <= m ; i ++ )
    read ( s[ i ] );
  if ( n == 1 )
  {
    int ans = 1e9;
    int mn , mx; mn = 1e9 , mx = - 1e9;
    for ( rint i = 1 ; i <= m ; i ++ )
      mn = min ( mn , p[ i ][ 1 ] ) , mx = max ( mx , p[ i ][ 1 ] );
    for ( rint i = 1 ; i <= m ; i ++ ) if ( s[ i ] )
      ans = min ( ans , min ( abs ( p[ i ][ 1 ] - mn ) , abs ( p[ i ][ 1 ] - mx ) ) + abs ( mn - mx ) );
    print ( ans , 1 ) , endl;
    return;
  }
  if ( m == 2 )
  {
    int ans = 0;
    for ( rint i = 1 ; i <= n ; i ++ )
      ans += abs ( p[ m ][ i ] - p[ 1 ][ i ] );
    print ( ans ); 
    int res = 1;
    for ( rint i = 1 ; i < n ; i ++ )
    {
      ( res *= C ( abs ( p[ m ][ i ] - p[ 1 ][ i ] ) , ans ) ) %= mod;
      ans -= abs ( p[ m ][ i ] - p[ 1 ][ i ] );
    }
    if ( s[ m ] && s[ 1 ] )
      res *= 2;
    print ( res % mod ) , endl;
    return;
  }
}
Re; signed main ()
{ 
  freopen ( "ge.in" , "r" , stdin );
  freopen ( "ge.out" , "w" , stdout );
  fac[ 0 ] = inv[ 0 ] = 1;
  for ( rint i = 1 ; i < 1e6 + 1 ; i ++ )
    fac[ i ] = 1ll * fac[ i - 1 ] * i % mod , inv[ i ] = ksm ( fac[ i ] , mod - 2 );
  read ( t );
  while ( t -- )
    solve ( );
  return flush ( ) , 0;
}