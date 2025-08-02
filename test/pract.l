%{
#include<stdio.h>
%}

%%
0([01]*1) {printf("Accepted:%s\n",yytext);}
1([01]*0) {printf("Accepted:%s\n",yytext);}
[01]+     {printf("Rejected:%s\n",yytext);}
.|\n  
%%

int main(int argc,char **argv){
printf("Enter a string:\n");
yylex();
return 0;
}

int yywrap(){
return 1;
}
