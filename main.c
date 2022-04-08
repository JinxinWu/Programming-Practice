#include <stdio.h>
#include <malloc.h>
#include <assert.h>

struct	Node
{
    int	digit; //����
    struct Node *next, *prev; //ǰ����ָ��
};
//�޷��Ŵ����ṹ��
struct UBigNumber
{
    int flag;
    int digitCount; //λ��
    struct Node *pHead, *pTail; //ָ��ͷ��㣬β���
};
//���к������صĴ���ռ�õ��ڴ���Դ�ɺ��������߸����ͷ�
//�����޷��Ŵ���
struct UBigNumber InputUBN ();
//��ӡ�޷��Ŵ���
void PrintUBN (struct UBigNumber ubn);
//�����޷��Ŵ������
struct UBigNumber AddUBN (struct UBigNumber *pA, struct UBigNumber *pB);
//�����޷��Ŵ������ͷſռ�
void DestoryUBN (struct UBigNumber *pA);

//���к������޷��Ŵ�������������
//������ʾ�޷��Ŵ����ô�ͷ���˫����
void _InitUBN (struct UBigNumber *pUBN);
//�޷��Ŵ���β�����һλ��
void _AppendDigit (struct UBigNumber *pUBN, int digit);
//�޷��Ŵ���ǰ�����һλ��
void _AppendFrontDigit (struct UBigNumber *pUBN, int digit);
//�޷��Ŵ����淶��ʾ��ȥ����λ����0�����ٺ�һλ����
void _Normalize (struct UBigNumber *pUBN);
//��̬����һ����㣬���ؽ��ָ��
//����ʧ��ʱ���򻯳����˳�����
struct Node *_NewNode ();

//�����޷��Ŵ������
struct UBigNumber SubUBN (struct UBigNumber *pA, struct UBigNumber *pB);
//�����޷��Ŵ������
struct UBigNumber MultiplyUBN (struct UBigNumber *pA, struct UBigNumber *pB);

//�޷��Ŵ�����1λ��
struct UBigNumber _MultiplyDigit (struct UBigNumber *pA, int digit);
//�����޷��Ŵ�����[start, end)������������ɵ��޷��Ŵ���
//������Χ�������ֺ��ԣ����Ժ������в�����ʱ����0
struct UBigNumber _FetchSub (struct UBigNumber *pA, int start, int end);

void exchange(struct UBigNumber* p,struct UBigNumber* q)//��������
{
    struct	Node* new=p->pHead;
    p->pHead=q->pHead;
    q->pHead=new;
    //printf("%d\n",p->pHead->next->data);
    new=p->pTail;
    p->pTail=q->pTail;
    q->pTail=new;
    //printf("%d\n",q->pHead->next->data);
    //free(new);
}
int big_small(struct UBigNumber* p,struct UBigNumber* q)//�ȽϾ���ֵ�Ĵ�С��ǰ�ߴ󷵻�0�����ߴ󷵻�1
{
    struct	Node* pnode=p->pHead->next;
    struct	Node* qnode=q->pHead->next;
    if(p->digitCount>q->digitCount)
        return 0;
    else if(p->digitCount<q->digitCount)
    {
        exchange(p,q);
        return 1;
    }
    else
    {
        while(pnode->digit!=qnode->digit||pnode!=NULL||qnode!=NULL)
        {
            pnode=pnode->next;
            qnode=qnode->next;
        }
        if(pnode->digit>qnode->digit)
            return 0;
        else if(pnode->digit<qnode->digit)
        {
            exchange(p,q);
            return 1;
        }
    }
    return 0;
}
void printresult(struct UBigNumber A,struct UBigNumber B)
{
    struct UBigNumber C,D;
    _InitUBN(&C);
    _InitUBN(&D);
    //��������
	if(A.flag==1&&B.flag==1)//A>0,B>0
    {
        if(big_small(&A,&B)==0)
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            PrintUBN(C);
            printf("\n");
            PrintUBN(D);
        }
        else
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            PrintUBN(C);
            printf("\n");
            printf("-");
            PrintUBN(D);
        }
    }
    if(A.flag==1&&B.flag==-1)//A>0,B<0
    {
        if(big_small(&A,&B)==0)
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            PrintUBN(D);
            printf("\n");
            PrintUBN(C);
        }
        else
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            printf("-");
            PrintUBN(D);
            printf("\n");
            PrintUBN(C);
        }
    }
    if(A.flag==-1&&B.flag==1)//A<0,B>0
    {
        if(big_small(&A,&B)==0)
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            printf("-");
            PrintUBN(D);
            printf("\n");
            printf("-");
            PrintUBN(C);
        }
        else
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            PrintUBN(D);
            printf("\n");
            printf("-");
            PrintUBN(C);
        }
    }
    if(A.flag==-1&&B.flag==-1)//A<0,B<0
    {
        if(big_small(&A,&B)==0)
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            printf("-");
            PrintUBN(C);
            printf("\n");
            printf("-");
            PrintUBN(D);
        }
        else
        {
            C=AddUBN(&A,&B);
            D=SubUBN(&A,&B);
            printf("-");
            PrintUBN(C);
            printf("\n");
            PrintUBN(D);
        }
    }
    DestoryUBN(&C);
	DestoryUBN(&D);
}

