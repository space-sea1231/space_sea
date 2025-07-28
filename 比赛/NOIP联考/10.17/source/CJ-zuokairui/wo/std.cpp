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
int t , n , a[ N ] , b[ N ] , tot , c[ N ];
bool vis[ N ] , tag[ N ];
void solve ( )
{
  read ( n );
  for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
    tag[ i ] = vis[ i ] = 0; tot = 0;
  for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
  {
    read ( a[ i ] ) , vis[ a[ i ] ] = 1;
  }
  for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
    if ( ! vis[ i ] )
      b[ ++ tot ] = i;
  int ans = 0 , cnt = 0;
  do
  {
    for ( rint i = 1 , j = 1 ; i <= ( n << 1 ) ; i ++ )
    {
      c[ i ] = a[ i ];
      if ( ! c[ i ] )
        c[ i ] = b[ j ++ ];
    }
    int res = 0;
    for ( rint i = 2 ; i <= ( n << 1 ) ; i += 2 )
      res += abs ( c[ i ] - c[ i - 1 ] );
    if ( res > ans )
    {
      ans = res , cnt = 1;
      endl;
      for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
        print ( c[ i ] ); endl;
    }
    else if ( res == ans )
    {
      cnt ++;
      for ( rint i = 1 ; i <= ( n << 1 ) ; i ++ )
        print ( c[ i ] ); endl;
    }
  } while ( next_permutation ( b + 1 , b + tot + 1 ) );
  print ( cnt ) , endl; endl;
}
Re; signed main ()
{ 
  // freopen ( "wo.in" , "r" , stdin );
  // freopen ( "std.out" , "w" , stdout );
  read ( t );
  while ( t -- )
    solve ( );
  // return flush ( ) , tam;
  return flush ( ) , 0;
}
/*
1 2 3 5 4 6 
1 2 3 5 6 4 
1 2 3 6 4 5 
1 2 3 6 5 4 
6 


*/