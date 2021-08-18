#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Datatype;

//二叉树的节点结构体
typedef struct Node
{
	Datatype data;	//数据域
	struct Node *lchild;			//左孩子
	struct Node *rchild;			//右孩子
}BST_node, *BST_tree;


typedef struct Queue
{
	Datatype *queue;		//队的连续内存的名字（数组名）队列指针
	int size;				//队的长度
	int front;				//队头
	int rear;				//队尾
}Sq, *node_q;

//初始化一个空的队列
node_q init_queue(int size)
{
	node_q s = malloc(sizeof(Sq));
	if (s != NULL)
	{
		s->queue = calloc(size, sizeof(Datatype));		//为队列申请空间
		s->size = size;									//队的大小
		s->front = s->rear = 0;
	}
	return s;
}

//队空
bool queue_empty(node_q s)
{
	return (s->front == s->rear);
}

//队满
bool queue_full(node_q s)
{
	return ((s->rear+1)%s->size == s->front);
}

//入队
bool in_queue(node_q s, Datatype data)
{
	//判断队满
	if (queue_full(s))
	{
		return false;
	}
	//将rear往后偏移
	s->rear = (s->rear+1) % s->size;
	//填数据
	s->queue[s->rear] = data;
	//*(s->queue + s->rear) = data;
	return true;
}

//出队
bool out_queue(node_q s, Datatype *data)
{
	//判断队空
	if (queue_empty(s))
	{
		return false;
	}
	//将front往后偏移
	s->front = (s->front+1) % s->size;
	//获取
	*data = s->queue[s->front];
	return true;
}

//初始化一个空树
BST_tree init_tree(void)
{
	return NULL;	//空的二叉搜索树
	//BST_tree tree = NULL;
}

//新建节点
BST_tree create_node(Datatype data)
{
	//为新节点申请空间
	BST_tree new = malloc(sizeof(BST_node));
	if (new != NULL)
	{
		new->data = data;
		new->lchild = NULL;
		new->rchild = NULL;
	}
	return new;
}

//插入节点
BST_tree insert_node(BST_tree root, BST_tree new)
{
	if (new == NULL)
	{
		return root;
	}
	//如果原来二叉搜索树是空的
	//那么第一次插入的节点就是根节点
	if (root == NULL)
	{
		return new;
	}
	//原本有节点的情况
	else
	{
		//(1)新节点比root小，将new插入到root的左子树中
		if (new->data < root->data)
		{
			root->lchild = insert_node(root->lchild, new);
		}
		//(2)新节点比root大，将new插入到root的右子树中
		else
		if (new->data > root->data)
		{
			root->rchild = insert_node(root->rchild, new);
		}
		//(3)新节点与root相等，插入失败
		else
		{
			printf("该节点已存在，插入失败\n");
		}
	}

	return root;
}

//查找节点
BST_tree find_node(BST_tree root, Datatype data)
{
	if(root == NULL)
	{
		return NULL;
	}
	else
	{
		//(1)待查找节点小于根节点数据，从左子树查找
		if(data < root->data)
		{
			return find_node(root->lchild, data);
		}
		//(1)待查找节点大于根节点数据，从右子树查找
		else
		if (data > root->data)
		{
			return find_node(root->rchild, data);
		}
		else
		{
			return root;
		}
	}
}

//遍历树
//先序遍历
void pre_tree(BST_tree root)
{
	if (root == NULL)
	{
		return ;
	}
	printf("%d ", root->data);	//根
	pre_tree(root->lchild);		//左
	pre_tree(root->rchild);		//右
}

//中序遍历
void mid_tree(BST_tree root)
{
	if (root == NULL)
	{
		return ;
	}
	mid_tree(root->lchild);			//左
	printf("%d ", root->data);		//根
	mid_tree(root->rchild);			//右
}

//后序遍历
void tail_tree(BST_tree root)
{
	if (root == NULL)
	{
		return ;
	}
	tail_tree(root->lchild);		//左	
	tail_tree(root->rchild);		//右
	printf("%d ", root->data);		//根
}

//按层遍历
void layer_tree(BST_tree root)
{
	if (root == NULL)
	{
		return ;
	}
	//1、创建一个空队
	node_q q = init_queue(1024);
	//2、将根节点进行入队
	in_queue(q, root->data);
	int n;
	while(1)
	{
		//3、出队队首（如果队列为空，遍历结束，跳出循环）
		if (!out_queue(q, &n))
		{
			break;
		}
		//出队的时候打印这个数据
		printf("%d ",n);
		//取查找出队节点的地址，将这个节点的左右孩子进行入队
		BST_tree node = find_node(root, n);
		if (node->lchild != NULL)
		{
			in_queue(q, node->lchild->data);
		}
		if (node->rchild != NULL)
		{
			in_queue(q, node->rchild->data);
		}
	}
	printf("\n");
}

//删除节点
BST_tree delete_node(BST_tree root, Datatype data)
{
	//如果树为空，直接将根节点返回
	if (root == NULL)
	{
		return root;
	}
	else
	{
		//(1)待删除节点比根节点小，在根节点的左子树中删除
		if (data < root->data)
		{
			root->lchild = delete_node(root->lchild, data);
		}
		//(2)待删除节点比根节点大，在根节点的右子树中删除
		else
		if (data > root->data)
		{
			root->rchild = delete_node(root->rchild, data);
		}
		//(3)待删除节点跟根节点数据相等，这个根节点就是待删节点
		else
		{
			//(3.1)当待删节点有左子树，用左子树中最大节点接替待删除节点
			if (root->lchild != NULL)
			{
				//找左子树中最大节点，不断往右找
				BST_tree tmp = NULL;
				for(tmp = root->lchild; tmp->rchild != NULL; tmp = tmp->rchild);
				//接替
				root->data = tmp->data;
				//然后在左子树中删掉原来用来接替的节点，考虑这个接替的节点是否还有左孩子
				root->lchild = delete_node(root->lchild, tmp->data);
			}
			//(3.2)当待删节点只有右子树，用右子树中最小节点接替待删除节点
			else
			if (root->rchild != NULL)
			{
				//找右子树中最小节点，不断往右找
				BST_tree tmp = NULL;
				for(tmp = root->rchild; tmp->lchild != NULL; tmp = tmp->lchild);
				//接替
				root->data = tmp->data;
				//然后在右子树中删掉原来用来接替的节点，考虑这个接替的节点是否还有右孩子
				root->rchild = delete_node(root->rchild, tmp->data);
			}
			//(3.3)当待删节点没有左右子树，删除节点是目前子树的叶子（根）节点，直接删除
			else
			{
				free(root);
				root = NULL;
			}
		}
	}
	return root;
}

int main(int argc, char const *argv[])
{
	//初始化空树
	BST_tree root = init_tree();

	int num;
	while(1)
	{
		scanf("%d", &num);
		if (num > 0)
		{
			root = insert_node(root, create_node(num));
		}
		else
		if (num < 0)
		{
			root = delete_node(root, -num);
			layer_tree(root);
		}
		else
		{
			break;
		}
	}
	printf("先序遍历\n");
	pre_tree(root);
	printf("\n");
	printf("中序遍历\n");
	mid_tree(root);
	printf("\n");
	printf("后序遍历\n");
	tail_tree(root);
	printf("\n");
	printf("按层遍历\n");
	layer_tree(root);

	
	return 0;
}
