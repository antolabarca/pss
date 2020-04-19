#include <stdio.h>
#include <stdlib.h>

void rotar(int A[], int n) {
	int a1= A[n-1];
	for (int i = n-1; i > 1; --i) {
		A[i]=A[i-1];
	}
	A[1]=a1;
}

int main(int argc, char *argv[]) {
	int n= atoi(argv[1]);
	int A[n];
	for (int i = 0; i < n; ++i) {
		A[i]=i+1;
	}
	for (int i = 0; i < n-1; ++i) {
		int semana=i+1;
    	printf("semana %d:",semana);
		for (int j = 0; j < n/2; ++j) {
    		printf(" %d-%i",A[j],A[n-(j+1)]);
    	}
    	printf("\n");
		rotar(A,n);
	}
	return 0;
}