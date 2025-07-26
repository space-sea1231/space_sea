#include <bits/stdc++.h>
using namespace std;
#define Re char y_y
#define rint register int
#define tam cerr << 1e3 * clock ( ) / CLOCKS_PER_SEC << 'm' << 's' << ' ' << ( &y_y - &x_x ) / 1024.0 / 1024.0 << 'M' << 'B' << '\n' , 0
char x_x;
const int N = 2e5 + 5;
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
int n , p[ N ] , t;
int low ( int x ) { return x & ( -x ); }
unsigned int tree[ N ];
void modify ( int x , int val )
{
  for ( rint i = x ; i <= n ; i += low ( i ) )
    tree[ i ] += val;
}
unsigned int ask ( int x , unsigned int res = 0 )
{
  for ( rint i = x ; i ; i -= low ( i ) )
    res += tree[ i ];
  return res;
}
void solve ()
{
  read ( n );
  for ( rint i = 1 ; i <= n ; i ++ )
    read ( p[ i ] ) , tree[ i ] = 0;
  unsigned int ans = 0;
  for ( rint i = 1 ; i <= n ; i ++ )
  {
    for ( rint j = i + 1 ; j <= n ; j ++ )
    {
      // if ( p[ i ] < p[ j ] )
      //   continue;
      swap ( p[ i ] , p[ j ] );
      unsigned res = 0 , d = 0;
      for ( rint k = 1 ; k <= n ; k ++ )
      {
        if ( p[ k ] < p[ k - 1 ] )
          d = 1;
        else
          d ++;
        res += d;
      }
      swap ( p[ i ] , p[ j ] );
      ans = max ( ans , res );
    }
  }
  print ( ans ) , endl;
}
Re; signed main ()
{ 
  freopen ( "wei.in" , "r" , stdin );
  freopen ( "wei.out" , "w" , stdout );
  read ( t );
  while ( t -- )
    solve ( );
  return flush ( ) , 0;
}