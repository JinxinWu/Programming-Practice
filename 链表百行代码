//链表百行代码


#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node *head=NULL;
struct node *List_Init(struct node *head){//创建空链表
    head=(struct node*)malloc(sizeof(struct node));
    head->next=NULL;
    head->data=0;//第一个数据无意义，相当于带头结点的链表
    return head;
}
void List_Append(struct node *head,int data){//追加数据data
    struct node *p,*q;
    p=head;
    q=(struct node*)malloc(sizeof(struct node));
    q->data=data;
    q->next=NULL;
    while(p->next!=NULL)
        p=p->next;
    p->next=q;
}
void List_print(struct node *head){//遍历输出数据
    struct node *p;
    if(head==NULL){//链表未建立
        printf("List not defined!\n");
        return;
    }
    if(head->next==NULL){//链表建立了但为空
        printf("List is empty!\n");
        return;
    }
    p=head->next;
    printf("%d",p->data);
    p=p->next;
    while(p!=NULL){
        printf(" %d",p->data);
        p=p->next;
    }
    printf("\n");
}
void List_Insert(struct node *head,int n,int d){//向链表第n个位置插入数据d
    int i;
    struct node *p,*q;
    q=(struct node*)malloc(sizeof(struct node));
    q->data=d;
    q->next=NULL;
    p=head;
    for(i=1;i<n;i++)
        p=p->next;//head里没有数据，从下一个开始算位置
    q->next=p->next;//把链表下一个位置接给q->next
    p->next=q;//把第n个位置给q
}
int List_Find(struct node *head,int d){//在链表中查找数据d，若找到返回位置，没找到返回-1
    int cnt=1;
    struct node *p;
    p=head->next;
    while(p!=NULL){
        if(p->data==d)
            return cnt;
        p=p->next;
        cnt++;
    }
    return -1;
}
void List_Delete(struct node *head,int n){//删除第n个位置的数据
    struct node *p,*q;
    int i;
    p=head;
    q=p->next;
    for(i=1;i<n;i++)
        if(p!=NULL)
            p=p->next;
    if(p==NULL||p->next==NULL)//考虑第n个位置是否超过或恰好等于数据总数
        return;
    q=p->next;//此时p->next为第n位，将其赋值给q
    p->next=p->next->next;//将第n+1位赋值给第n位
    free(q);//q被释放删除
}
int main(){
    char c;
    int i,n,q,data;
    while(scanf("%c",&c)!=EOF){
        if(c=='I')
            head=List_Init(head);//创建空链表(有节点)后要记录表头位置
        if(c=='A'){
            scanf("%d",&data);
            List_Append(head,data);
        }
        if(c=='C'){
            scanf("%d",&q);
            for(i=0;i<q;i++){
                scanf("%d",&data);
                List_Append(head,data);//用上面那个函数重复向尾部增加数据
            }
        }
        if(c=='P')
            List_print(head);
        if(c=='N'){
            scanf("%d %d",&n,&data);
            List_Insert(head,n,data);
        }
        if(c=='F'){
            scanf("%d",&data);
            if(List_Find(head,data)==-1)
                printf("Not Found!\n");
            else
                printf("index:%d\n",List_Find(head,data));
        }
        if(c=='D'){
            scanf("%d",&n);
            List_Delete(head,n);
        }
    }
    return 0;
}


