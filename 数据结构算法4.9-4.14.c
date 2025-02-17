#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
//定义常量 
#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define MaxBookNum 1000
#define MaxKeyNum 2500
#define MaxLineLen 500
#define MaxWordNum 10
const char *common_words[10]={"the", "of", "and", "in", "to", "a", "is", "that", "it", "for"};
const int common_words_count=10;
typedef struct ListkNode{
	int data;  //定义链表元素结构 
	struct ListkNode *next;
}ListNode,*LinkList;

typedef struct { 
	int last;     //定义词表长度 
	char *item[MaxWordNum];  //定义字符串数组
}WordListType; 


typedef struct {
	char *key;
	LinkList bnolist;
}IdxTermType;//定义索引表元素 

typedef struct {
	IdxTermType item[MaxKeyNum+1];
	int last; 
}IdxListType;//定义索引表数据类型 

   char *buf;  //定义书目缓冲区 
   WordListType wdlist;  //定义词表


//声明
void InitIdxList(IdxListType *idxlist);
	//初始化操作，置索引表idxlist为空表，且在idxlist->item[0]设一空串 

void GetLine(FILE *f);
	//从文件f读入一个书目信息到书目串缓冲区buf  
 
int ExtractKeyWord(int *bno);
	//从Buf中提取书名关键词到词表wdlist,书号存入bno。 

int InsIdxList(IdxListType *idxlist,int bno);
	//将书号为bno的书名关键词按词典顺序插入 索引表idxlist
	
void putText(FILE *g,IdxListType idxlist);
//将生成的索引表idxlist输出到文件g。

bool cmp_common_word(const char *word);

void InserNewKey(IdxListType **idxlist,int i,char *wb);


void InitIdxList(IdxListType *idxlist){
	idxlist->last=0;
	int i=0;
	for(i=0;i<=MaxKeyNum;i++){
		idxlist->item[i].bnolist=NULL;
		idxlist->item[i].key=NULL;
	}
}

void GetLine(FILE *f){
	if(!(fgets(buf,MaxLineLen,f))){
		buf[0]='\0';
    }
}

bool cmp_common_word(const char *word){
	int i=0;
	for(i=0;i<common_words_count;i++){
		if(strcasecmp(word,common_words[i])==0){
			return true;
		}
	}
	return false;
}
int ExtractKeyWord(int *bno){
	// 假设buf格式为 "书号 原始书名"
	char *token=strtok(buf," ");
	if (token == NULL) return ERROR;
	*bno=atoi(token);//提取书号
	
	//提取剩余部分
	token=strtok(NULL,"\n");
	if(token==NULL) return ERROR;
	
	//分割书名
	wdlist.last=0;
	char *word=strtok(token," ");
	while(word!=NULL&&wdlist.last<MaxWordNum){
		if(!cmp_common_word(word)){
			wdlist.item[wdlist.last]=strdup(word);
			if (wdlist.item[wdlist.last] == NULL) {
                return OVERFLOW;
            }
			wdlist.last++;
		}
		word=strtok(NULL," ");
	} 
	return OK;
}

int Locate(IdxListType *idxlist,char *wb,bool *found){
	int i=0;
	*found=false;
	for(i=0;i<idxlist->last;i++){
		if(!strcmp(wb,idxlist->item[i].key)){
			*found=true;
			return i;
		}else if(strcmp(wb,idxlist->item[i].key)<0){
			return i;
		}
	}
	
	return idxlist->last;
}

void InitList(LinkList *head){
	(*head)=(LinkList)malloc(sizeof(ListNode));
	if (*head != NULL) {
        (*head)->next = NULL;
    }
}
void InsertNewKey(IdxListType *idxlist,int pos,char *wb){
	if (idxlist->last >= MaxKeyNum) return;
	int j=0;
	for(j=idxlist->last;j>pos;j--){
		idxlist->item[j]=idxlist->item[j-1]; 
	}
	idxlist->item[pos].key = strdup(wb); 
	InitList(&idxlist->item[pos].bnolist);
	idxlist->last++;
	
}
int InsertBook(IdxListType *idxlist,int pos,int bno){
	if ((idxlist)->item[pos].bnolist == NULL) {
        InitList(&(idxlist)->item[pos].bnolist);
        if (idxlist->item[pos].bnolist == NULL) return OVERFLOW;
    }
	LinkList p=(LinkList)malloc(sizeof(ListNode));
	if (p == NULL) return OVERFLOW;
	p->data=bno;
	p->next=idxlist->item[pos].bnolist->next;
	idxlist->item[pos].bnolist->next=p;
	return OK;
}
int InsIdxList(IdxListType *idxlist,int bno){
	int i=0;
	char *wd=wdlist.item[i];
	bool found=false;
	for(i=0;i<wdlist.last;i++){
		int pos=Locate(idxlist,wd,&found);
		if(!found) InsertNewKey(idxlist,pos,wd); 
		if(!(InsertBook(idxlist,pos,bno))) return OVERFLOW;
	}
	return OK;
}

void PutText(FILE *g,IdxListType *idxlist){
	int i=0;
	for (i = 0; i <idxlist->last; i++) {
        fprintf(g, "关键词: %s\n书号列表: ", idxlist->item[i].key);
        ListNode *p = idxlist->item[i].bnolist->next;
        while (p != NULL) {
            fprintf(g, "%d ", p->data);
            p = p->next;
        }
        fprintf(g, "\n");
    }
}

void FreeIdxList(IdxListType *idxlist) {
	int i=0;
    for (i = 0; i < idxlist->last; i++) {
        free(idxlist->item[i].key);
        ListNode *p = idxlist->item[i].bnolist;
        while (p != NULL) {
            ListNode *temp = p;
            p = p->next;
            free(temp);
        }
    }
}

int main (){
	buf=(char*)malloc(MaxLineLen*sizeof(char));
	if (buf == NULL) {
        perror("内存分配失败");
        return EXIT_FAILURE;
    }

	FILE *f;
	FILE *g;
	if(f=fopen("D:\\C-code\\BookInfo.txt","r")){
		if(g=fopen("D:\\C-code\\BookIdx.txt","w")){
			IdxListType idxlist;
			InitIdxList(&idxlist);
			int BookNo=0;
			while(!feof(f)){
				GetLine(f);
				ExtractKeyWord(&BookNo);
				InsIdxList(&idxlist,BookNo);
				int i=0; 
				for (i = 0; i < wdlist.last; i++) {
                    free(wdlist.item[i]);
                }
                wdlist.last = 0;
			}
			
			PutText(g,&idxlist);
			FreeIdxList(&idxlist);
            fclose(f);
            fclose(g);
            free(buf);
		}
	}
} 
/*测试文件内容 
101 The Art of Programming
102 Data Structures and Algorithms
103 In the Heat of the Night
104 To Kill a Mockingbird
105 The Lord of the Rings
106 Of Mice and Men
107 The Great Gatsby
108 For Whom the Bell Tolls
109 To the Lighthouse
110 It is a Truth Universally Acknowledged*/