int main ()
{   struct UBigNumber A, B, C;
    A = InputUBN (); //�޷��Ŵ�������
    B = InputUBN ();
    C = MultiplyUBN (&A, &B); //�޷��Ŵ������

    printresult(A,B);
    printf ("\n");
    PrintUBN (C);

    DestoryUBN (&A); //�����޷��Ŵ���
    DestoryUBN (&B);
    DestoryUBN (&C);
    return 0;
}

//�����޷��Ŵ���
struct UBigNumber InputUBN ()
{
    struct UBigNumber result;
    _InitUBN(&result);

    char ch;
	ch=getchar();
	if(ch=='-')
	    result.flag=-1;
	else
	    result.flag=1;
	//printf("%d\n",result.flag);//���
	while(ch<'0'||ch>'9')
	    ch=getchar();
	//printf("%c",ch);//���
	while(ch>='0'&&ch<='9')
	{
		_AppendDigit(&result,ch-'0');
		ch=getchar();
	}
    _Normalize(&result);
    return result;
}
//��ӡ�޷��Ŵ���
void PrintUBN (struct UBigNumber ubn)
{
    if(ubn.flag==-1)
        printf("-");
    assert (ubn.digitCount > 0 && ubn.pHead->next != NULL); //���� �� ������1λ����
    struct Node *la = ubn.pHead->next; //ͷ��������ݣ�����
    while (la)
    {
        printf ("%d", la->digit);
        la = la->next;
    }
}
//�����޷��Ŵ������
struct UBigNumber AddUBN (struct UBigNumber *pA, struct UBigNumber *pB)
{
    struct UBigNumber result, *pResult = &result;
    _InitUBN(pResult);
    int iCarry = 0; //��λ����ʼ0
    struct Node *p1, *p2;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)   //������ͬλ����
    {
        int digit = p1->digit + p2->digit + iCarry;
        iCarry = digit / 10; //�½�λ
        digit %= 10;         //��ǰ���λ
        _AppendFrontDigit (pResult, digit); //�����������λ
        p1 = p1->prev; //׼������ǰһλ
        p2 = p2->prev;
    }
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit (pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead)  //�ڶ�����ʣ��λ����
    {
        int digit = p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit (pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0) //����λ����
        _AppendFrontDigit (pResult, iCarry);
    return result;
}
//�����޷��Ŵ������ͷſռ�
void DestoryUBN (struct UBigNumber *pUBN)
{
    while (pUBN->pHead != NULL)  //��պ�Ӧ��ֻʣһ��ͷ���
    {
        struct Node *p =  pUBN->pHead;  //��ɾ�����
        pUBN->pHead = p->next;          //βָ��ǰ��
        free (p);                       //�ͷŽ��
    }
}
//������ʾ�޷��Ŵ����ô�ͷ���˫����
void _InitUBN (struct UBigNumber *pUBN)
{
    struct Node *p = _NewNode ();
    pUBN->pHead = pUBN->pTail = p; //��ͷ���
    p->next = p->prev = NULL;
    pUBN->digitCount = 0; //λ��0
}
//�޷��Ŵ���β�����һλ��
void _AppendDigit (struct UBigNumber *pUBN, int digit)
{
    if (pUBN->digitCount == 1 && pUBN->pTail->digit == 0)//ԭֻ��һ����λ0
    {
        pUBN->pTail->digit = digit; //λ�����䣬��ֵΪ0
        return;
    }
    struct Node *p = _NewNode ();  //�����½��
    p->digit = digit;              //���ý����ֵ
    p->next = NULL;                //�޸�˫������ӳ�Ϊ��β�����
    p->prev = pUBN->pTail;
    pUBN->pTail->next = p;
    pUBN->pTail = p;
    ++pUBN->digitCount;             //�޸�λ��
}
//�޷��Ŵ���ǰ���һλ��
void _AppendFrontDigit (struct UBigNumber *pUBN, int digit)
{
    struct Node *p = _NewNode (); //�����½��
    p->digit = digit;             //���ý����ֵ
    p->next = pUBN->pHead->next;  //�޸�˫���������ͷ����
    if (p->next != NULL)
        p->next->prev = p;
    p->prev = pUBN->pHead;
    pUBN->pHead->next = p;
    if (pUBN->pTail == pUBN->pHead)
        pUBN->pTail = p;          //ԭ��ֻ��ͷ���ʱ���½��Ҳ��β���
    ++pUBN->digitCount;           //�޸�λ��
}
//�޷��Ŵ����淶��ʾ��ȥ����λ����0�����ٺ�һλ����
void _Normalize (struct UBigNumber *pUBN)
{
    if (pUBN->digitCount == 0)
        _AppendDigit (pUBN, 0);
    while (pUBN->digitCount > 1 && pUBN->pHead->next->digit == 0)  //ȥ����λ�����0
    {
        struct Node *p;
        p = pUBN->pHead->next; //��ɾ���Ľ��
        pUBN->pHead->next = p->next; //����������ɾ��
        p->next->prev = pUBN->pHead; //����������ɾ��
        free (p);                       //�ͷŽ��
        --pUBN->digitCount;          //����λ��
    }
}
//��̬����һ����㣬���ؽ��ָ��
//����ʧ��ʱ���򻯳����˳�����
struct Node *_NewNode ()
{
    struct Node *p;
    p = (struct Node *) malloc (sizeof (struct Node));
    if (p == NULL)   //����ʧ��
    {
        printf ("Error : out of memory\n");
        exit (-1); //�򻯳����˳�����
    }
    return p;
}

