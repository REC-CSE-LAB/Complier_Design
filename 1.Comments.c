#include <stdio.h>
#include <string.h>

int main()
{
	char str[50];
	printf("enter the comment : ");
	gets(str);
	if( str[0] == '/' )
	{
		if( str[1] == '/' )
			puts("\nit is a comment");
		else if ( str[1] == '*' )
		{
			int i,flag;
			for	( i = 2, flag = 1; i < strlen(str)-1; ++i )
			{
				if( str[i] == '*' && str[i+1] == '/' )
				{
					puts("\nit is a comment");
					flag = 0;
					break;
				}
			}
			if(flag)
				puts("\nit is not a comment");
		}
	}
	else
		puts("\nit is not a comment");
	return 0;
}
