#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
//���峣�� 
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
	int data;  //��������Ԫ�ؽṹ 
	struct ListkNode *next;
}ListNode,*LinkList;

typedef struct { 
	int last;     //����ʱ��� 
	char *item[MaxWordNum];  //�����ַ�������
}WordListType; 


typedef struct {
	char *key;
	LinkList bnolist;
}IdxTermType;//����������Ԫ�� 

typedef struct {
	IdxTermType item[MaxKeyNum+1];
	int last; 
}IdxListType;//������������������ 

   char *buf;  //������Ŀ������ 
   WordListType wdlist;  //����ʱ�


//����
void InitIdxList(IdxListType *idxlist);
	//��ʼ����������������idxlistΪ�ձ�����idxlist->item[0]��һ�մ� 

void GetLine(FILE *f);
	//���ļ�f����һ����Ŀ��Ϣ����Ŀ��������buf  
 
int ExtractKeyWord(int *bno);
	//��Buf����ȡ�����ؼ��ʵ��ʱ�wdlist,��Ŵ���bno�� 

int InsIdxList(IdxListType *idxlist,int bno);
	//�����Ϊbno�������ؼ��ʰ��ʵ�˳����� ������idxlist
	
void putText(FILE *g,IdxListType idxlist);
//�����ɵ�������idxlist������ļ�g��

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
	// ����buf��ʽΪ "��� ԭʼ����"
	char *token=strtok(buf," ");
	if (token == NULL) return ERROR;
	*bno=atoi(token);//��ȡ���
	
	//��ȡʣ�ಿ��
	token=strtok(NULL,"\n");
	if(token==NULL) return ERROR;
	
	//�ָ�����
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
        fprintf(g, "�ؼ���: %s\n����б�: ", idxlist->item[i].key);
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
        perror("�ڴ����ʧ��");
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
/*�����ļ����� 
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

