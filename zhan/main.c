#include <stdio.h>
#include <stdlib.h>
typedef struct celltype//���������õ�������������
{
    int cal;
    struct celltype * next;
}* line;
typedef struct queue
{
    line front;
    line rear;
}* que;
void lmakenull(que q)//�����ƿ�
{
    q->front=(line)malloc(sizeof(struct celltype));
    q->front->next=NULL;
    q->rear=q->front;
}
int lempty(que q)//��������Ƿ�Ϊ��
{
    if(q->front==q->rear)
        return 1;
    else
        return 0;
}
void enqueue(int x,que a)//���ݽ���
{
    a->rear->next=(line)malloc(sizeof(struct celltype));
    a->rear=a->rear->next;
    a->rear->cal=x;
    a->rear->next=NULL;
}
void dequeue(que q)//ɾ������Ԫ��
{
    line tmp;
    if (lempty(q))
        printf("ջΪ�ա�\n");
    else
    {
        tmp=q->front->next;
        q->front->next=tmp->next;
        //free(tmp);
        if (q->front->next==NULL)
            q->rear=q->front;
    }
}
int lfront(que q)//�������Ԫ��
{
    if (lempty(q))
        return -1;
    else
        return q->front->next->cal;
}
void makenull(que a,que b)//ջ�ƿ�
{
    lmakenull(a);
    lmakenull(b);
}
void push(int x,que a)//������ջ
{
    enqueue(x,a);
}
int empty(que a,que b)//����ջ�Ƿ�Ϊ��
{
    if(lempty(a)&&lempty(b))
        return 1;
    else
        return 0;
}
int top(que a,que b)//���ջ������
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
void pop(que a,que b)//ɾ��ջ������
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
    que a=(que)malloc(sizeof(struct queue));//�ö���ģ��ջҪ�õ����������еĽṹ��
    que b=(que)malloc(sizeof(struct queue));
    int swi,x;
    while(1)
    {
      printf("����������ѡ��\n1���ƿ�ջ\n2��������ջ\n3�����ջ������\n4��ɾ��ջ������\n5������ջ�Ƿ�Ϊ��\n");
      scanf("%d",&swi);
      switch(swi)
      {
      case 1:
        makenull(a,b);
        break;
      case 2:
        printf("�������������ݣ�\n");
        scanf("%d",&x);
        push(x,a);
        break;
      case 3:
        printf("ջ������Ϊ��\n");
        if(!empty(a,b))
        printf("%d\n",top(a,b));
        else
        printf("ջΪ��\n");
        break;
      case 4:
        pop(a,b);
        break;
      case 5:
        if(empty(a,b))
            printf("ջΪ�ա�\n");
        else
            printf("ջ�ǿա�\n");
      }
    }
    return 0;
}