//�����޷��Ŵ������
struct UBigNumber SubUBN (struct UBigNumber *pA, struct UBigNumber *pB)
{
    struct UBigNumber result;
    _InitUBN(&result);
    int iCarry = 0; //��λ����ʼ0
    struct Node *p1, *p2;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)   //������ͬλ����
    {
        int digit = p1->digit - p2->digit + iCarry;
        iCarry = 0;
        if (digit < 0)
        {
            digit += 10;         //��ǰ���λ
            iCarry = -1; //�½�λ
        }
        _AppendFrontDigit (&result, digit); //�����������λ
        p1 = p1->prev; //׼������ǰһλ
        p2 = p2->prev;
    }
    assert (p2 == pB->pHead);
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit + iCarry;
        iCarry = 0;
        if (digit < 0)
        {
            digit += 10;         //��ǰ���λ
            iCarry = -1; //�½�λ
        }
        _AppendFrontDigit (&result, digit); //�����������λ
        p1 = p1->prev; //׼������ǰһλ
    }
    assert (iCarry == 0);
    _Normalize(&result);
    return result;
}
//�����޷��Ŵ������
struct UBigNumber MultiplyUBN (struct UBigNumber *pA, struct UBigNumber *pB)
{
    //�ݹ���ֹ����
    if (pB->digitCount == 1)
        return _MultiplyDigit (pA, pB->pTail->digit);
    else if (pA->digitCount == 1)
        return _MultiplyDigit (pB, pA->pTail->digit);
    // �����ֳ���
    int m = pA->digitCount;
    int n = pB->digitCount;

