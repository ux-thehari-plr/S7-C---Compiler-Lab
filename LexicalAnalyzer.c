#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void main(){

	FILE *fp;
	char ch;
	char BUFF[100], keyword[20][100], identi[20][100], literals[20][100], operators[100], spclsymbol[100];
	int digitLit[100];
	int i = 0, noKey = 0, noIdenti = 0, noDig = 0, noLit = 0, noOperat = 0, noSpclsym = 0, linenum = 0, num;

	fp = fopen("input.txt","r");

	while (!feof(fp)) {
		
		ch = getc(fp);

		if(ch == '#')
		{
			while(getc(fp) != '\n');
			linenum++;
		}
		else if(isalpha(ch))
		{
			i = 0;
			while(isalpha(ch))
			{
				BUFF[i++] = ch;
				ch = getc(fp);
			}
			BUFF[i] = '\0';

			if( strcmp(BUFF,"if") == 0||
					strcmp(BUFF,"else") == 0||
					strcmp(BUFF,"for") == 0||
					strcmp(BUFF,"while") == 0||
					strcmp(BUFF,"int") == 0||
					strcmp(BUFF,"char") == 0||
					strcmp(BUFF,"void") == 0||
					strcmp(BUFF,"float") == 0||
					strcmp(BUFF,"double") == 0||
					strcmp(BUFF,"return") == 0
			  )
				strcpy(keyword[noKey++],BUFF);
			else
				strcpy(identi[noIdenti++],BUFF);

			fseek(fp,-1*(sizeof(char)),SEEK_CUR);
		}

		else if(isdigit(ch))
		{
			num = ch - '0';
			ch = getc(fp);
			while(isdigit(ch))
			{
				num = num*10;
				num += ch - '0';
				ch = getc(fp);
			}

			digitLit[noDig++] = num;
			fseek(fp,-1*(sizeof(char)),SEEK_CUR);
		}
		
		else if(ch == '"')
		{
			i=0;
			ch = getc(fp);
			while(1)
			{
				if(ch == '"')
					break;
				BUFF[i++] = ch;
				ch = getc(fp);
			}
			BUFF[i] = '\0';

			strcpy(literals[noLit++],BUFF);
		}

		else {
			switch(ch) {
				case '\n' :
					++linenum;
				case '\t' :
				case ' ' :
				case '\r' :
					break;
				case '+' :
				case '-' :
				case '*' :
				case '/' :
				case '%' :
				case '=' :
					operators[noOperat++] = ch;
					break;
				default :
					spclsymbol[noSpclsym++] = ch;
			}
		}
	}
	fclose(fp);

	printf("\nNumber of lines: %d\n", linenum + 1);
	printf("Keywords:\n");
	for(int i=0;i<noKey;++i)
		printf("%s\n",keyword[i]);
	printf("\nIdentifiers:\n");
	for(int i=0;i<noIdenti;++i)
		printf("%s\n",identi[i]);
	printf("\nString Literals:\n");
	for(int i=0;i<noLit;++i)
		printf("%s\n",literals[i]);
	printf("\nInteger Literals:\n");
	for(int i=0;i<noDig;++i)
		printf("%d\n",digitLit[i]);
	printf("\nOperators:\n");
	for(int i=0;i<noOperat;++i)
		printf("%c\n",operators[i]);
	printf("\nSpecial Symbols:\n");
	for(int i=0;i<noSpclsym - 1;++i)
		printf("%c\n",spclsymbol[i]);
	printf("\n");
}

