#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stack
{
	char *stack;		//表示栈结构的空间起始地址（比如数组的元素）
	int size;			//最多能放的元素的个数(大小为size * char)
	int top;			//栈的偏移
};

//初始化一个空的顺序栈
struct stack *init_stack(int size)
{
	struct stack *s = malloc(sizeof(struct stack));
	if(s != NULL)
	{
		s->stack = calloc(size, sizeof(char));
		s->size = size;
		s->top = -1;
	}
}

//栈空
bool stack_empty(struct stack *s)
{
	return (s->top == -1);
}

//栈满
bool stack_full(struct stack *s)
{
	return (s->top == s->size-1);
}

//入栈
bool push(struct stack *s, char data)
{
	if (stack_full(s))
	{
		return false;
	}
	//栈顶偏移，表示有一个数据入栈
	s->top++;
	//将新的数据放到栈顶
	s->stack[s->top] = data;		//*(s->stack + s->top) = data;
	return true;
}

//出栈
bool pop(struct stack *s, char data)
{
	if (s->stack[s->top] == data)
	{
		s->top--;
		return true;
	}
	else
	{
		return false;
	}
}

//栈的遍历
void display(struct stack *s)
{
	int i;
	for (i = 0; i < s->top+1; ++i)
	{
		printf("%c ", s->stack[i]);
	}
	printf("\n");
}



int main(int argc, char const *argv[])
{
	char arr[100] = "\0";

	printf("请输入需要判断的表达式：\n");
	gets(arr);
	
	//初始化一个空的顺序栈
	struct stack *s = init_stack(100);

	for (int i = 0; arr[i] != '\0'; i++)
	{
		if(arr[i] == '(' || arr[i] == '[' || arr[i] == '{')
		{
			if(push(s, arr[i]) == 0)
			{
				printf("入栈失败\n");
			}
			//display(s);
		}
		else if (arr[i] == ')')
		{
			if(pop(s, arr[i] - 1) == 0)
				printf("括号不匹配\n");
		}
		else if(arr[i] == ']' || arr[i] == '}')
		{
			if(pop(s, arr[i] - 2) == 0)
				printf("括号不匹配\n");
		}
	}

	if(stack_empty(s) == 1)
	{
		printf("括号匹配\n");
	}
	else
	{
		printf("括号不匹配\n");	
		display(s);
	}
	
	return 0;
}