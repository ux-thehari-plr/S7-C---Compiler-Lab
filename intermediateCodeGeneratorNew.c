#include<stdio.h>
#include<ctype.h>

int main()
{
	char input[20],oprndStk[20],opratStk[20];
	int oprndStkTop=-1,opratStkTop=-1,i=0,n=0;

	printf("Enter a valid expression: ");
	fgets(input,20,stdin);

	FILE *fp;
	fp = fopen("Quadruple","w");
	
	while(input[i] != '\0')
	{
		if(isalpha(input[i]))
		{
			oprndStk[++oprndStkTop] = input[i++];
			continue;
		}
		else
		{
			if(opratStkTop == -1)
			{
				opratStk[++opratStkTop] = input[i++];
				continue;
			}

			if(input[i] == ')')
			{
				while(opratStk[opratStkTop] != '(')
				if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
				{
					fprintf(fp,"\nr%d r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = r%c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
				}
				else if(isdigit(oprndStk[oprndStkTop-1]))
				{
					fprintf(fp,"\nr%d r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = r%c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
				}
				else if(isdigit(oprndStk[oprndStkTop]))
				{
					fprintf(fp,"\nr%d %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = %c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
				}
				else
				{
					fprintf(fp,"\nr%d %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = %c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
				}

				--opratStkTop;
				++i;
			}
			else if(((input[i] == '*' || input[i] == '/' || input[i] == '%') && (opratStk[opratStkTop] == '*' || opratStk[opratStkTop] == '/' || opratStk[opratStkTop] == '%')) ||
				((input[i] == '+' || input[i] == '-' )  && (opratStk[opratStkTop] == '+' || opratStk[opratStkTop] == '-')))// Same priority
			{
				if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
				{
					fprintf(fp,"\nr%d r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = r%c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					opratStk[++opratStkTop] = input[i++];
				}
				else if(isdigit(oprndStk[oprndStkTop-1]))
				{
					fprintf(fp,"\nr%d r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = r%c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					opratStk[++opratStkTop] = input[i++];
				}
				else if(isdigit(oprndStk[oprndStkTop]))
				{
					fprintf(fp,"\nr%d %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = %c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					opratStk[++opratStkTop] = input[i++];
				}
				else
				{
					fprintf(fp,"\nr%d %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = %c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					opratStk[++opratStkTop] = input[i++];
				}

			}
			else if((input[i] == '*' || input[i] == '/' || input[i] == '%') && (opratStk[opratStkTop] == '+' || opratStk[opratStkTop] == '-' ))	// High priority comes to low priority
			{
				opratStk[++opratStkTop] = input[i++];
			}
			else if((input[i] == '+' || input[i] == '-') && (opratStk[opratStkTop] == '*' || opratStk[opratStkTop] == '/' ))	// low priority comes to High priority
			{
				if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
				{
					fprintf(fp,"\nr%d r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = r%c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					continue;
				}
				else if(isdigit(oprndStk[oprndStkTop-1]))
				{
					fprintf(fp,"\nr%d r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = r%c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					continue;
				}
				else if(isdigit(oprndStk[oprndStkTop]))
				{
					fprintf(fp,"\nr%d %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = %c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					continue;
				}
				else
				{
					fprintf(fp,"\nr%d %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
					printf("\nr%d = %c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					oprndStk[--oprndStkTop] = (char)(n+0x30);
					continue;
				}
			}
			else
				if(input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
					opratStk[++opratStkTop] = input[i++];
				else if(input[i] == '\n' && opratStkTop != -1)
					while(opratStkTop != -1)
					{
						// While dumping everything at the end, ignore parenthesis...
						if(opratStk[opratStkTop] == '(') 
						{
							++i;
							--opratStkTop;
							continue;
						}

						if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
						{
							fprintf(fp,"\nr%d r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
							printf("\nr%d = r%c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
							oprndStk[--oprndStkTop] = (char)(n+0x30);
						}
						else if(isdigit(oprndStk[oprndStkTop-1]))
						{
							fprintf(fp,"\nr%d r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
							printf("\nr%d = r%c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
							oprndStk[--oprndStkTop] = (char)(n+0x30);
						}
						else if(isdigit(oprndStk[oprndStkTop]))
						{
							if(opratStk[opratStkTop] == '=')
							{

								fprintf(fp,"\n%c r%c =",oprndStk[oprndStkTop-1],oprndStk[oprndStkTop]);
								printf("\n%c %c r%c",oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
								oprndStk[--oprndStkTop] = (char)(n+0x30);
							}
							else
							{
								fprintf(fp,"\nr%d %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
								printf("\nr%d = %c %c r%c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
								oprndStk[--oprndStkTop] = (char)(n+0x30);
							}
						}
						else
						{
							if(opratStk[opratStkTop] == '=')
							{

								fprintf(fp,"\n%c %c %c",oprndStk[oprndStkTop-1],oprndStk[oprndStkTop],opratStk[opratStkTop]);
								printf("\n%c %c %c",oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
								oprndStk[--oprndStkTop] = (char)(n+0x30);
							}
							else
							{
								fprintf(fp,"\nr%d %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop],oprndStk[oprndStkTop]);
								printf("\nr%d = %c %c %c",n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
								oprndStk[--oprndStkTop] = (char)(n+0x30);
							}
						}
					}
		}
	}

	fclose(fp);

	// Formatting as Quadruples...
	printf("\n\nQuadruples:\n");
	printf("\nResult\tOperand1\tOperator\tOperand2\n");
	printf("-------\t--------\t-------\t\t------\n");
	char res[4],opr1[4],opr2[4],oprat[2];
	fp = fopen("Quadruple","r");
	while(!feof(fp))
	{
		opr2[0] = '\0';	//if operand2 empty
		fscanf(fp,"%s%s%s%s",res,opr1,oprat,opr2);
		printf("%s\t\t%s\t\t%s\t\t%s\n",res,opr1,oprat,opr2);
	}

	printf("\n");
	return 0;
}
