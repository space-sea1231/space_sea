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
int t , n;
vector < pair < int , int > > e;
Re; signed main ()
{ 
  read ( t );
  while ( t -- )
  {
    printf("---%d---\n", t);
    e. clear ();
    read ( n );
    int p = n - 3;
    int z = ( p / 3 ) * 2;
    for ( rint i = 2 ; i <= 1 + n - z ; i ++ ) e. push_back ( { 1 , i } );
    if ( n >= 6 ) e. push_back ( { 2 , 3 } ) , e. push_back ( { 2 , 3 + z / 2 } );
    for ( rint i = 4 ; i <= 2 + z / 2 ; i ++ ) 
    {
      e. push_back ( { 2 , i } );
      e. push_back ( { 3 , i } );
    }
    sort ( e. begin () , e. end () );
    for ( auto [ u , v ] : e ) printf ("%d %d\n", u , v );
  }
  // return flush ( ) , tam;
  return flush ( ) , 0;
}