    int h = (m> n?m:n) / 2;
    /* ���Ϊa, b, c, d */
    struct UBigNumber a, b, c, d;

    a = _FetchSub (pA, 0, m - h); //��m-hλ
    b = _FetchSub (pA, m - h, m); //��hλ
    c = _FetchSub (pB, 0, n - h);  //��m-hλ
    d = _FetchSub (pB, n - h, n);  //��hλ
    // ����z2, z0, z1, �˴��ĳ˷�ʹ�õݹ�
    struct UBigNumber z0, z1, z2;

    z2 = MultiplyUBN (&a, &c); //z2 = a * c;
    z0 = MultiplyUBN (&b, &d); //z0 = b * d;
    struct UBigNumber  t1, t2, t3,t4,t5, result;
    t1 = AddUBN(&a, &b);    //t1 = a+b
    t2 = AddUBN(&c, &d);     //t2 = c+d
    //���ٸ�����ʹ�õ��޷��Ŵ���
    DestoryUBN (&a);
    DestoryUBN (&b);
    DestoryUBN (&c);
    DestoryUBN (&d);
    t3 = MultiplyUBN (&t1, &t2); //t3 = (a+b)*(c+d)
    t4 = AddUBN(&z0, &z2);   //t4 = z0 + z2
    z1 = SubUBN(&t3, &t4);   //z1 = (a+b)*(c+d) - z2 - z0

    int i;
    for (i= 0; i < 2 *h; ++i) //z2 *= (10^(2*h))
        _AppendDigit (&z2, 0);
    for (i= 0; i < h; ++i) //z1 *= (10 ^ h)
        _AppendDigit (&z1, 0);
    t5 = AddUBN(&z2, &z1); //t5= z2*10^2h + z1 * 10^h
    result = AddUBN(&t5, &z0); //result = z2*10^2h + z1 * 10^h +z0
    //������˷�������
    if((pA->flag==-1&&pB->flag!=-1)||(pA->flag!=-1&&pB->flag==-1))
        result.flag=-1;

    DestoryUBN (&z0);
    DestoryUBN (&z1);
    DestoryUBN (&z2);
    DestoryUBN (&t1);
    DestoryUBN (&t2);
    DestoryUBN (&t3);
    DestoryUBN (&t4);
    DestoryUBN (&t5);
    return result;
}

//�޷��Ŵ�����1λ��
struct UBigNumber _MultiplyDigit (struct UBigNumber *pA, int digit2)
{
    struct UBigNumber result;
    _InitUBN (&result);
    if (digit2 == 0)
    {
        _AppendDigit (&result, 0);
        return result;
    }

    int iCarry = 0; //��λ����ʼ0
    struct Node *p1;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit * digit2 + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit (&result, digit);
        p1 = p1->prev;
    }
    if (iCarry != 0) //����λ����
        _AppendFrontDigit (&result, iCarry);
    return result;
}

//�����޷��Ŵ�����[start, end)������������ɵ��޷��Ŵ���
//������Χ�������ֺ��ԣ����Ժ������в�����ʱ����0
struct UBigNumber _FetchSub (struct UBigNumber *pA, int start, int end)
{
    struct UBigNumber result;
    _InitUBN (&result);
    int i = 0;
    struct Node *p = pA->pHead->next;
    while (i < start && p != NULL)
    {
        p = p->next;
        ++i;
    }
    while (i < end && p != NULL)
    {
        _AppendDigit (&result, p->digit); //�����β��
        p = p->next;
        ++i;
    }
    _Normalize (&result);
    return result;
}
