#include <iostream>
#include <string>
#include <cmath>
using namespace std;
struct stack
{
    char val;
    stack* next;
};
void MakeNull(stack* S)
{
    S=new stack;
    S->next=NULL;
}
void push(char x,stack* S)
{
    stack* stk;
    stk=new stack;
    stk->val=x;
    stk->next=S->next;
    S->next=stk;
}
void pop(stack* S)
{
    stack* stk;
    if (S->next)
    {
        stk=S->next;
        S->next=stk->next;
        delete stk;
    }
}
char top(stack* S)
{
    if (S->next)
        return (S->next->val);
    else
        return 0;
}
bool Empty(stack* S)
{
    if (S->next)
        return 0;
    else
        return 1;
}
int op(char x)
{
    if (x=='+'||x=='-') return 1;
    if (x=='*'||x=='/') return 2;
    if (x=='(') return 3;
    return -1;
}
struct num
{
    double val;
    num* next;
};
void pushnum(double x,num* number)
{
    num* stk;
    stk=new num;
    stk->val=x;
    stk->next=number->next;
    number->next=stk;
}
void popnum(num* number)
{
    num* stk;
    if (number->next)
    {
        stk=number->next;
        number->next=stk->next;
        delete stk;
    }
}
double topnum(num* number)
{
    if (number->next)
        return (number->next->val);
    else
        return 0;
}
int main()
{
    while (1)
    {
    cout<<"输入中缀表达式"<<endl;
    string s;
    cin>>s;
    if (s=="0") break;
    stack *S=new stack;
    S->next=NULL;
    string postfix="";
    cout<<"输出后缀表达式"<<endl;
    int len=s.length();
    for (int i=0;i<len;i++)
    {
        if ((s[i]>='0'&&s[i]<='9')||s[i]=='.')
        {
            postfix+=s[i];
            continue;
        }
        if (s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='('||s[i]==')'||s[i]=='#')
        {
            if (s[i]!='('&&s[i]!=')') postfix+=" ";
            if (s[i]==')')
            {
                while (top(S)!='(')
                {
                    postfix+=top(S);
                    pop(S);
                }
                pop(S);
                continue;
            }
            else
            {
                if (top(S)==0|| op(s[i]) > op(top(S)) ||top(S)=='(')
                {
                    push(s[i],S);
                    continue;
                }
                while ( top(S)!=0&&op(s[i]) <= op(top(S)) &&top(S)!='(')
                {
                    postfix+=top(S);
                    pop(S);
                }
                push(s[i],S);
            }
        }
    }
    while (S->next!=NULL)
    {
        postfix+=top(S);
        pop(S);
    }
    cout<<postfix<<endl;
    cout<<"输出计算的值"<<endl;
    num* number=new num;
    number->next=NULL;
    double temp=0;
    bool flag=1;
    double div=1;
    bool change=1;
    int len2=postfix.length();
    int j=0;
    if (postfix[0]=='-')
    {
        change=0;
        j=1;
        while (postfix[j]!=' ')
        {
            if (postfix[j]=='.') flag=0;
            else if (flag) temp=temp*10-(postfix[j]-'0');
            else if (!flag)
            {
                div*=10;
                temp-=(postfix[j]-'0')/div;
            }
            j++;
        }
    }
    for (int i=j;i<len2;i++)
    {
        if (postfix[i]>='0'&&postfix[i]<='9'&&flag)
        {
            change=0;
            temp=temp*10+postfix[i]-'0';
            continue;
        }
        else if (postfix[i]>='0'&&postfix[i]<='9'&&!flag)
        {
            div*=10;
            temp+=(postfix[i]-'0')/div;
            continue;
        }
        else if (postfix[i]=='.')
        {
            flag=0;
            continue;
        }
        else if (postfix[i]==' ')
        {
            if (change==0) pushnum(temp,number);
            change=1;
            temp=0;
            flag=1;
            div=1;
            continue;
        }
        else if (postfix[i]=='+'||postfix[i]=='-'||postfix[i]=='*'||postfix[i]=='/')
        {
            if (change==0) pushnum(temp,number);
            double x,y;
            change=1;
            temp=0;
            flag=1;
            div=1;
            switch (postfix[i])
            {
                case '+':
                    y=topnum(number);
                    popnum(number);
                    x=topnum(number);
                    popnum(number);
                    x=x+y;
                    pushnum(x,number);
                    break;
                case '-':
                    y=topnum(number);
                    popnum(number);
                    x=topnum(number);
                    popnum(number);
                    x=x-y;
                    pushnum(x,number);
                    break;
                case '*':
                    y=topnum(number);
                    popnum(number);
                    x=topnum(number);
                    popnum(number);
                    x=x*y;
                    pushnum(x,number);
                    break;
                case '/':
                    y=topnum(number);
                    popnum(number);
                    x=topnum(number);
                    popnum(number);
                    x=x/y;
                    pushnum(x,number);
                    break;
            }
            continue;
        }
    }
    cout<<topnum(number)<<endl<<endl;
    }
    return 0;
}
