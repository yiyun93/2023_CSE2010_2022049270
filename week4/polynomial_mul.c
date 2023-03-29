#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#define BUFFSIZE 1024

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct polyTerm {
    int order;
    int coeff;
    struct polyTerm* nextNode;
}polyTerm;


typedef struct poly {
    polyTerm headNode;
} poly;

void clearPoly(poly* A) {
    polyTerm *p = (A->headNode).nextNode;
    polyTerm *temp;
    while(p){
        temp = p;
        p = p->nextNode;
        free(temp);
    }

    //write your code here.
}

void printPoly_impl(poly A, char* buffer) {
    polyTerm *p = (A.headNode).nextNode;
    int i = 0;
    while(p){
        if(i && (p->coeff)>=0) i += sprintf(buffer+i, "+");

        i += sprintf(buffer+i, "%dx^%d", p->coeff, p->order);

        p = p->nextNode;
    }
    //write your code here.
}

void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf("%s", buffer);
}

void addTerm(poly* A, int exp, int coeff) {
    polyTerm *p = &(A->headNode);
    while(p->nextNode){
        p = p->nextNode;
    }
    
    polyTerm* term = (polyTerm*)malloc(sizeof(polyTerm));
    term->coeff = coeff;
    term->order = exp;
    term->nextNode = NULL;

    p->nextNode = term;

    //write your code here.
}

poly multiPoly(poly A, poly B) {
    poly C, temp, temp2;
    C.headNode.nextNode = NULL;
    temp.headNode.nextNode = NULL;
    temp2.headNode.nextNode = NULL;
    polyTerm *a, *b;

    for(polyTerm* A_p = A.headNode.nextNode; A_p; A_p=A_p->nextNode){
        for(polyTerm* B_p = B.headNode.nextNode; B_p; B_p=B_p->nextNode){
            int tempCoeff = (A_p->coeff)*(B_p->coeff);
            int tempOrder = A_p->order + B_p->order;

            if(tempCoeff){
                addTerm(&temp, tempOrder, tempCoeff);
            }
        }
        // a는 temp의 포지션, b는 C의 포지션
        a = temp.headNode.nextNode;
        b = C.headNode.nextNode;
        while(a&&b){
            if(a->order > b->order){
                addTerm(&temp2, a->order, a->coeff);
                a = a->nextNode;
            }
            else if(a->order == b->order){
                if(a->coeff+b->coeff) addTerm(&temp2, a->order, a->coeff+b->coeff);
                a = a->nextNode;
                b = b->nextNode;
            }
            else if(a->order < b->order){
                addTerm(&temp2, b->order, b->coeff);
                b= b->nextNode;
            }
        }
        for(;a;a=a->nextNode) addTerm(&temp2, a->order, a->coeff);
        for(;b;b=b->nextNode) addTerm(&temp2, b->order, b->coeff);

        clearPoly(&temp);
        temp = C;
        C.headNode.nextNode = temp2.headNode.nextNode;
        clearPoly(&temp);
        temp2.headNode.nextNode = NULL;
    }



    return C;
}

int main() {
	poly A, B;
    A.headNode.nextNode = NULL;
    B.headNode.nextNode = NULL;

    addTerm(&A, 1, 1);
    addTerm(&A, 0, 1);
    printf("poly A: ");
    printPoly(A);
    printf("\n");

    addTerm(&B, 1, 1);
    addTerm(&B, 0, -1);
    printf("poly B: ");
    printPoly(B);
    printf("\n");

    printf("A*B: ");
    printPoly(multiPoly(A, B));

	return 0;
}
