#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//�����Թ���С 
#define ROWS 5
#define COLS 5
 
 
//���巽��ö��
typedef enum {
	RIGHT,
	DOWN,
	LEFT,
	UP,
	NONE
}Direction;

//����ջԪ�ؽṹ��
typedef struct {
	int rows;
	int clos;
	int dir;
}StackNode;

//����ջ�ṹ
typedef struct {
	StackNode *data;
	int top;
	int capacity;
}Stack;

//ȫ�ֱ������Թ��ͷ��ʱ��
int maze[ROWS][COLS]={
    {1,1,0,1,1},
    {0,1,1,1,0},
    {0,0,0,1,1},
    {1,0,1,1,1},
    {1,1,1,0,1},
};
int visited[ROWS][COLS]={0};


//ջ��������
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

//����·�������� 
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

// �����Թ���С������Ϊ5x5��
#define ROWS 5
#define COLS 5

// ���巽��ö�٣�˳ʱ��˳���ҡ��¡����ϣ�
typedef enum {
    RIGHT,
    DOWN,
    LEFT,
    UP,
    NONE  // ��ʾδ��ʼ������
} Direction;

// ����ջԪ�ؽṹ��
typedef struct {
    int row;
    int col;
    Direction dir;  // ��ǰ̽���ķ�������
} StackNode;

// ����ջ�ṹ
typedef struct {
    StackNode *data;
    int top;
    int capacity;//���� 
} Stack;

// ȫ�ֱ������Թ��ͷ��ʱ��
int maze[ROWS][COLS] = {
    {1, 1, 1, 1, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 1},
    {1, 0, 1, 1, 0},
    {1, 1, 1, 1, 1}
};
int visited[ROWS][COLS] = {0};

// ջ��������
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

// ���λ���Ƿ����Թ���
bool isValid(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

// ���λ���Ƿ��ͨ��δ����������ͨ����
bool isPassable(int row, int col) {
    return isValid(row, col) && maze[row][col] == 1 && !visited[row][col];
}

// ��ȡ��һ�������λ��
void getNextPosition(int row, int col, Direction dir, int *newRow, int *newCol) {
    switch (dir) {
        case RIGHT: *newRow = row;     *newCol = col + 1; break;
        case DOWN:  *newRow = row + 1; *newCol = col;     break;
        case LEFT:  *newRow = row;     *newCol = col - 1; break;
        case UP:    *newRow = row - 1; *newCol = col;     break;
        default:    *newRow = -1;      *newCol = -1;      break;
    }
}

// ����·����������
bool findPath(int startRow, int startCol, int exitRow, int exitCol) {
    Stack *stack = createStack(ROWS * COLS);
    visited[startRow][startCol] = 1;
    push(stack, (StackNode){startRow, startCol, RIGHT});

    while (!isEmpty(stack)) {
        StackNode current = peek(stack);
        int currRow = current.row;
        int currCol = current.col;
        Direction currDir = current.dir;

        // �������
        if (currRow == exitRow && currCol == exitCol) {
            printf("Path found! Exit at (%d, %d)\n", currRow, currCol);
            return true;
        }

        // ������һ������
        bool found = false;
        int d;
        for (d = currDir; d < 4; d++) {
            int newRow, newCol;
            getNextPosition(currRow, currCol, d, &newRow, &newCol);

            if (isPassable(newRow, newCol)) {
                // ����ջ����̽������
                stack->data[stack->top].dir = d + 1;
                // ѹ����λ�ò����Ϊ�ѷ���
                visited[newRow][newCol] = 1;
                push(stack, (StackNode){newRow, newCol, RIGHT});
                found = true;
                break;
            }
        }

        // ���з��򶼲���ͨ������
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
    // �������(0,0)�ͳ���(4,4)
    findPath(0, 0, 4, 4);
    return 0;
}
*/
