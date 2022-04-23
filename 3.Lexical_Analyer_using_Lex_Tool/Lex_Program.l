%{
#include <stdio.h>
%}
delim [\t]
ws {delim}+
letter [A-Za-z]
digit [0-9]
id _|$|{letter}({letter}|{digit}|_)*
num {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
%%
ws {printf("no action");}
int|char|short|float|auto|double|struct|break|if|else|long|switch|case|enum|register|typedef|extern|return|union|const|unsigned|continue|for|signed|void|default|goto|sizeof|volatile|do|static|while {printf("%s is a keyword",yytext);}
{id} {printf("%s is a identifier",yytext);}
{num} {printf("it is a number");}
"<" {printf("it is a relation operator less than");}
">" {printf("it is a relation operator greater than");}
">=" {printf("it is a relation operator greater than or equal");}
"<=" {printf("it is a relation operator less than or equal");}
"==" {printf("it is a relation operator equal");}
"<>" {printf("it is a relation operator not equal");}
";"|"("|")"|"."|"$"|":"|"#"|"["|"]"|"{"|"}"|"~"|"_"|"?" {printf("it is a special symbol");}
%%
int main()
{
yylex();
}
int yywrap()
{
return 0;
}
