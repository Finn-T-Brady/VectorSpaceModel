#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef VecChunk_MAX
#define VecChunk_MAX 8
#endif

#ifndef VecSpace_DELIMLIST
#define VecSpace_DELIMLIST(a) (a==' ' ||  a==',' || a=='.' || a=='!' || a=='?' || a=='\n')
#endif

#ifndef VECCHUNK_INC
#define VECCHUNK_INC

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

VecChunk* VecInit(int blocks){
	VecChunk* Head = calloc(sizeof(VecChunk),1);
	VecChunk* itr;
	itr=Head;
	while(--blocks){
		itr->items=calloc(sizeof(VecKey),VecChunk_MAX);
		itr->next=calloc(sizeof(VecChunk),1);
		itr=itr->next;
	}
	itr->items=calloc(sizeof(VecKey),VecChunk_MAX);
	return Head;
}

void VecDump(VecChunk *Head){
	int n;
	while(Head){
		printf("%i-",Head->n);
		n=VecChunk_MAX;
		while(n--){
			printf("(%i,%s), ",Head->items[n].n,Head->items[n].key);
		}
		printf("%\n");
		Head=Head->next;
	}
}


int VecMergeSort(VecChunk* Head){
	VecChunk* itr;
	itr = Head;

	int n;
	char g;
	int blockCount = 0;
	VecKey* buffer = calloc(sizeof(VecKey),VecChunk_MAX);
	while(itr->next){
		n=4;
		while(n--){
			g = strcmp(itr->items[2*n].key,itr->items[2*n+1].key)>0;
			buffer[2*n]=itr->items[2*n+g];
			buffer[2*n+1]=itr->items[2*n+1-g];
		}
		n=2;
		while(n--){
			//
		}
		//
		//
		blockCount+=1;
		itr=itr->next;
	}
	//
	return 0;
}

VecChunk* StrDecomp(char* in,int blockSize,int bufferSize){
	char* buffer = calloc(sizeof(char),bufferSize);
	char* bufferP;

	VecChunk* Head = VecInit(blockSize);
	VecChunk* VecItr;
	int n;
	int p;
	
	while(*in){
		bufferP=buffer;
		while(*in && !VecSpace_DELIMLIST(*in)){
			*bufferP=(*in+32*(*in>='A' && *in<='Z'));
			bufferP++;
			in++;
		}
		*bufferP=0;
		VecItr=Head;
		while(1){
			n=0;
			p=0;
			while(n<VecChunk_MAX){
				if(VecItr->items[n].key==0){
					VecItr->items[n].key=(char*)calloc(1,bufferP-buffer);
					VecItr->n+=1;
					do{
						VecItr->items[n].key[p]=buffer[p];
					}while(buffer[p++]);
					VecItr->items[n].n=1;
					goto StrDecompLoopEnd;
				}
				if(strcmp(buffer,VecItr->items[n].key)==0){
					VecItr->items[n].n+=1;
					goto StrDecompLoopEnd;
				}
				n++;
			}
			if(VecItr->next==0){
				VecItr->next=VecInit(blockSize);
			}
			VecItr=VecItr->next;
		}
StrDecompLoopEnd:
		while(*in && VecSpace_DELIMLIST(*in)){
			in++;
		}
	}
	return Head;
}

double VecNorm(VecChunk* head){
	int squareSum = 0;
	int n;
	while(head){
		n=VecChunk_MAX;
		while(n--){
			squareSum += head->items[n].n * head->items[n].n;
		}
		head=head->next;
	}
	double norm = sqrt(squareSum);
	return norm;
}


//shouldn't use: O(n^2) performance
int VecDotProduct_unsorted(VecChunk* A, VecChunk* B){
	VecChunk* itrB = B;
	int result = 0;
	int n, m;
	char *a, *b;
	while(A){
		n=0;
		while(n<VecChunk_MAX && A->items[n].key){
			a=A->items[n].key;
			itrB=B;
			while(itrB){
				m=0;
				while(m<VecChunk_MAX && B->items[m].key){
					b=itrB->items[m].key;
					if(strcmp(a,b)==0){
						result+= A->items[n].n * itrB->items[m].n;
						goto DotProd_unsorted_escPoint;
					}
					m++;
				}
				itrB=itrB->next;
			}
			DotProd_unsorted_escPoint:n++;
		}
		A=A->next;
	}
	return result;
}

double VecCosine_unsorted(VecChunk *A, VecChunk *B){
	int DotProd = VecDotProduct_unsorted(A,B);
	double normA,normB;
	normA = VecNorm(A);
	normB = VecNorm(B);

	double result = DotProd/(normA*normB);
	return result;
}


#endif
