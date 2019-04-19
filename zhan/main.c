#include <stdio.h>
#include <stdlib.h>
typedef struct celltype//建立队列用到的两个机构体
{
    int cal;
    struct celltype * next;
}* line;
typedef struct queue
{
    line front;
    line rear;
}* que;
void lmakenull(que q)//队列制空
{
    q->front=(line)malloc(sizeof(struct celltype));
    q->front->next=NULL;
    q->rear=q->front;
}
int lempty(que q)//检验队列是否为空
{
    if(q->front==q->rear)
        return 1;
    else
        return 0;
}
void enqueue(int x,que a)//数据进队
{
    a->rear->next=(line)malloc(sizeof(struct celltype));
    a->rear=a->rear->next;
    a->rear->cal=x;
    a->rear->next=NULL;
}
void dequeue(que q)//删除队首元素
{
    line tmp;
    if (lempty(q))
        printf("栈为空。\n");
    else
    {
        tmp=q->front->next;
        q->front->next=tmp->next;
        //free(tmp);
        if (q->front->next==NULL)
            q->rear=q->front;
    }
}
int lfront(que q)//输出队首元素
{
    if (lempty(q))
        return -1;
    else
        return q->front->next->cal;
}
void makenull(que a,que b)//栈制空
{
    lmakenull(a);
    lmakenull(b);
}
void push(int x,que a)//数据入栈
{
    enqueue(x,a);
}
int empty(que a,que b)//检验栈是否为空
{
    if(lempty(a)&&lempty(b))
        return 1;
    else
        return 0;
}
int top(que a,que b)//输出栈顶数据
{
    if(b->front!=b->rear)
        return b->front->next->cal;
    else
    {
        while (!lempty(a))
        {
            enqueue(a->front->next->cal,b);
            dequeue(a);
        }
        while (b->front->next->next!=NULL)
        {
            enqueue(b->front->next->cal,a);
            dequeue(b);
        }
        return b->front->next->cal;
    }
}
void pop(que a,que b)//删除栈顶数据
{
    if(b->front!=b->rear)
        dequeue(b);
    else
    {
        while (!lempty(a))
        {
            enqueue(a->front->next->cal,b);
            dequeue(a);
        }
        while (b->front->next->next!=NULL)
        {
            enqueue(b->front->next->cal,a);
            dequeue(b);
        }
        dequeue(b);
    }
}
int main()
{
    que a=(que)malloc(sizeof(struct queue));//用队列模拟栈要用到的两个队列的结构体
    que b=(que)malloc(sizeof(struct queue));
    int swi,x;
    while(1)
    {
      printf("请输入您的选择：\n1、制空栈\n2、数据入栈\n3、输出栈顶数据\n4、删除栈顶数据\n5、检验栈是否为空\n");
      scanf("%d",&swi);
      switch(swi)
      {
      case 1:
        makenull(a,b);
        break;
      case 2:
        printf("请输入您的数据：\n");
        scanf("%d",&x);
        push(x,a);
        break;
      case 3:
        printf("栈顶数据为：\n");
        if(!empty(a,b))
        printf("%d\n",top(a,b));
        else
        printf("栈为空\n");
        break;
      case 4:
        pop(a,b);
        break;
      case 5:
        if(empty(a,b))
            printf("栈为空。\n");
        else
            printf("栈非空。\n");
      }
    }
    return 0;
}
