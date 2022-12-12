#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
int main()
{
	FILE *fpin,*fpout;
	char constVar,buff[100];
	int constVarVal;
	bool valueAssigned = false;
	fpin = fopen("input.txt","r");
	fpout = fopen("outputConstProp.txt","w");

	printf("Enter the constant variable: ");
	scanf("%c",&constVar);

	int num = 0;
	while(!feof(fpin))
	{
		fgets(buff,100,fpin);
		// To stop trailing extra brackets
		if(feof(fpin)) break;

		for(int i=0;buff[i] != '\0';)
		{
			if((buff[i] == constVar && i>0 && (buff[i-1] == ' ' || buff[i-1] == '\t' || buff[i-1] == '+' || buff[i-1] == '-' || buff[i-1] == '='))
					|| (i==0 && buff[i] == constVar && (buff[i+1] == ' ' || buff[i+1] == '='))) // Well intended OR poorly intended...
			{
				if(buff[i+1] == '=' && !valueAssigned)
				{
					++i;
					int start=-1,stop=-1;
					while(buff[++i] == ' ');
					if(isdigit(buff[i]))
					{
						start = i;
						while(isdigit(buff[++i]));
						stop = i-1;
					}

					if(start != -1)
					{
						num = (int)buff[start] - 0x30;
						for(int j=start+1;j<=stop;++j)
						{
							num *= 10;
							num += (int)buff[j] - 0x30;
						}
						
						constVarVal = num;
						valueAssigned = true;
						fprintf(fpout,buff);
						i = strlen(buff);
					}
					else
					{
						fclose(fpin);
						fclose(fpout);
						perror("\n Constant is reassigned another value...\n");
						return -1;
					}
				}	
				else if(buff[i+1] == ' ' || buff[i+1] == '+' || buff[i+1] == '-' || buff[i+1] == '*' || buff[i+1] == '/' || buff[i+1] == ';' || buff[i+1] == ')' || buff[i+1] == '%')
				{
					if(!valueAssigned)
					{
						fclose(fpin);
						fclose(fpout);
						perror("\n Value is used before assigned a value...\n");
						return -1;
					}
					else
					{
						//fputc(constVarVal,fpout);
						fprintf(fpout,"%d",constVarVal);
						//fputc(' ',fpout);
					}

					while(buff[++i]!='\0')
					{
						if(buff[i] == constVar)
							fputc(constVarVal,fpout);
						else
							fputc(buff[i],fpout);
					}
				}
				else
					fputc(buff[i++],fpout);
			}
			else
				fputc(buff[i++],fpout);

		}
	}

	fclose(fpin);
	fclose(fpout);

	printf("\n\nOriginal Program:\n");
	fpin = fopen("input.txt","r");
	fpout = fopen("outputConstProp.txt","r");

	while(!feof(fpin))
		printf("%c",fgetc(fpin));

	printf("\n\nProgram after Optimization:\n");
	while(!feof(fpout))
		printf("%c",fgetc(fpout));

	fclose(fpin);
	fclose(fpout);

	return 0;
}
