#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Declarations
	int i = 0, state = 0 ;
	char ch, str[30];
	
	// Reading input
	printf("Enter a string :  ");
	gets(str);
	
	// String Recogization logic
	while ( str[i] != '\0' )
	{
		switch ( state )
		{
			// State 0
			case 0: ch = str[i++];
					if( ch == 'a' )
						state = 1;
					else
						state = 4;	
					break;
			
			// State 1		
			case 1: ch = str[i++];
					if( ch == 'a' )
						state = 1;
					else if ( ch == 'b' )
						state = 2;
					else
						state = 4;
					break;
			
			// State 2		
			case 2: ch = str[i++];
					if( ch == 'b' )
						state = 3;
					else
						state = 4;
					break;
			
			// State 3
			case 3: ch = str[i++];
					if( ch != '\0' )
						state = 4;
					break;
			
			// State 4		
			case 4: printf("%s is not recognised.",str);
					exit(0);
		}
	}
	
	// Output
	if( state == 1 )
		printf("%s is accepted under rule \'a\'",str);
	else if ( state == 3 )
		printf("%s is accepted under rule \'abb\'",str);
	else
		printf("%s is not recognised.",str);
		
	return 0;
}
