#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//定义迷宫大小 
#define ROWS 5
#define COLS 5
 
 
//定义方向枚举
typedef enum {
	RIGHT,
	DOWN,
	LEFT,
	UP,
	NONE
}Direction;

//定义栈元素结构体
typedef struct {
	int rows;
	int clos;
	int dir;
}StackNode;

//定义栈结构
typedef struct {
	StackNode *data;
	int top;
	int capacity;
}Stack;

//全局变量：迷宫和访问标记
int maze[ROWS][COLS]={
    {1,1,0,1,1},
    {0,1,1,1,0},
    {0,0,0,1,1},
    {1,0,1,1,1},
    {1,1,1,0,1},
};
int visited[ROWS][COLS]={0};


//栈操作函数
Stack* creatStack(int capacity){
	Stack *stack=(Stack*)malloc(sizeof(Stack));
	stack->data=(StackNode*)malloc(capacity*sizeof(StackNode));
	stack->capacity=capacity;
	stack->top=-1;
	return stack;
} 


int push(Stack *stack,StackNode node){
	if(stack->top==stack->capacity-1) return 0;
	stack->top++;
	stack->data[stack->top]=node;
	return 1;
	
}

int stackEmpty(Stack *stack){
	if(stack->top==-1) return 1;
	return 0;
}


void getNextPosition(int row,int col,Direction d,int *newRow,int *newCol){
	switch(d){
		case RIGHT: *newRow = row;     *newCol = col + 1; break;
        case DOWN:  *newRow = row + 1; *newCol = col;     break;
        case LEFT:  *newRow = row;     *newCol = col - 1; break;
        case UP:    *newRow = row - 1; *newCol = col;     break;
        default:    *newRow = -1;      *newCol = -1;      break;
	}
}


bool mazeEmpty(int row,int col){
	if((row>=0&&row<=4)&&(col>=0&&col<=4)&&maze[row][col]){
		return true;
	}
	return false;
}
bool isPassable(int row,int col){
	return mazeEmpty(row,col)&&!visited[row][col];
}

void pop(Stack *stack){
	if(stackEmpty(stack)){
		printf("Stack underflow!\n");
		exit(1);
	}
	stack->top--;
}

//查找路径主函数 
bool findpath(int startRow,int startCol,int exitRow,int exitCol){
	visited[0][0]=1;
	Stack *stack=creatStack(ROWS*COLS);
	if(!stack) return 0; 
	push(stack,(StackNode){startRow,startCol,RIGHT});
    
    
    while(!stackEmpty(stack)){
    	StackNode current=stack->data[stack->top]; 
    	int currRow=current.rows;
    	int currCol=current.clos;
    	Direction currdir=current.dir;
    	
    	if(currRow == exitRow && currCol == exitCol){
    		printf("Path found! Exit at (%d, %d)\n", currRow, currCol);
    		return true;
		}
		
		
		bool found=false;
		int d=0;
		for(d=currdir;d<4;d++){
			int newRow=0;
			int newCol=0;
			getNextPosition(currRow,currCol,d,&newRow,&newCol);
			if(isPassable(newRow, newCol)){
				push(stack,(StackNode){newRow,newCol,RIGHT});
				visited[newRow][newCol]=1;
				found=true;
				break;
			}
		}
		if(!found){
			pop(stack);
			if(!stackEmpty(stack)){
				stack->data[stack->top].dir++;
			}
		}
	}
	printf("No path found.\n");
}



int main(){
	findpath(0,0,4,4);
	return 0;
} 
















 /*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义迷宫大小（假设为5x5）
#define ROWS 5
#define COLS 5

// 定义方向枚举（顺时针顺序：右、下、左、上）
typedef enum {
    RIGHT,
    DOWN,
    LEFT,
    UP,
    NONE  // 表示未初始化方向
} Direction;

// 定义栈元素结构体
typedef struct {
    int row;
    int col;
    Direction dir;  // 当前探索的方向索引
} StackNode;

// 定义栈结构
typedef struct {
    StackNode *data;
    int top;
    int capacity;//容量 
} Stack;

// 全局变量：迷宫和访问标记
int maze[ROWS][COLS] = {
    {1, 1, 1, 1, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 1},
    {1, 0, 1, 1, 0},
    {1, 1, 1, 1, 1}
};
int visited[ROWS][COLS] = {0};

// 栈操作函数
Stack* createStack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (StackNode*)malloc(capacity * sizeof(StackNode));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, StackNode node) {
    if (stack->top >= stack->capacity - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = node;
}

StackNode pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

StackNode peek(Stack *stack) {
    return stack->data[stack->top];
}

// 检查位置是否在迷宫内
bool isValid(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

// 检查位置是否可通（未被访问且是通道）
bool isPassable(int row, int col) {
    return isValid(row, col) && maze[row][col] == 1 && !visited[row][col];
}

// 获取下一个方向的位置
void getNextPosition(int row, int col, Direction dir, int *newRow, int *newCol) {
    switch (dir) {
        case RIGHT: *newRow = row;     *newCol = col + 1; break;
        case DOWN:  *newRow = row + 1; *newCol = col;     break;
        case LEFT:  *newRow = row;     *newCol = col - 1; break;
        case UP:    *newRow = row - 1; *newCol = col;     break;
        default:    *newRow = -1;      *newCol = -1;      break;
    }
}

// 查找路径的主函数
bool findPath(int startRow, int startCol, int exitRow, int exitCol) {
    Stack *stack = createStack(ROWS * COLS);
    visited[startRow][startCol] = 1;
    push(stack, (StackNode){startRow, startCol, RIGHT});

    while (!isEmpty(stack)) {
        StackNode current = peek(stack);
        int currRow = current.row;
        int currCol = current.col;
        Direction currDir = current.dir;

        // 到达出口
        if (currRow == exitRow && currCol == exitCol) {
            printf("Path found! Exit at (%d, %d)\n", currRow, currCol);
            return true;
        }

        // 尝试下一个方向
        bool found = false;
        int d;
        for (d = currDir; d < 4; d++) {
            int newRow, newCol;
            getNextPosition(currRow, currCol, d, &newRow, &newCol);

            if (isPassable(newRow, newCol)) {
                // 更新栈顶的探索方向
                stack->data[stack->top].dir = d + 1;
                // 压入新位置并标记为已访问
                visited[newRow][newCol] = 1;
                push(stack, (StackNode){newRow, newCol, RIGHT});
                found = true;
                break;
            }
        }

        // 所有方向都不可通，回溯
        if (!found) {
            pop(stack);
            if (!isEmpty(stack)) {
                
                
            }
        }
    }

    printf("No path found.\n");
    return false;
}

int main() {
    // 设置入口(0,0)和出口(4,4)
    findPath(0, 0, 4, 4);
    return 0;
}
*/
