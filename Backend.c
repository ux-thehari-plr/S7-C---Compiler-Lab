#include&lt;stdio.h&gt;
#include&lt;conio.h&gt;
#include&lt;string.h&gt;
#include&lt;ctype.h&gt;
#include&lt;graphics.h&gt;
typedef struct
{ char var[10];
int alive;
}
regist;
regist preg[10];
void substring(char exp[],int st,int end)
{ int i,j=0;
char dup[10]=&quot;&quot;;
for(i=st;i&lt;end;i++)
dup[j++]=exp[i];
dup[j]=&#39;0&#39;;
strcpy(exp,dup);
} int getregister(char var[])
{ int i;
for(i=0;i&lt;10;i++)
{
if(preg[i].alive==0)
{s

trcpy(preg[i].var,var);
break;
}}
return(i);
}
void getvar(char exp[],char v[])
{ int i,j=0;
char var[10]=&quot;&quot;;
for(i=0;exp[i]!=&#39;\0&#39;;i++)
if(isalpha(exp[i]))
var[j++]=exp[i];
else
break;
strcpy(v,var);
}
void main()
{ char basic[10][10],var[10][10],fstr[10],op;
int i,j,k,reg,vc,flag=0;
clrscr();
printf(&quot;\nEnter the Three Address Code:\n&quot;);
for(i=0;;i++)
{
gets(basic[i]);
if(strcmp(basic[i],&quot;exit&quot;)==0)
break;
}
printf(&quot;\nThe Equivalent Assembly Code is:\n&quot;);
for(j=0;j&lt;i;j++)
{
getvar(basic[j],var[vc++]);
strcpy(fstr,var[vc-1]);
substring(basic[j],strlen(var[vc-1])+1,strlen(basic[j]));
getvar(basic[j],var[vc++]);
reg=getregister(var[vc-1]);
if(preg[reg].alive==0)
{
printf(&quot;\nMov R%d,%s&quot;,reg,var[vc-1]);
preg[reg].alive=1;
}
op=basic[j][strlen(var[vc-1])];

substring(basic[j],strlen(var[vc-1])+1,strlen(basic[j]));
getvar(basic[j],var[vc++]);
switch(op)
{ case &#39;+&#39;: printf(&quot;\nAdd&quot;); break;
case &#39;-&#39;: printf(&quot;\nSub&quot;); break;
case &#39;*&#39;: printf(&quot;\nMul&quot;); break;
case &#39;/&#39;: printf(&quot;\nDiv&quot;); break;
}
flag=1;
for(k=0;k&lt;=reg;k++)
{ if(strcmp(preg[k].var,var[vc-1])==0)
{
printf(&quot;R%d, R%d&quot;,k,reg);
preg[k].alive=0;
flag=0;
break;
}} if(flag)
{
printf(&quot; %s,R%d&quot;,var[vc-1],reg);
printf(&quot;\nMov %s,R%d&quot;,fstr,reg);
}s
trcpy(preg[reg].var,var[vc-3]);
getch();
}}