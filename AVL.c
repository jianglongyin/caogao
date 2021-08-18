#include "link_queue.h"

//二叉树的节点结构体
typedef struct Node
{
	Datatype data;				//数据域
	int height;					//以该节点为接的树的高度
	struct Node *lchild;			//左孩子
	struct Node *rchild;			//右孩子
}AVL_node, *AVL_tree;

//初始化一个空树
AVL_tree init_tree(void)
{
	return NULL;	//空的二叉树
	//BST_tree tree = NULL;
}

//创建节点
AVL_tree create_node(Datatype data)
{
	//为新节点申请空间
	AVL_tree new = malloc(sizeof(AVL_node));
	if (new != NULL)
	{
		new->data = data;
		new->height = 1;					//给节点的高度初始化
		new->lchild = NULL;
		new->rchild = NULL;
	}
	return new;
}

//获取树的高度
int height(AVL_tree root)
{
	if (root != NULL)
	{
		return root->height;
	}
	return 0;
}

//比较两个树高度的最大值作为返回
int max(int h1, int h2)
{
	return (h1>h2?h1:h2);
}

//右旋
AVL_tree avl_right(AVL_tree root)
{
	AVL_tree tmp = root->lchild;
	root->lchild = tmp->rchild;
	tmp->rchild = root;

	//更新节点的高度(树的高度是按照从下往上的)
	root->height = max(height(root->lchild), height(root->rchild))+1;
	tmp->height = max(height(tmp->lchild), height(tmp->rchild))+1; 

	return tmp;
}

//左旋
AVL_tree avl_left(AVL_tree root)
{
	AVL_tree tmp = root->rchild;
	root->rchild = tmp->lchild;
	tmp->lchild = root;

	//更新节点的高度(树的高度是按照从下往上的)
	root->height = max(height(root->lchild), height(root->rchild))+1;
	tmp->height = max(height(tmp->lchild), height(tmp->rchild))+1; 

	return tmp;
}

//自平衡处理函数
AVL_tree avl_opt(AVL_tree root)
{
	//(1)左边不平衡
	//root的左子树高度-右子树高度 > 1
	if (height(root->lchild)-height(root->rchild) > 1)
	{
		//(1.1)左-左不平衡
		if(height(root->lchild->lchild) > height(root->lchild->rchild))
		{
			//对root为根进行右旋
			root = avl_right(root);
		}
		//(1.2)左-右不平衡
		else
		if(height(root->lchild->lchild) < height(root->lchild->rchild))
		{
			//对root的左孩子为根进行左旋
			root->lchild = avl_left(root->lchild);
			//对root为根进行右旋
			root = avl_right(root);
		}
	}
	//(2)右边不平衡
	//root的右子树高度-左子树高度 > 1
	else
	if (height(root->rchild)-height(root->lchild) > 1)
	{
		//(1.1)右-右不平衡
		if(height(root->rchild->rchild) > height(root->rchild->lchild))
		{
			//对root为根进行左旋
			root = avl_left(root);
		}
		else
		//(1.2)右-左不平衡
		if(height(root->rchild->rchild) < height(root->rchild->lchild))
		{
			//对root的右孩子为根进行右旋
			root->rchild = avl_right(root->rchild);
			//对root为根进行左旋
			root = avl_left(root);
		}
	}
	//(3)平衡
	else
	{}
	return root;
}

//插入节点
AVL_tree insert_node(AVL_tree root, AVL_tree new)
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

	//自平衡处理
	root = avl_opt(root);
	//根节点高度更新
	root->height = max(height(root->lchild), height(root->rchild))+1;

	return root;
}

//删除节点
AVL_tree delete_node(AVL_tree root, Datatype data)
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
				AVL_tree tmp = NULL;
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
				AVL_tree tmp = NULL;
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

//遍历树
//先序遍历
void pre_tree(AVL_tree root)
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
void mid_tree(AVL_tree root)
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
void tail_tree(AVL_tree root)
{
	if (root == NULL)
	{
		return ;
	}
	tail_tree(root->lchild);		//左	
	tail_tree(root->rchild);		//右
	printf("%d ", root->data);		//根
}

//查找节点
AVL_tree find_node(AVL_tree root, Datatype data)
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

//按层遍历
void layer_tree(AVL_tree root)
{
	if (root == NULL)
	{
		return ;
	}
	//1、创建一个空队
	p_queue q = init_link_queue();
	//2、将根节点进行入队
	in_queue(q, root->data);
	int n;
	p_node d;
	while(1)
	{
		//3、出队队首（如果队列为空，遍历结束，跳出循环）
		if (!out_queue(q, &d))
		{
			break;
		}
		//出队的时候打印这个数据
		printf("%d ", d->data);
		//取查找出队节点的地址，将这个节点的左右孩子进行入队
		AVL_tree node = find_node(root, d->data);
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

int main(int argc, char const *argv[])
{
	AVL_tree root = init_tree();
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
			//自平衡处理
			root = avl_opt(root);
			//根节点高度更新
			root->height = max(height(root->lchild), height(root->rchild))+1;
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
	printf("按层遍历\n");
	layer_tree(root);
	printf("\n");
	return 0;
}


