#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
char temp[2], temp2[2];
char act[15];

int check( void );

int main()
{
	puts("\n\t\t SHIFT REDUCE PARSE\n");
	puts("\nGRAMMAR");
	puts("\nE -> E+E \nE -> E/E \nE -> E*E \nE -> a|b");

	printf("\nEnter the input symbol: \t");
	gets(ip_sym);

	puts("\n\t Stack - Implementation table");
	puts("\nStack\t\tInput Symbol\t\tAction");
	puts("_____\t\t____________\t\t______\n");
	
	printf("\n$\t\t%s$\t\t\t---",ip_sym);
	strcpy(act,"Shift ");

	temp[0] = ip_sym[ip_str];
	temp[1] = '\0';
	strcat( act, temp );
	len = strlen(ip_sym);

	for( i = 0; i <= len-1; ++i )
	{
		stack[st_ptr] = ip_sym[ip_ptr];
		stack[st_ptr] = '\0';
		ip_sym[ip_ptr] = ' ';
		ip_ptr++;

		printf("\n$%s\t\t%s$\t\t\t%s",stack,ip_sym,act);
		strcpy( act, "Shift ");
		temp[0] = ip_sym[ip_str];
		temp[1] = '\0';

		strcat( act, temp );
		check();
		str_ptr++;
	}
	check();
	return 0;
}

int check( void )
{
	int flag = 0;
	temp2[0] = stack[str_ptr];
	temp2[0] = '\0';
	
	if( (isalpha(temp2[0]) )
