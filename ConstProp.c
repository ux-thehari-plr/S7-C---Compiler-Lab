#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

void main() {
    FILE *fp;
	char ch, var;
    int varval;
    bool varfound = false;

    fopen("constp.txt","r");

    printf("Enter constant variable: ", &var);
    scanf("%d", &var);


    while (!feof(fp)) {

		ch = getc(fp);

        if(ch == var && getc(fp) == '=') {
            ch = getc(fp);
            
            if(isdigit(ch))
		    {
                varval = ch - '0';
                ch = getc(fp);
                while(isdigit(ch))
                {
                    varval = varval*10;
                    varval += ch - '0';
                    ch = getc(fp);
                }
                digitLit[noDig++] = varval;
            }
        }
        
}