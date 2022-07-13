#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// default keywords, symbols and operators of 'c'.
const char keywords [32][10] = { "int", "char", "short", "float", "auto", "double", "struct", "break", "if", "else",
				 "long", "switch", "case", "enum", "register", "typedef","extern", "return", "union",
				 "const", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof",
				 "volatile", "do", "static", "while" };

int main()
{

	// Declaring variables
	FILE *ptr;
	char ch, buffer[30] = "\0";
	int lines_count = 0;

	// Function prototyping
	int is_keyword ( const char buffer [] );
	int is_identifier ( const char buffer [] );
	int is_operator ( const char ch );
	int is_special_symbol ( const char ch );

	// Assigning file address to file pointer
	ptr = fopen ("code.c", "w");

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
			else
				printf("%-10s is an unknown token.\n",buffer);
			ungetc(ch,ptr);
		}
		
		// check only for numericals ( like intergers, floating point numbers ) 
		else if ( isdigit(ch) )
		{
			buffer[i++] = ch;
			while( (ch = getc(ptr) ) != EOF )
			{
				if( isdigit(ch) )
					buffer[i++] = ch;
				else
					break;
			}
			printf("%-10d is an numerical.\n", atoi(buffer));
			ungetc(ch,ptr);
		}

		// check for comments
		else if ( ch == '/' )
		{
			// storing in buffer and reading the next element in the file
			buffer[i++] = ch;
			ch = getc(ptr);
			if( ch == '/' )
			{
				while( (ch = getc(ptr)) != EOF || (ch = getc(ptr)) != '\n' )
					continue;
				if( ch == '\n' )
					lines_count++;
			}
			else if ( ch == '*' )
			{
				while( (ch = getc(ptr)) != EOF || ( (ch = getc(ptr)) != '/' && buffer[strlen(buffer)-1] != '*' ) )
				{
					if( ch == '\n' )
						lines_count++;
				}
			}
			else 
			{
				printf("%-10c is an operator.\n",buffer[0]);
				ungetc(ch,ptr);
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
	if ( ch == '+' || ch == '-' || ch ==  '*' || ch == '/' || ch == '%' || ch == '!' || ch == '&' || ch == '<' || ch == '>' || ch == '=' || ch == '|' )
		return 1;
	return 0;
}

int is_special_symbol ( const char ch )
{
	if ( ch == ',' || ch == '.' || ch ==  '(' || ch == ')' || ch == ';' || ch == '$' || ch == ':' || ch == '#' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '~' || ch == '-' || ch == '?' )
		return 1;
	return 0;
}
