%{
#include <stdio.h>
%}

num(0|1)*0(0|1)*

%%
{num} {printf("accepted\n"); }
.+    {printf("not accepted\n"); }
\n    {return 0;}
%%
int main( )
{
  printf("Enter the string: ");
  yylex( );
  return 0;
  
}

