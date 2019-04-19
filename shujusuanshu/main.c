#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 30
typedef struct numberstack//用于存放数字的栈结构
{
    double val[50];
    int top;
}* numstack;
void nummakenull(numstack s)//数字栈制空
{
    s->top=0;
}
int numempty(numstack s)//检验数字栈是否为空
{
    if(s->top<1)
        return 1;
    else
        return 0;
}
double numtop(numstack s)//输出数字栈栈顶元素
{
    if (numempty(s))
        return -1;
    else
        return (s->val[s->top]);
}
void numpop(numstack s)//删除数字栈栈顶元素
{
    if(numempty(s))
        s->top=0;
    else
        s->top=s->top-1;
}
void numpush(double x,numstack s)//数字入栈
{
    if(s->top==49)
        printf("栈满\n");
    else
        s->top=s->top+1;
        s->val[s->top]=x;
}
typedef struct df{//符号栈的结构
    char cval[max];
    int top;
}* charstack;

void charmakenull(charstack s)//符号栈制空
{
    s->top=0;
}
int charempty(charstack s)//检验符号栈是否为空
{
    if(s->top<1)
        return 1;
    else
        return 0;
}
char chartop(charstack s)//输出符号栈栈顶元素
{
    if (charempty(s))
        return 'f';//如果栈空返回f
    else
        return (s->cval[s->top]);
}
void charpop(charstack s)//删除符号栈栈顶元素
{
    if(charempty(s))
        s->top=0;
    else
        s->top=s->top-1;
}
void charpush(char x,charstack s)//符号入栈
{
    if(s->top==max-1)
        printf("栈满\n");
    else
        s->top=s->top+1;
        s->cval[s->top]=x;
}
int opjuge(char a)//判断运算符的优先级
{
    if ((a=='+')||(a=='-'))
        return 1;
    else if ((a=='*')||(a=='/'))
        return 2;
    else if (a=='(')
            return 0;
        return 4;
}
int main()
{
    while(1){
    charstack op=(charstack)malloc(sizeof(struct df));//用于存放运算符的栈
    charstack hou=(charstack)malloc(sizeof(struct df));//用于存放后缀表达式的栈
    charmakenull(op);
    charmakenull(hou);
    numstack shu=(numstack)malloc(sizeof(struct numberstack));//用于存放数字的栈
    nummakenull(shu);
    int i=0,j=1,k=0,l,flag=-1;
    double p,q,b=1;
    char str[50];//记录中缀表达式
    char suan[9];//用于多位数的实现求解
    printf("\n请输入中缀表达式（输入f结束运行，括号用英文括号）：\n");
    scanf("%s",str);
    if(str[0]=='f')
        break;
    printf("后缀表达式为\n");
    while(str[i]!='\0')//扫描中缀表达式并转换成后缀表达式输出。同时将输出的后缀表达式记录到符号栈hou中
    {
        if(i==0&&str[i]=='-') charpush(str[i],op);
        else if((str[i]>='0'&&str[i]<='9')||str[i]=='.')//如果是数字或者小数点直接输出
        {
            printf("%c",str[i]);
            charpush(str[i],hou);
        }
        else//将运算符压入栈或者弹出栈
        {
            printf(" ");
            charpush(' ',hou);
            if(charempty(op))
            {
                charpush(str[i],op);
            }
            else if (str[i]=='(')
            {
                charpush(str[i],op);
            }
            else if (str[i]==')')
            {
                while (chartop(op)!='('&&(!charempty(op)))
                {
                        printf("%c",chartop(op));
                        charpush(chartop(op),hou);
                    charpop(op);
                }
                charpop(op);
            }
            else if(opjuge(str[i])>opjuge(chartop(op)))
            {
                charpush(str[i],op);
            }
            else if(opjuge(str[i])<=opjuge(chartop(op)))
            {
                while (opjuge(str[i])<=opjuge(chartop(op))&&(!charempty(op)))
                {
                    printf("%c",chartop(op));
                    charpush(chartop(op),hou);
                    charpop(op);
                }
                charpush(str[i],op);
            }
        }
        i++;
    }
    if (!charempty(op))//弹出栈中未弹出的运算符
    {
        while(!charempty(op))
        {
            printf("%c",chartop(op));
            charpush(chartop(op),hou);
            charpop(op);
        }
    }
    if (str[0]=='-')
    {
        b=-1;
    }
    for(j=1;j<=(hou->top);j++)//扫描后缀表达式，并计算后缀表达式的运算结果
    {
        if((hou->cval[j]>='0'&&hou->cval[j]<='9')||hou->cval[j]=='.')
        {
            if(hou->cval[j]=='.')//用于记录小数点出现的位置
                flag=k;
            else
            {
               suan[k]=hou->cval[j];
               k++;//多加了一个1，所以后面是k-1
            }
        }
        else
        {
            double a=0;
            for(l=k-1;l>=0;l--)//计算多位数的值
            {
               a=a+(suan[l]-48)* pow(10,k-1-l);
            }
            if(k!=0&&a==0)
            {
                printf("数据不能为0\n");
                goto L1;
            }
            if(a!=0)
            {
               if(flag!=-1)
               a=a/pow(10,k-flag);//计算多位小数的值
               a=a*b;
               numpush(a,shu);
               a=0;
               flag=-1;
            }
            k=0;
        if(b==-1&&hou->cval[j]=='-')
        {
            getchar();
            b=1;
        }

        else//根据运算符进行运算
            switch(hou->cval[j]){
        case ' ':
            break;
        case '+':
            p=numtop(shu);
            numpop(shu);
            q=numtop(shu);
            numpop(shu);
            p=p+q;
            numpush(p,shu);
            break;
        case '-':
            p=numtop(shu);
            numpop(shu);
            q=numtop(shu);
            numpop(shu);
            p=q-p;
            numpush(p,shu);
            break;
        case '*':
            p=numtop(shu);
            numpop(shu);
            q=numtop(shu);
            numpop(shu);
            p=q*p;
            numpush(p,shu);
            break;
        case '/':
            p=numtop(shu);
            numpop(shu);
            q=numtop(shu);
            numpop(shu);
            p=q/p;
            numpush(p,shu);
            break;
        }
        }
    }
    printf("\n最终结果为：\n");
    if(str[0]=='-')
    printf("%lf",-numtop(shu));
    else
        printf("%lf",numtop(shu));
    numpop(shu);
    }
    L1:
    return 0;
}
