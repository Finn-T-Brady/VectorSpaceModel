#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "VectorSpace.h"

int main(){
	char *TestStr = "Hello, my name is Joel, I work in Computer Science, I program mainly in Haskell, I specialise in researching hardware development. I Have published several papers regarding types of hardware, weather they are commonly used or not.";

	char *TestStr2 = "Greetings, I am Joey, I am working in Biology, I am branching out in to wetware research, wetware is when biological life is used in computer hardware. I believe that fungal wetware is an amazing development in computer hardware";
	

	VecChunk *Vec_TestStr = StrDecomp(TestStr,32);
	VecChunk *Vec_TestStr2 = StrDecomp(TestStr2,32);

	VecMergeSort(Vec_TestStr);
	VecMergeSort(Vec_TestStr2);
	

	printf("Test Vector A:\n");
	VecDump(Vec_TestStr);
	printf("\nTest Vector B:\n");
	VecDump(Vec_TestStr2);
	printf("\n");
		
	int dp = VecDotProduct(Vec_TestStr,Vec_TestStr2);

	double norm_A,norm_B;
	norm_A=VecNorm(Vec_TestStr);
	norm_B=VecNorm(Vec_TestStr2);

	printf("A,B dot product:%i\n",dp);
	printf("A norm:%lf\nB norm:%lf\n",norm_A,norm_B);

	double cs = VecCosine(Vec_TestStr,Vec_TestStr2);
	double scs = VecCosine(Vec_TestStr,Vec_TestStr);

	printf("A-B cosine:%lf\nA-A cosine(should be 1):%lf\n",cs,scs);
	
	return 0;
}
