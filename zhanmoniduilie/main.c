#include <stdio.h>
#include <stdlib.h>
typedef struct asd//ջ�Ľṹ
{
    int val[50];
    int top;
}* Stack;
void smakenull(Stack s)//��ջ�ƿ�
{
   s->top=0;
}
int sempty(Stack s)//����ջ�Ƿ�Ϊ��
{
    if (s->top<1)
        return 1;
    else
        return 0;
}
int stop(Stack s)//���ջ������
{
    if (sempty(s))
        return -1;
    else
        return s->val[s->top];
}
void spop(Stack s)//ɾ��ջ������
{
    if (sempty(s))
        printf("ջ���޷���ɾ��\n");
    else
        s->top=s->top-1;
}
void spush(int x,Stack s)//������ջ
{
    if (s->top==49)
        printf("ջ���޷�����ջ\n");
    else
    {
        s->top=s->top+1;
        s->val[s->top]=x;
    }
}
void makenull(Stack a,Stack b)//�����ƿ�
{
    smakenull(a);
    smakenull(b);
}
int empty(Stack a,Stack b)//�����ƿ�
{
    if (sempty(a)&&sempty(b))
        return 1;
    else
        return 0;
}
void enqueue(int x,Stack a)//�������
{
    spush(x,a);
}
void dequeue(Stack a,Stack b)//ɾ�����е�һԪ��
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
int Front(Stack a,Stack b)//������е�һ��Ԫ��
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
        Stack a=(Stack)malloc(sizeof(struct asd));//�������ṹ������ʵ�ֶ��й��ܽ���������ջ
        Stack b=(Stack)malloc(sizeof(struct asd));
        while(1)
    {
        printf("����������ѡ��\n1���ƿն���\n2���������������\n3�������������\n4��ɾ�����е�һ������\n5����������Ƿ�Ϊ��\n");
        scanf("%d",&swi);
        switch(swi)
        {
        case 1:
            makenull(a,b);
            break;
        case 2:
            printf("�������������ݣ�\n");
            int x;
            scanf("%d",&x);
            enqueue(x,a);
            break;
        case 3:
            if(empty(a,b))
                printf("ջΪ�ա�\n");
            else{
            printf("���еĵ�һ��Ԫ��Ϊ��\n");
            printf("%d\n",Front(a,b));}
            break;
        case 4:
            dequeue(a,b);
            break;
        case 5:
            if(empty(a,b))
                printf("����Ϊ�ա�\n");
            else
                printf("���зǿա�\n");
                break;
        }
    }
    return 0;
}
