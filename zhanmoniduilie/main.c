#include <stdio.h>
#include <stdlib.h>
typedef struct asd//栈的结构
{
    int val[50];
    int top;
}* Stack;
void smakenull(Stack s)//将栈制空
{
   s->top=0;
}
int sempty(Stack s)//检验栈是否为空
{
    if (s->top<1)
        return 1;
    else
        return 0;
}
int stop(Stack s)//输出栈顶数据
{
    if (sempty(s))
        return -1;
    else
        return s->val[s->top];
}
void spop(Stack s)//删除栈顶数据
{
    if (sempty(s))
        printf("栈空无法再删除\n");
    else
        s->top=s->top-1;
}
void spush(int x,Stack s)//数据入栈
{
    if (s->top==49)
        printf("栈满无法再入栈\n");
    else
    {
        s->top=s->top+1;
        s->val[s->top]=x;
    }
}
void makenull(Stack a,Stack b)//队列制空
{
    smakenull(a);
    smakenull(b);
}
int empty(Stack a,Stack b)//队列制空
{
    if (sempty(a)&&sempty(b))
        return 1;
    else
        return 0;
}
void enqueue(int x,Stack a)//数据入队
{
    spush(x,a);
}
void dequeue(Stack a,Stack b)//删除队列第一元素
{
    if(sempty(b))
    {
        while(!sempty(a))
        {
            spush(stop(a),b);
            spop(a);
        }
    }
    spop(b);
}
int Front(Stack a,Stack b)//输出队列第一个元素
{
   if(sempty(b))
    {
        while(!sempty(a))
        {
            spush(stop(a),b);
            spop(a);
        }
    }
    return b->val[b->top];
}
int main()
{
        int swi;
        Stack a=(Stack)malloc(sizeof(struct asd));//此两个结构是用于实现队列功能建立的两个栈
        Stack b=(Stack)malloc(sizeof(struct asd));
        while(1)
    {
        printf("请输入您的选择：\n1、制空队列\n2、向队列输入数据\n3、输出队列数据\n4、删除队列第一个数据\n5、检验队列是否为空\n");
        scanf("%d",&swi);
        switch(swi)
        {
        case 1:
            makenull(a,b);
            break;
        case 2:
            printf("请输入您的数据：\n");
            int x;
            scanf("%d",&x);
            enqueue(x,a);
            break;
        case 3:
            if(empty(a,b))
                printf("栈为空。\n");
            else{
            printf("队列的第一个元素为：\n");
            printf("%d\n",Front(a,b));}
            break;
        case 4:
            dequeue(a,b);
            break;
        case 5:
            if(empty(a,b))
                printf("队列为空。\n");
            else
                printf("队列非空。\n");
                break;
        }
    }
    return 0;
}
