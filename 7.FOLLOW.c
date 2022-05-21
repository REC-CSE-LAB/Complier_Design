#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nop, m = 0;
char prod[10][10], res[10];

void FIRST ( char c );
void FOLLOW ( char c );
void result ( char c );

int main()
{
	int i;
	int choice;
	char c;
	
	printf("Enter the no. of productions : ");
	scanf("%d",&nop);
	puts("Enter the production string like \"E=E+T\" \nand epsilon as #");
	
	for( i = 0; i < nop; ++i )
	{
		printf("Enter production Number %d : ",i+1);
		scanf("%s",prod[i]);
	}
	do
	{
		m = 0;
		memset( res, '\0', sizeof(res) );
		
		printf("Find FOLLOW of --> ");
		scanf(" %c",&c);
		
		if( isupper(c) )
			FOLLOW(c);
		else
		{
			printf("Not Possible");
			return 0;
		}
		
		printf("Follow (%c) = { ", c);
		for( i = 0; i < m; ++i )
			printf("%c ", res[i] );
		printf(" }\n");
		
		printf("Do you want to continue(Press 1 to continue...) ? ");
		scanf("%d",&choice);
	} while( choice == 1 );
		
	return 0;
}

void FOLLOW ( char c )
{
	int i, j;
	if( prod[0][0] == c )
		result('$');
	for( i = 0; i < nop; ++i )
	{
		for( j = 2; j <= strlen(prod[i]); ++j )
		{
			if( prod[i][j] == c )
			{
				if ( prod[i][j+1] != '\0' )
					FIRST( prod[i][j+1] != '\0' );
				if ( prod[i][j+1] == '\0' && c != prod[i][0] )
					FOLLOW( prod[i][0] );
			}
		}
	}
	return ;
}

void FIRST ( char c )
{
	int k;
	if ( !( isupper(c) ) )
		result(c);
	for( k = 0; k < nop; ++k )
	{
		if( prod[k][0] == c )
		{
			if ( prod[k][2] == '#' )
				FOLLOW( prod[k][0] );
			else if ( prod[k][2] == c )
				return ;
			else if ( islower(prod[k][2]) )
				result (prod[k][2]);
			else
				FIRST ( prod[k][2] );
		}
	}
	return ;
}

void result ( char c )
{
	int i;
	for( i = 0; i <= m; ++i )
		if( res[i] == c )
			return ;
	res[m++] = c;
}
