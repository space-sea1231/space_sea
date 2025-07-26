#include <bits/stdc++.h>
using namespace std;
#define Re char y_y
#define rint register int
#define tam cerr << 1e3 * clock ( ) / CLOCKS_PER_SEC << 'm' << 's' << ' ' << ( &y_y - &x_x ) / 1024.0 / 1024.0 << 'M' << 'B' << '\n' , 0
char x_x;
const int N = 1e5 + 5;
char buf[ 1 << 23 ] , *p1 = buf , *p2 = buf , obuf[ 1 << 23 ] , *O = obuf;
#define getchar() ( p1 == p2 && ( p2 = ( p1 = buf ) + fread( buf , 1 , 1 << 21 , stdin ) , p1 == p2 ) ? EOF : *p1 ++ )
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
template <class S>
inline void print ( S x )
{
  stack < char > s;
  if ( x == 0 ) return pc ( '0' ) , pc ( ' ' ) , void ();
  if ( x < 0 ) x = - x , pc ( '-' );
  while ( x ) { s. push ( x % 10 + 48 ) , x /= 10; }
  while ( ! s. empty () ) pc ( s. top () ) , s. pop ();
  putchar ( ' ' );
}
template <class S , class ...Args>
inline void print ( S x , Args ...y ) { print ( x ) , print ( y ... ); }
#undef pc
#define endl putchar ( '\n' )

Re; signed main ()
{
  system ( "g++ -o data data.cpp -std=c++14" );
  system ( "g++ -o std std.cpp -std=c++14" );
  system ( "g++ -o wo wo.cpp -std=c++14" );
  int cnt = 0;
  while ( cnt < 10000000 )
  {
    system ( "./data" );
    system ( "./wo" );
    system ( "./std" );
    if ( system ( "diff wo.out std.out -Bb" ) )
      return cout << "WA on " << ++ cnt , 0;
    cout << "AC on " << ++ cnt << '\n';
  }
  return tam;
  return 0;
}