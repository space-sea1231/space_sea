#include <bits/stdc++.h>
#define int long long
using namespace std;
#define Re char y_y
#define rint register int
#define tam cerr << 1e3 * clock ( ) / CLOCKS_PER_SEC << 'm' << 's' << ' ' << ( &y_y - &x_x ) / 1024.0 / 1024.0 << 'M' << 'B' << '\n' , 0
char x_x;
const int N = 3e6 + 5 , mod = 998244353;
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
int t , n , a[ N ];
int sm[ N ] , bi[ N ] , tsm , tbi;
int S[ N ] , B[ N ] , tS , tB;
int fac[ N ] , inv[ N ];
bool vis[ N ];
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
int low ( int x ) { return x & ( - x ); }
int tree[ N ];
void modify ( int x , int val )
{
  for ( rint i = x ; i <= ( n << 1 ) ; i += low ( i ) )
    tree[ i ] += val;
}
int ask ( int x , int res = 0 )
{
  for ( rint i = x ; i ; i -= low ( i ) )
    res += tree[ i ];
  return res;
}
void solve ( )
{
  read ( n ); tsm = tbi = tS = tB = 0;
  for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
    read ( a[ i ] ) , vis[ a[ i ] ] = 1;
  for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
    vis[ a[ i ] ] = 1;
  for ( rint i = 1 ; i <= n ; i ++ )
  {
    if ( vis[ i ] )
      continue;
    sm[ ++ tsm ] = i;
  }
  for ( rint i = n + 1 ; i <= ( n << 1 ) ; i ++ )
  {
    if ( vis[ i ] )
      continue;
    bi[ ++ tbi ] = i;
  }
  for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
  {
    if ( ! a[ i ] )
      continue;
    if ( a[ i ] && a[ i & 1 ? i + 1 : i - 1 ] )
      continue;
    if ( a[ i ] <= n )
      S[ ++ tS ] = a[ i ];
    else
      B[ ++ tB ] = a[ i ];
  }
  sort ( S + 1 , S + tS + 1 );
  sort ( B + 1 , B + tB + 1 );
  int ans = 1;
  if ( tbi < tS )
  {
    for ( rint i = 1 ; i <= tS ; i ++ )
      modify ( S[ i ] , 1 );
    for ( rint i = tsm - ( tS - tbi ) + 1 ; i <= tsm ; i ++ )
    {
      ans *= ask ( sm[ i ] );
      modify ( sm[ i ] , -1 );
    }
    ( ans *= A ( tbi , tbi ) ) %= mod;
    tbi = 0 , tsm = tsm - ( tS - tbi ) + 1;
  }
  else if ( tsm < tB )
  {
    for ( rint i = 1 ; i <= tB ; i ++ )
      modify ( B[ i ] , 1 );
    for ( rint i = tbi - ( tB - tsm ) + 1 ; i <= tbi ; i ++ )
    {
      ans *= ask ( bi[ i ] );
      modify ( bi[ i ] , -1 );
    }
    ( ans *= A ( tbi , tbi ) ) %= mod;
    tsm = 0 , tbi = tbi - ( tB - tsm ) + 1;
  }
  else
  {
    ( ans *= ( A ( tS , tbi ) * A ( tB , tsm ) % mod ) ) %= mod;
    tsm -= tS , tbi -= tB;
  }
  int cnt3 = 0;
  for ( rint i = 1 ; i <= ( n << 1 ) ; i += 2 )
    if ( a[ i ] == 0 && a[ i + 1 ] == 0 )
      cnt3 ++;
  if ( tsm < tbi )
    swap ( tsm , tbi );
  if ( cnt3 )
    ( ans *= A ( tsm , cnt3 ) * A ( tbi , cnt3 ) % mod * ksm ( 2 , tsm ) % mod ) %= mod;
  print ( ans );
}
Re; signed main ()
{ 
  // freopen ( "wo.in" , "r" , stdin );
  // freopen ( "wo.out" , "w" , stdout );
  fac[ 0 ] = inv[ 0 ] = 1;
  for ( rint i = 1 ; i < 1e6 + 1 ; i ++ )
    fac[ i ] = 1ll * fac[ i - 1 ] * i % mod , inv[ i ] = ksm ( fac[ i ] , mod - 2 );
  read ( t );
  while ( t -- )
    solve ( );
  return flush ( ) , 0;
}
/*
0 6 0 2 8 5 0 1 11 0 4 0 13 9 
*/