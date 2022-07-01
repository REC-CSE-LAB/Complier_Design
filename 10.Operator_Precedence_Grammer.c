#include <stdio.h>
#include <ctype.h>
#include <string.h>

char prod[10][10];

int main()
{
	int i,j,nop;
	char f1, f2;

	printf("How many Number of Productions ? : ");
	scanf("%d",&nop);
	
	puts("\nEnter the production String like \"E=E+T\"\nand choose epsilon as #\n");
	for( i = 0; i < nop; ++i )
	{
		printf("Enter the Production Number %d : ", i+1 );
		scanf("%s",prod[i]);
	}

	for( i = 0; i < nop; ++i )
	{
		for( j = 2; j < strlen(prod[i]); ++j )
		{
			f1 = prod[i][j];
			f2 = prod[i][j+1];

			if( ( prod[i][2] == '#' ) || ( isupper(f1) && isupper(f2) ) )
			{
				puts("\nThe given grammer is not Operator Precedence Grammer");
				return 0;
			}
		}
	}

	puts("\nThe given grammer is Operator Precedence Grammer");
	return 0;
}
