#include<stdio.h>
#include<ctype.h>

int main()
{
	char input[20],oprndStk[20],opratStk[20];
	int oprndStkTop=-1,opratStkTop=-1,i=0,n=0;

	printf("Enter a valid expression: ");
	fgets(input,20,stdin);
	
	while(input[i] != '\0')
	{
		if(isalpha(input[i]))
		{
			oprndStk[++oprndStkTop] = input[i++];
			continue;
		}
		else if
		{
			if(opratStkTop == -1)
			{
				opratStk[++opratStkTop] = input[i++];
				continue;
			}

			if(input[i] == ')')
			{
				while(opratStk[opratStkTop] != '(') {
					if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
					{
						printf("\nr%d = r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					}
					else if(isdigit(oprndStk[oprndStkTop-1]))
					{
						printf("\nr%d = r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					}
					else if(isdigit(oprndStk[oprndStkTop]))
					{
						printf("\nr%d = %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					}
					else
					{
						printf("\nr%d = %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
					}
					oprndStk[--oprndStkTop] = (char)(n+0x30);
				}

				++i;
			}
			else if(((input[i] == '*' || input[i] == '/' || input[i] == '%') && (opratStk[opratStkTop] == '*' || opratStk[opratStkTop] == '/' || opratStk[opratStkTop] == '%')) ||
				((input[i] == '+' || input[i] == '-' )  && (opratStk[opratStkTop] == '+' || opratStk[opratStkTop] == '-')))// Same priority
			{
				if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
				{
					printf("\nr%d = r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				else if(isdigit(oprndStk[oprndStkTop-1]))
				{
					printf("\nr%d = r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				else if(isdigit(oprndStk[oprndStkTop]))
				{
					printf("\nr%d = %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				else
				{
					printf("\nr%d = %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				oprndStk[--oprndStkTop] = (char)(n+0x30);
				opratStk[++opratStkTop] = input[i++];

			}
			else if((input[i] == '*' || input[i] == '/' || input[i] == '%') && (opratStk[opratStkTop] == '+' || opratStk[opratStkTop] == '-' ))	// High priority comes to low priority
			{
				opratStk[++opratStkTop] = input[i++];
			}
			else if((input[i] == '+' || input[i] == '-') && (opratStk[opratStkTop] == '*' || opratStk[opratStkTop] == '/' ))	// low priority comes to High priority
			{
				if(isdigit(oprndStk[oprndStkTop-1]) && isdigit(oprndStk[oprndStkTop]))
				{
					printf("\nr%d = r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				else if(isdigit(oprndStk[oprndStkTop-1]))
				{
					printf("\nr%d = r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				else if(isdigit(oprndStk[oprndStkTop]))
				{
					printf("\nr%d = %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				else
				{
					printf("\nr%d = %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
				}
				oprndStk[--oprndStkTop] = (char)(n+0x30);
				continue;
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
							printf("\nr%d = r%c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
							oprndStk[--oprndStkTop] = (char)(n+0x30);
						}
						else if(isdigit(oprndStk[oprndStkTop-1]))
						{
							printf("\nr%d = r%c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
							oprndStk[--oprndStkTop] = (char)(n+0x30);
						}
						else if(isdigit(oprndStk[oprndStkTop]))
						{
							printf("\nr%d = %c %c r%c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
							oprndStk[--oprndStkTop] = (char)(n+0x30);
						}
						else
						{
							printf("\nr%d = %c %c %c",++n,oprndStk[oprndStkTop-1],opratStk[opratStkTop--],oprndStk[oprndStkTop]);
							oprndStk[--oprndStkTop] = (char)(n+0x30);
						}
					}
		}
	}

	printf("\n");
	return 0;
}
