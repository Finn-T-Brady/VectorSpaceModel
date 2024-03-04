#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "VectorSpace.h"

int main(){
	char *TestStr = "This is a test string, its goal is to test this program. AAAA... \n I hear it's amazing when the famous stuffed purple worm in flap-jaw space, with the tuning fork... does a raw blink off Hara-Kiri rock. I need scissors! 61!";

	char *TestStr2 = "The Purpose of this String is to Test part of this Program,61... Raiden, turn off the game console.";
	       
	VecChunk *Vec_TestStr = StrDecomp(TestStr,2,32);
	VecChunk *Vec_TestStr2 = StrDecomp(TestStr2,1,32);

	printf("Test Vector A:\n");
	VecDump(Vec_TestStr);
	printf("\nTest Vector B:\n");
	VecDump(Vec_TestStr2);
	printf("\n");
	
	int dp = VecDotProduct_unsorted(Vec_TestStr,Vec_TestStr2);
	
	double norm_A,norm_B;
	norm_A=VecNorm(Vec_TestStr);
	norm_B=VecNorm(Vec_TestStr2);

	printf("A,B dot product:%i\n",dp);
	printf("A norm:%lf\nB norm:%lf\n",norm_A,norm_B);

	double cs = VecCosine_unsorted(Vec_TestStr,Vec_TestStr2);
	double scs = VecCosine_unsorted(Vec_TestStr,Vec_TestStr);

	printf("A-B cosine:%lf\nA-A cosine(should be 1):%lf\n",cs,scs);

	
	return 0;
}
