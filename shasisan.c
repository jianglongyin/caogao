#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

int display( struct node * q )
{
    int i = 0 ;
    struct node * p = q;
    while(p->next != q)
    {
        p = p->next;
       ++i;
    }
    return i ;
}



int main()
{
    struct node *head,*p,*q;            //head为链表头
    int n,i,k;
 
    //输入n
    printf("有n个人参与此游戏 ，每报到第k人 ， 此人退出游戏\n");
    printf("please input n and k:\n");
    scanf("%d %d",&n,&k);
 
    //建立链表
    //创建第一个结点， head 指向表头结点,p指向表尾结点
    head = p =(struct node *)malloc(sizeof(struct node));           
    p->data = 1;
    //构建单循环链表
    for( i=2;i<=n;i++)
    {
        //q为当前正在创建的的结点                                            
        q = (struct node *)malloc(sizeof(struct node));            
        q ->data = i;
        p ->next = q; 
        //将q链入表尾 
        p=q;                                        
    }
    //头尾相连 构建循环
    p->next = head;                                                 

    //删除过程
    q=head;                                                       //head报数为1
    while( display( p ) != 2)
    {                                          //表中元素多于一个
        if(k%2 !=0)
        {
            for ( i= 0; i < k/2; i++) 
            {
                p = q->next;
                q = p->next;
            }
            //删除q
             //绕过结点q
            p->next = q->next; 
            //显示被删除的编号                               
            printf("%d\t",q->data);
            //回收被删除的空间                        
            free(q) ; 
            //让q指向报1的结点                                       
            q = p->next;                                     
        } 

        else if(k%2 ==0)
        {
            for(i=0;i<k/2-1;i++)
            {
               p = q->next;
               q = p->next;
            }
            p=q->next;

           //删除p
            //绕过结点q
            q->next=p->next; 
            //显示被删除的编                                     
            printf("%d\t",p->data); 
             //回收被删除的空间                          
            free(p); 
            //让q指向报1的结点                                         
            q=q->next;                                       
        }

    }
    //打印结果
    printf("\n最后剩下:%d , %d\n",q->data , q->next->data);
    return 0;
}