#include <stdlib.h>
#include <string.h>
#include <math.h>


//I couldn't be bothered to write it like this
//I was gonna have all the algorithms allow for the user to define their own VSM_VecChunk_MAX
#undef VSM_VecChunk_MAX
//#ifndef VSM_VecChunk_MAX
#define VSM_VecChunk_MAX 8
//#endif

#ifndef VSM_VecSpace_DELIMLIST
#define VSM_VecSpace_DELIMLIST(a) (a==' ' ||  a==',' || a== '.' || a=='!' || a=='?' || a=='\n')
#endif

#ifndef VSM_VECSPACE_INC
#define VSM_VECSPACE_INC

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
		itr->items=calloc(sizeof(VecKey),VSM_VecChunk_MAX);
		itr->next=calloc(sizeof(VecChunk),1);
		itr=itr->next;
	}
	itr->items=calloc(sizeof(VecKey),VSM_VecChunk_MAX);
	return Head;
}
void VecDelSingle(VecChunk* A){
	free(A->items);
	free(A);
}
int VecDelFull(VecChunk* Head){
	VecChunk* A;
	int n=0;
	while(Head){
		n++;
		free(Head->items);
		A=Head;
		Head=Head->next;
		free(A);
	}
	return n;
}

void VecDump(VecChunk *Head){
	int n;
	while(Head){
		printf("%i-",Head->n);
		n=VSM_VecChunk_MAX;
		while(n--){
			printf("(%i,%s), ",Head->items[n].n,Head->items[n].key);
		}
		printf("\n");
		Head=Head->next;
	}
}

int VecKeyBubble(VecKey* Arr,int n){
	if(n<2)return 0;
	int m;
	VecKey temp;
	while(--n){
		m=0;
		while(m<n){
			if(strcmp(Arr[m].key,Arr[m+1].key)>0){
				temp = Arr[m+1];
				Arr[m+1]=Arr[m];
				Arr[m]=temp;
			}
			m+=1;
		}
	}
	return 0;
}

void VecMergeSort_a(VecChunk* A,VecChunk* B, int n,int max);

int VecMergeSort(VecChunk* Head){
	VecChunk* itr;
	itr = Head;

	int n,m;
	int blockCount = 0;
	VecKey* itrArr;
	VecKey* buffer;
	while(itr->next){
		itrArr=itr->items;
		
		VecKeyBubble(itrArr,4);
		VecKeyBubble(&(itrArr[4]),4);

		buffer = (VecKey*)malloc(8*sizeof(VecKey));
		
		n=0;
		m=0;
		
		while(n<4 && m<4){
			if(strcmp(itrArr[n].key,itrArr[4+m].key)>0){
				buffer[n+m]=itrArr[4+m];
				m++;
			}else{
				buffer[n+m]=itrArr[n];
				n++;
			}
		}
		while(n<4){
			buffer[n+m]=itrArr[n];
			n++;
		}
		while(m<4){
			buffer[n+m]=itrArr[4+m];
			m++;
		}

		free(itr->items);
		itr->items=buffer;

		blockCount+=1;
		itr=itr->next;
	}
	
	itrArr=itr->items;
	n=0;
	m=0;
	
	buffer = calloc(8,sizeof(VecKey));
	
	VecKeyBubble(itrArr,itr->n/2);
	VecKeyBubble(&(itrArr[itr->n/2]),itr->n - itr->n/2);
	
	while(n<(itr->n/2) && m<(itr->n - itr->n/2)){
		if(strcmp(itrArr[n].key,itrArr[m+itr->n/2].key)>0){
			buffer[n+m]=itrArr[m+itr->n/2];
			m++;
		}else{
			buffer[n+m]=itrArr[n];
			n++;
		}
	}
	while(n<(itr->n/2)){
		buffer[n+m]=itrArr[n];
		n++;
	}
	while(m<(itr->n - itr->n/2)){
		buffer[n+m]=itrArr[m+itr->n/2];
		m++;
	}
	
	free(itr->items);
	itr->items=buffer;

	blockCount+=1;

	n=1;
	itr=Head->next;
	while(2*n <= blockCount){
		VecMergeSort_a(Head,itr,n,blockCount);
		itr=itr->next;
		n++;
	}
	
	return 0;
}

