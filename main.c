#include <stdio.h>
#include <stdlib.h>

#ifndef VecChunk_MAX
#define VecChunk_MAX 8
#endif

typedef struct List_0{
	void* X;
	struct List_0* next;
} List;

List** NewNCyc(int n){
	List* Head = calloc(n,sizeof(List));
	int x = n-1;
	while(x--){
		Head[n].next=&Head[n+1];
	}
	Head[n-1].next=Head;
	return &Head;
}
typedef struct VecChunk_1 VecKey;
typedef struct VecChunk_0{
	int n;
	VecKey* items;
	struct VecChunk_0* next;
} VecChunk;

struct VecChunk_1{
	char* key;
	int n;
};

VecChunk StrDecomp(char* in){
	//
	//
}

int main(){
	char *a = "This is a test string, its goal is to test this program";

	VecChunk J;
	J.items=calloc(sizeof(VecKey),8);
	J.items[4].key="aaa";
	J.items[4].n=1;

	return 0;
}
