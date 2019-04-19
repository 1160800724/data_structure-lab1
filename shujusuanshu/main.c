#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 30
typedef struct numberstack//���ڴ�����ֵ�ջ�ṹ
{
    double val[50];
    int top;
}* numstack;
void nummakenull(numstack s)//����ջ�ƿ�
{
    s->top=0;
}
int numempty(numstack s)//��������ջ�Ƿ�Ϊ��
{
    if(s->top<1)
        return 1;
    else
        return 0;
}
double numtop(numstack s)//�������ջջ��Ԫ��
{
    if (numempty(s))
        return -1;
    else
        return (s->val[s->top]);
}
void numpop(numstack s)//ɾ������ջջ��Ԫ��
{
    if(numempty(s))
        s->top=0;
    else
        s->top=s->top-1;
}
void numpush(double x,numstack s)//������ջ
{
    if(s->top==49)
        printf("ջ��\n");
    else
        s->top=s->top+1;
        s->val[s->top]=x;
}
typedef struct df{//����ջ�Ľṹ
    char cval[max];
    int top;
}* charstack;

void charmakenull(charstack s)//����ջ�ƿ�
{
    s->top=0;
}
int charempty(charstack s)//�������ջ�Ƿ�Ϊ��
{
    if(s->top<1)
        return 1;
    else
        return 0;
}
char chartop(charstack s)//�������ջջ��Ԫ��
{
    if (charempty(s))
        return 'f';//���ջ�շ���f
    else
        return (s->cval[s->top]);
}
void charpop(charstack s)//ɾ������ջջ��Ԫ��
{
    if(charempty(s))
        s->top=0;
    else
        s->top=s->top-1;
}
void charpush(char x,charstack s)//������ջ
{
    if(s->top==max-1)
        printf("ջ��\n");
    else
        s->top=s->top+1;
        s->cval[s->top]=x;
}
int opjuge(char a)//�ж�����������ȼ�
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
    charstack op=(charstack)malloc(sizeof(struct df));//���ڴ���������ջ
    charstack hou=(charstack)malloc(sizeof(struct df));//���ڴ�ź�׺���ʽ��ջ
    charmakenull(op);
    charmakenull(hou);
    numstack shu=(numstack)malloc(sizeof(struct numberstack));//���ڴ�����ֵ�ջ
    nummakenull(shu);
    int i=0,j=1,k=0,l,flag=-1;
    double p,q,b=1;
    char str[50];//��¼��׺���ʽ
    char suan[9];//���ڶ�λ����ʵ�����
    printf("\n��������׺���ʽ������f�������У�������Ӣ�����ţ���\n");
    scanf("%s",str);
    if(str[0]=='f')
        break;
    printf("��׺���ʽΪ\n");
    while(str[i]!='\0')//ɨ����׺���ʽ��ת���ɺ�׺���ʽ�����ͬʱ������ĺ�׺���ʽ��¼������ջhou��
    {
        if(i==0&&str[i]=='-') charpush(str[i],op);
        else if((str[i]>='0'&&str[i]<='9')||str[i]=='.')//��������ֻ���С����ֱ�����
        {
            printf("%c",str[i]);
            charpush(str[i],hou);
        }
        else//�������ѹ��ջ���ߵ���ջ
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
    if (!charempty(op))//����ջ��δ�����������
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
    for(j=1;j<=(hou->top);j++)//ɨ���׺���ʽ���������׺���ʽ��������
    {
        if((hou->cval[j]>='0'&&hou->cval[j]<='9')||hou->cval[j]=='.')
        {
            if(hou->cval[j]=='.')//���ڼ�¼С������ֵ�λ��
                flag=k;
            else
            {
               suan[k]=hou->cval[j];
               k++;//�����һ��1�����Ժ�����k-1
            }
        }
        else
        {
            double a=0;
            for(l=k-1;l>=0;l--)//�����λ����ֵ
            {
               a=a+(suan[l]-48)* pow(10,k-1-l);
            }
            if(k!=0&&a==0)
            {
                printf("���ݲ���Ϊ0\n");
                goto L1;
            }
            if(a!=0)
            {
               if(flag!=-1)
               a=a/pow(10,k-flag);//�����λС����ֵ
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

        else//�����������������
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
    printf("\n���ս��Ϊ��\n");
    if(str[0]=='-')
    printf("%lf",-numtop(shu));
    else
        printf("%lf",numtop(shu));
    numpop(shu);
    }
    L1:
    return 0;
}