void VecMergeSort_a(VecChunk* A,VecChunk* B, int n,int max){
	VecChunk *itrA, *itrB;
VecMerge_restart:
	itrA=A;
	itrB=B;

	int j=2*n;
	if(j>max)j=max;
	VecKey** buffers = calloc(j,sizeof(VecKey*));
	while(j--){
		buffers[j]=calloc(8,sizeof(VecKey));
	}
	j=2*n;
	if(j>max)j=max;
	
	int nA,nB;
	nA=nB=0;
	while(itrA!=B && (nB%8)<itrB->n && nB<8*(j-n)){
		if(strcmp(itrA->items[nA%8].key,itrB->items[nB%8].key)<0){
			buffers[(nA+nB)/8][(nA+nB)%8]=itrA->items[nA%8];
			nA++;
			if(nA%8==0)itrA=itrA->next;
		}else{
			buffers[(nA+nB)/8][(nA+nB)%8]=itrB->items[nB%8];
			nB++;
			if(nB%8==0)itrB=itrB->next;
		}
	}
	while(itrA!=B){
		buffers[(nA+nB)/8][(nA+nB)%8]=itrA->items[nA%8];
		nA++;
		if(nA%8==0)itrA=itrA->next;
	}
	while((nB%8)<itrB->n && nB<8*(j-n)){
		buffers[(nA+nB)/8][(nA+nB)%8]=itrB->items[nB%8];
		nB++;
		if(nB%8==0)itrB=itrB->next;
	}
	nA=0;
	itrA=A;
	while(nA<j){
		free(itrA->items);
		itrA->items=buffers[nA];
		nA++;
		itrA=itrA->next;
	}

	if((max-=j)>0){
		while(j--){
			A=A->next;
			B=B->next;
		}
		goto VecMerge_restart;
	}
}

VecChunk* StrDecomp(char* in,int bufferSize){
	char* buffer = calloc(sizeof(char),bufferSize);
	char* bufferP;

	VecChunk* Head = VecInit(1);
	VecChunk* VecItr;
	int n;
	int p;
	while(*in && VSM_VecSpace_DELIMLIST(*in)){
		in++;
	}
	while(*in){
		bufferP=buffer;
		while(*in && !VSM_VecSpace_DELIMLIST(*in)){
			*bufferP=(*in+32*(*in>='A' && *in<='Z'));
			bufferP++;
			in++;
		}
		*bufferP=0;
		VecItr=Head;
		while(1){
			n=0;
			p=0;
			while(n<VSM_VecChunk_MAX){
				if(VecItr->items[n].key==0){
					VecItr->items[n].key=(char*)calloc(1,bufferP-buffer+1);
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
				VecItr->next=VecInit(1);
			}
			VecItr=VecItr->next;
		}
StrDecompLoopEnd:
		while(*in && VSM_VecSpace_DELIMLIST(*in)){
			in++;
		}
	}
	return Head;
}

double VecNorm(VecChunk* head){
	int squareSum = 0;
	int n;
	while(head){
		n=VSM_VecChunk_MAX;
		while(n--){
			squareSum += head->items[n].n * head->items[n].n;
		}
		head=head->next;
	}
	double norm = sqrt(squareSum);
	return norm;
}

int VecDotProduct(VecChunk* A,VecChunk* B){
	int result = 0;
	int n,m;
	int j;
	n=0;
	m=0;
	while(A){
		while((j=strcmp(A->items[n].key,B->items[m].key))>0){
			m++;
			if(m==B->n){
				m=0;
				B=B->next;
				if(B==0)goto VecDotProd_endLoop;
			}
		}
		if(j==0)result+=A->items[n].n * B->items[m].n;
		n++;
		if(n==A->n){
			n=0;
			A=A->next;
		}
	}
VecDotProd_endLoop:
	return result;
}

//shouldn't use: O(n^2) performance
int VecDotProduct_unsorted(VecChunk* A, VecChunk* B){
	VecChunk* itrB = B;
	int result = 0;
	int n, m;
	char *a, *b;
	while(A){
		n=0;
		while(n<VSM_VecChunk_MAX && A->items[n].key){
			a=A->items[n].key;
			itrB=B;
			while(itrB){
				m=0;
				while(m<VSM_VecChunk_MAX && itrB->items[m].key){
					b=itrB->items[m].key;
					if(strcmp(a,b)==0){
						result+= A->items[n].n * itrB->items[m].n;
						goto VecDotProd_unsorted_escPoint;
					}
					m++;
				}
				itrB=itrB->next;
			}
			VecDotProd_unsorted_escPoint:n++;
		}
		A=A->next;
	}
	return result;
}

double VecCosine(VecChunk* A, VecChunk* B){
	int DotProd = VecDotProduct(A,B);
	double normA,normB;
	normA=VecNorm(A);
	normB=VecNorm(B);

	double result = DotProd/(normA*normB);
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
