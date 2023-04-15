#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct Node{
    int data;
    struct Node* nextNode;
} Node;

typedef struct LinkedList{
    int curCount; //현재 List에 들어있는 Node의 개수
    Node headNode; //List의 시작 Node
}LinkedList;

typedef struct StackNode{
    int data;
    struct StackNode* next;
}StackNode;

void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void showLinkedStack(StackNode* top);
StackNode* topLinkedStack(StackNode* top);
void deleteLinkedStack(StackNode** top);
int isEmpty(StackNode* top);

int addNode(LinkedList* pList, int pos, int data);
int removeNode(LinkedList* pList, int pos);
void showNode(LinkedList* pList);
// int isEmpty(LinkedList* pList);
int findPos(LinkedList* pList, int data);
void makeEmpty(LinkedList* pList);

void reverseList(LinkedList* linkedList, StackNode** top);

int main(){
    int pos;
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    linkedList->curCount = 0;
    linkedList->headNode.nextNode = NULL;

    StackNode* top = NULL;
    StackNode* pNode;

    //showNode(linkedList);
    addNode(linkedList, 0, 10);
    addNode(linkedList, 5, 100);
    addNode(linkedList, 1, 20);
    addNode(linkedList, 2, 30);
    addNode(linkedList, 1, 50);
    addNode(linkedList, 1, 70);
    addNode(linkedList, 1, 40);

    showNode(linkedList);

    reverseList(linkedList, &top);

    showNode(linkedList);

    // removeNode(linkedList, 1);
    // showNode(linkedList);

    // pos = findPos(linkedList, 30);
    // printf("the location of node with data '30': %d\n", pos);

    makeEmpty(linkedList);
    showNode(linkedList);
    
    return 0;
}

void reverseList(LinkedList* pList, StackNode** top){
    Node *pNode = NULL;
    StackNode *sNode = NULL;

    printf("Reverse Linked List!\n");
    //Stack에 List저장
    pNode = pList->headNode.nextNode;
    while(pNode!=NULL){
        pushLinkedStack(top, pNode->data);
        pNode = pNode->nextNode;
    }

    //List에 Stack 저장
    makeEmpty(pList);
    int i = 0;
    while(*top!=NULL){
        addNode(pList, i++, (*top)->data);
        sNode = popLinkedStack(top);
        free(sNode);
    }
}

void showNode(LinkedList* pList){
    int i=0;
    Node *pNode = NULL;

    if(pList == NULL){
        printf("showNode() error\n");
        return;
    }

    printf("현재 Node 개수 : %d \n", pList->curCount);
    pNode = pList->headNode.nextNode;
    // pNode가 Linked List의 마지막 노드까지 이동하면서 출력
    while(pNode != NULL){
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("----------------------------\n");
}

// int isEmpty(LinkedList* pList){
//     if (pList == NULL){
//         printf("isEmpty() error\n");
//         return -1;
//     }
//     //head 노드가 가리키는 next 노드가 존재하는가
//     if(pList->headNode.nextNode == NULL)
//         return TRUE;
//     else
//         return FALSE;
// }

int findPos(LinkedList* pList, int data){
    int pos = 0;
    Node *pNode = NULL;

    if(pList == NULL){
        printf("findPos() error\n");
        return FALSE;
    }

    pNode = pList->headNode.nextNode;
    //마지막 노드까지 탐색
    while(pNode!=NULL){
        if(pNode->data == data){
            return pos;
        }
        
        pos++;
        pNode = pNode->nextNode;
    }
    return FALSE;
}

void makeEmpty(LinkedList* pList){
    Node* pDummyNode = NULL, *pTmpNode=NULL;
    if(pList!=NULL){
        pTmpNode = pList->headNode.nextNode;
        while(pTmpNode!=NULL){
            pDummyNode = pTmpNode;
            pTmpNode = pTmpNode->nextNode;
            free(pDummyNode);
        }
        pList->headNode.nextNode = NULL;
        pList->curCount = 0;
    }
}

int addNode(LinkedList* pList, int pos, int data){
    int i=0;
    Node* pNewNode = NULL, *pTmpNode = NULL;
    if(pList == NULL){
        printf("addNode() error1\n");
        return FALSE;
    }
    if(pos <0 || pos> pList->curCount){
        printf("addNode() error2: 추가 범위 초과 \n");
        return FALSE;
    }

    pNewNode = (Node*)malloc(sizeof(Node));
    // if(!pNewNode){
    //     printf("addNode() error3 \n");
    //     return FALSE;
    // }

    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    //추가될 위치 직전 노드로 이동
    pTmpNode = &(pList->headNode);
    for(int i=0; i<pos; i++){
        pTmpNode = pTmpNode->nextNode;
    }

    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;
    pList->curCount++;
    return TRUE;
}

int removeNode(LinkedList* pList, int pos){
    int i=0;
    Node* pDelNode = NULL, *pTmpNode = NULL;

    if(pList == NULL){
        printf("removeNode() error1\n");
        return FALSE;
    }

    if(pos<0 || pos>pList->curCount){
        printf("removeNode() error2: 삭제 범위 초과\n");
        return FALSE;
    }

    //삭제될 노드 직전 위치로 이동
    pTmpNode = &(pList->headNode);
    for(i=0; i<pos; i++){
        pTmpNode = pTmpNode->nextNode;
    }

    pDelNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pDelNode->nextNode;
    free(pDelNode);
    pList->curCount--;

    return TRUE;
}

int isEmpty(StackNode* top){
    if (top == NULL)
        return TRUE;
    else
        return FALSE;
}

void showLinkedStack(StackNode* top){
    StackNode *pNode = NULL;
    if(isEmpty(top)){
        printf("The Stack is empty\n");
        return;
    }

    pNode = top;
    printf("============Show Stack===========\n");
    while(pNode != NULL){
        printf("[%d]\n", pNode->data);
        pNode = pNode->next;
    }
    printf("=================================\n");
}

StackNode* topLinkedStack(StackNode* top){
    StackNode *pNode = NULL;
    if(!isEmpty(top))
        pNode=top;

    return pNode;
}

void deleteLinkedStack(StackNode** top){
    StackNode *pNode = NULL, *pDelNode = NULL;
    pNode = *top;

    while(pNode!=NULL){
        pDelNode = pNode;
        pNode = pNode->next;
        free(pDelNode);
    }
    *top = NULL;
}

void pushLinkedStack(StackNode** top, int data){
    StackNode *pNode = NULL;

    //넣을 Stack Node를 할당하고 data값을 저장
    pNode = (StackNode*)malloc(sizeof(StackNode));
    pNode->data = data;
    pNode->next = NULL;

    //만일 Stack이 empty일 경우 바로 top으로 지정
    if(isEmpty(*top)){
        *top = pNode;
    }
    else{
        //넣을 Stack Node의 다음 노드가 현재의 top Node를 가리키고
        //top Node를 넣을 Stack Node로 지정
        pNode->next = *top;
        *top = pNode;
    }
}

StackNode* popLinkedStack(StackNode** top){
    StackNode *pNode = NULL;

    //비어 있는지 검사
    if(isEmpty(*top)){
        printf("The Stack is empty\n");
        return NULL;
    }
    //pNode에 top이 가리키는 노드를 지정하고 top은 그 다음 node로 지정
    pNode = *top;
    *top = (*top)->next;
    return pNode;
}