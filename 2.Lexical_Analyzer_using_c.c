#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// default keywords, symbols and operators of 'c'.
const char keywords [32][10] = { "int", "char", "short", "float", "auto", "double", "struct", "break", "if", "else",
				 "long", "switch", "case", "enum", "register", "typedef","extern", "return", "union",
				 "const", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof",
				 "volatile", "do", "static", "while" };
<<<<<<< HEAD
// const char symbols [20] = { ',', '<', '>', '.',  '(', ')', ';', '$', ':', '#', '[', ']', '\'', '\"', '{', '}', '~', '-', '?'};
// const char operators [12] = { '+', '-', '*', '/', '%', '!', '&', '<', '>', '=', '|' };
=======
//const char symbols [20] = { ',', '<', '>', '.',  '(', ')', ';', '$', ':', '#', '[', ']', '\'', '\"', '{', '}', '~', '-', '?'};
//const char operators [12] = { '+', '-', '*', '/', '%', '!', '&', '<', '>', '=', '|' };
>>>>>>> 89073e95648538e1581651a813a33c860963c957

int main()
{

	// Declaring variables
	FILE *ptr;
	char ch, buffer[30] = "\0";
	int flag_dot_count = 1, lines_count = 0;

	// Function prototyping
	int is_keyword ( const char buffer [] );
	int is_identifier ( const char buffer [] );
	int is_operator ( const char ch );
	int is_special_symbol ( const char ch );

	// Assigning file address to file pointer
	ptr = fopen ("code.c", "w");

	// Checking for any possible errors due to file operation
	if( ptr == NULL )
	{
		puts("Error occured while creating ( or ) opeaning the file...");
		puts("Press enter to continue...");
		fflush(stdin);
		getchar();
		exit(0);
	}

	// displaying prompt before writing into the file
	system("cls");
	fflush(stdin);
	puts("Enter the code : \n");

	// writing data into file
	while( (ch = getchar()) != EOF )
		putc(ch,ptr);
	
	// reassigning file pointer as read mode
	fclose(ptr);
	ptr = fopen("code.c", "r");

	// Checking for any possible errors due to file operation
	if( ptr == NULL )
	{
		puts("\nError occured while reading the file...");
		puts("Press enter to continue...");
		fflush(stdin);
		getchar();
		exit(0);
	}

	// Prompt before displaying the tokens.
	puts("\n--------------------------------------------");
	puts("\t\tTokens");
	puts("\n--------------------------------------------\n");

	// token generator logic 
	for ( int i = 0; (ch = getc(ptr)) != EOF;  i = 0, buffer[0] = '\0' )
	{
		// check only for identifiers and keywords
		if(isalpha(ch) || ch == '_')
		{
			buffer[i++] = ch;
			while( (ch = getc(ptr)) != EOF )
			{
				if( isalnum(ch) || ch == '_' )
					buffer[i++] = ch;
				else
					break;
			}
			buffer[i] = '\0';
			if( is_keyword ( buffer ) )
				printf("%-10s is an keyword.\n",buffer);
			else if( is_identifier( buffer ) )
				printf("%-10s is an identifier.\n",buffer);
			ungetc(ch,ptr);
		}
		
		// check only for numericals ( like intergers, floating point numbers ) 
		else if ( isdigit(ch) )
		{
			buffer[i++] = ch;
			while( (ch = getc(ptr) ) != EOF )
			{
				if( isdigit(ch) || ( ch == '.' && flag_dot_count ) )
				{
					if( ch == '.' )
						flag_dot_count = 0;
					buffer[i++] = ch;
				}
				else
					break;
			}
			if( flag_dot_count )
				printf("%-10d is an numerical.\n", atoi(buffer));
			else
				printf("%-10lf is an numerical.\n", atof(buffer));
			ungetc(ch,ptr);
		}
		
		// check only for string or character literal
		else if( ch == '\'' || ch == '\"' )
		{
			// checking for string literal
			if( ch == '\"' )
			{
				int pervious_index = -1, esq_flag = 0, end_flag = 1;
				buffer[i++] = ch;
				while( (ch = getc(ptr)) != EOF )
				{
					buffer[i++] = ch;

					// checking for escape sequences in sting literal
					if ( esq_flag && i == pervious_index )
					{
						if ( ch == '\\' 		// Backslash 
							 || ch == 'a'	 	// Alarm or Beep
							 || ch == 'b'	 	// Backspace
							 || ch == 'f'		// Form Feed
							 || ch == 'n'		// New Line
							 || ch == 'r'		// Carriage Return
							 || ch == 't'		// Tab (Horizontal)
							 || ch == 'v'		// Vertical Tab
							 || ch == '\''		// Single Quote
							 || ch == '\"'		// Double Quote
							 || ch == '0' )		// Null
						{
							esq_flag = 0;
						}
					}
						
					// checking for presence of escape sequences
					if( ch == '\\' )
					{
						esq_flag = 1;
						pervious_index = i+1;
					}
					
					// checking for the proper end of string literal
					if( ch == '\"' && buffer[i-2] != '\\' )
					{
						end_flag = 0;
						break;
					}
				}
				
				// if ch == EOF then we must replace the last index with '\0' to avoid the new line in output
				if( end_flag )
					buffer[i-1] = '\0';
				else
					buffer[i] = '\0';
					
				// printing status of the token
				if(esq_flag || end_flag)
					printf("%-10s is an invalid string literal",buffer);
				else
					printf("%-10s is an string literal.\n",buffer);
			}
			
			// checking for character literal 
			else
			{
				buffer[i++] = ch;
				while( (ch = getc(ptr)) != EOF )
				{
					buffer[i++] = ch;
					if( ch == '\'' )
						break;
				}
				buffer[i] = '\0';
				if( strlen(buffer) == 3 || 
					( strlen(buffer) == 4 && buffer[1] == '\\' 
						&& ( buffer[2] == '\\'			// Backslash 
							 || buffer[2] == 'a'		// Alarm or Beep
							 || buffer[2] == 'b'	 	// Backspace
							 || buffer[2] == 'f'		// Form Feed
							 || buffer[2] == 'n'		// New Line
							 || buffer[2] == 'r'		// Carriage Return
							 || buffer[2] == 't'		// Tab (Horizontal)
							 || buffer[2] == 'v'		// Vertical Tab
							 || buffer[2] == '\''		// Single Quote
							 || buffer[2] == '\"'		// Double Quote
							 || buffer[2] == '0' ) ) )
					printf("%-10s is an charcter literal.\n",buffer);
				else
					printf("%-10s is an invalid charcter literal.\n",buffer);
			}
		}
		
		// check for comments
		else if ( ch == '/' )
		{
			// storing in buffer and reading the next element in the file
			buffer[i++] = ch;
			ch = getc(ptr);
			
			
			
			// making sure that it's a comment
			if( ch != '/' && ch != '*' )
			{ 
				printf("%-10c is an operator.\n",buffer[0]);
				ungetc(ch,ptr);
			}
				
			// for single-line comment
			else if ( ch == '/' )
			{
				while( (ch = getc(ptr)) != EOF )
				{
					if( ch == '\n' )
					{
						lines_count++;
						break;
					}
				}
			}
			
			// for multi-line comment
			else if ( ch == '*' )
			{
				buffer[i++] = ch;
				while( (ch = getc(ptr)) != EOF )
				{
					buffer[i++] = ch;
					if ( ch == '\n' )
						lines_count++;
					else if ( ch == '/' && buffer[i-1] == '*' && i-1 > 1 )
						break;
				}
				buffer[i-1] = '\0';
				
				// checking for possible invalid comments
				if( ch == EOF )
					printf("%-10s is an invalid multi-line comment\n",buffer);
			}
		}
		
		// check only for special symbols and operator
		else if( ch != ' ' && ch != '\n' && ch != '\t'  )
		{
			if( is_operator(ch) )
				printf("%-10c is an operator.\n", ch);
			else if ( is_special_symbol(ch) )
				printf("%-10c is a special symbol.\n", ch );
		}
		
		// check for the delimitors
		else
		{						
			// counting the number of lines
			if( ch == '\n' )
				lines_count++;

			continue;
		}
				
	}
	printf("\nNumber of lines : %d", lines_count);
	fclose(ptr);
	return 0;
}

