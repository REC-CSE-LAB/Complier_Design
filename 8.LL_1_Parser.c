#include <stdio.h>
#include <string.h>

int i, k, n, top = -1, r, c, m, flag = 0;
char str[25], st[25], *temp, v, ch, ch1;
char t[5][6][10] = { "$", "$", "TX", "TX", "$", "$",
		     "+TX", "$", "$", "$", "e", "e",
		     "$", "$", "FY", "FY", "$", "$",
		     "e", "*FY", "$", "$", "e", "$",
		     "$", "$", "i", "(E)", "$", "$" };

void push ( char t )
{
	top++;
	st[top] = t;
	return ;
}

char pop ( void )
{
	ch1 = st[top];
	top--;
	return ch1;
}

int main()
{
	printf("Enter the string : ");
	scanf("%s",str);
	n=strlen(str);
	str[n++] = '$';
	i = 0;
	push('$');
	push('E');
	puts("Stack\t\t\tInput\t\t\tOperation");
	while( i < n )
	{
		for( k = 0; k <= top; k++ )
			printf("%c",st[k]);
		printf("\t\t\t");
		for( k = i; k < n; k++ )
			printf("%c",str[k]);
		printf("\t\t\t");
		if( flag == 1 )
			printf("pop");
		else if ( flag == 2 )
			printf("%c - > %s",ch,t[r][c]);
		if( str[i] == st[top] )
		{
			flag = 1;
			ch = pop();
			++i;
		}
		else
		{
			flag = 2;
			if( st[top] == 'E' )
				r = 0;
			else if( st[top] == 'X' )
				r = 1;
			else if( st[top] == 'T' )
				r = 2;
			else if( st[top] == 'Y' )
				r = 3;
			else if( st[top] == 'F' )
				r = 4;
			else
				break;

			if( str[i] == '+' )
				c = 0;
			else if( str[i] == '*' )
				c = 1;
			else if( str[i] == 'i' )
				c = 2;
			else if( str[i] == '(' )
				c = 3;
			else if( str[i] == ')' )
				c = 4;
			else if( str[i] == '$' )
				c = 5;
			else
				break;
			
			if( strcmp( t[r][c], "$" ) == 0 )
				break;
			ch = pop();
			temp = t[r][c];
			m = strlen(temp);

			if( strcmp( t[r][c], "e" ) != 0 )
			{
				for( k = m-1; k >= 0; k-- )
					push(temp[k]);
			}
		}
		printf("\n");
	}	
	if( i == n-1 )
		puts("\nParser Accepted");
	else
		puts("\nPaser Rejected");		
	return 0;
}
