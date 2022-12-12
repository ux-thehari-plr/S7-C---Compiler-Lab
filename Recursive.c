#include<stdio.h>
#include<stdbool.h>
//E –> T E’ 
//E’ –> + T E’ | e 
//T –> F T’ 
//T’ –> * F T’ | e 
//F –> ( E ) | i
int i=0;
bool flag=false,error=false;
char expr[10];
void E();
void Edash();
void T();
void Tdash();
void F();
int main()
{
	printf("Enter Expression:\n");
	scanf("%s",expr);

	E();
	if(flag)
	{
		if(error)
			printf("String Rejected\n");
		else if(expr[i] == '\0')
			printf("String Accepted\n");
		else
			printf("String Rejected\n");
	}

	return 0;
}

void E()
{
	T();
	Edash();
}
void Edash()
{
	if(expr[i] == '+')
	{
		++i;
		T();
		Edash();
	}
}
void T()
{
	F();
	Tdash();
}
void Tdash()
{
	if(expr[i] == '*')
	{
		++i;
		F();
		Tdash();
	}
}
void F()
{
	if(expr[i] == 'i') 
	{
		++i;
		flag = true;
		return;
	}
	else if(expr[i] == '(')
	{
		++i;
		E();
		if(expr[i] == ')')
		{
			++i;
			flag = true;
		}
		else
			flag = false;
	}
	else 
	{
		flag = false;
		error = true;
	}
}