int is_keyword ( const char buffer [] )
{
	for( int i = 0; i < 32; ++i )
		if( strcmp( buffer, keywords[i] ) == 0 )
			return 1;
	return 0;
}

int is_identifier ( const char buffer [] )
{
	if( buffer[0] == '_' || isalpha(buffer[0]) )
	{
		if( strlen(buffer) == 1 )
			return 1;
		int i,flag = 1;
		for( i = 1; i < strlen(buffer); ++i )
			flag = ( isalnum(buffer[i]) ) ? 0 : 1;
		return (flag) ? 0 : 1;
	}
	return 0;
}

int is_operator ( const char ch )
{
	if ( ch == '+' 
		 || ch == '-' 
		 || ch ==  '*' 
		 || ch == '/' 
		 || ch == '%' 
		 || ch == '!' 
		 || ch == '&' 
		 || ch == '<' 
		 || ch == '>' 
		 || ch == '=' 
		 || ch == '|' )
		return 1;
	return 0;
}

int is_special_symbol ( const char ch )
{
	if ( ch == ',' 
		 || ch == '.' 
		 || ch ==  '(' 
		 || ch == ')' 
		 || ch == ';' 
		 || ch == '$' 
		 || ch == ':' 
		 || ch == '#' 
		 || ch == '[' 
		 || ch == ']' 
		 || ch == '{' 
		 || ch == '}' 
		 || ch == '~' 
		 || ch == '-' 
		 || ch == '?' )
		return 1;
	return 0;
}
