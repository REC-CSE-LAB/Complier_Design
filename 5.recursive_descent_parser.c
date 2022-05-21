#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i = 0, flag_accept = 0, flag_error = 0;
void E_Prime ( const char str [] );
void T ( const char str [] );
void T_Prime ( const char str[] );
void F ( const char str[] );
void id ( const char str [] );
void E ( const char str [] );

int main()
{
	char str[30];

	puts( "Enter an arithmetic : " );
	gets(str);
		
	E( str );
	
	if( flag_accept == 1 && flag_error == 0 )
		printf("Accepted...!!!");
	else
		printf("Rejected...!!!");
	
	return 0;
}

void E ( const char str[] )
{
	T( str );
	E_Prime( str );
}

void E_Prime ( const char str[] )
{
	if( str[i++] == '+' )
	{
		T( str );
		E_Prime( str );
	}
	else
	{
		flag_error = 1;
		return ;
	}
}

void T ( const char str[] )
{
	F ( str );
	T_Prime( str );
}

void T_Prime ( const char str[] )
{
	if( str[i++] == '*' )
	{
		F( str );
		T_Prime( str );
	}
	else
	{
		flag_error = 1;
		return ;
	}
		
}

void F ( const char str[] )
{
	if( str[i++]  == '(' && str[strlen(str)-1] == ')' )
	{
		E( str );
	}
	else
	{
		id( str );
	}
}

void id ( const char str[] )
{
	char ch = str[i++];
	if ( isalpha(ch) || ch == '_' )
	{
		int flag = 0;
		while( i < strlen(str) )
		{
			ch = str[i++];
			if( !isalnum(ch) || ch != '_' )
			{
				flag =1;
				break;
			}
		}
		if(flag)
		{
			flag_accept = 1;
		}
	}
}
	
		
