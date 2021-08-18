#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

//头文件的声明
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//宏定义

//组合数据类型
typedef int Datatype;

//链式队列的节点管理结构体
typedef struct node
{
	Datatype data;				//数据域
	struct node *next;			//指针域	
}Node, *p_node;

//链式队列管理结构体
typedef struct link_queue
{
	p_node front;				//队首指针
	p_node rear;				//队尾指针
	int size;					//当前元素个数
}Link_queue, *p_queue;

//全局变量

//函数声明

//初始化空链式队列
p_queue init_link_queue(void);


//判断链式队列队空
bool link_queue_empty(p_queue q);


//创建节点
p_node create_node_q(Datatype data);

//入队
bool in_queue(p_queue q, Datatype data);


//出队
bool out_queue(p_queue q, p_node *data);

//遍历
void display(p_queue q);

#endif