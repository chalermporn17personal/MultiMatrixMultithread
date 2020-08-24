#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct parameter{
    int start;
    int end;
    int n;
    int **A;
    int **B;
    int **Result;
};

void getInput(int ***arrA , int ***arrB , int*** res , int *N)
{
    int n;
    scanf("%d", &n);
    int** arrayA ;
    int** arrayB ;
    int** result ;
    *N = n;
    arrayA = malloc(n * sizeof(int *));
    arrayB = malloc(n * sizeof(int *));
    result = malloc(n * sizeof(int *));

    *arrA = arrayA;
    *arrB = arrayB;
    *res = result;
    int i,j,k;
	if(arrayA == NULL || arrayB == NULL || result == NULL) {
		printf("Out of memory\n");
		exit(1);
	}
	for(i = 0; i < n; i++) {
		arrayA[i] = malloc(n * sizeof(int));
        arrayB[i] = malloc(n * sizeof(int));
        result[i] = malloc(n * sizeof(int));
		if(arrayA[i] == NULL) {
			printf("Out of memory\n");
			exit(1);
		}
	}
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            result[i][j] = 0;
        }
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &arrayA[i][j]);
        }
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &arrayB[j][i]);
        }
    }
}

void *Multiply(void* p_param)
{
    struct parameter * s2;
    s2 = (struct parameter *)(p_param);
    int i,j,k;
    int sum = 0;
    int end = s2 -> end;
    int start = s2 -> start;
    int n = s2 -> n;
    //printf("%d to %d \n",start,end);
    for( i = start ; i < end ; i = i + 1)
    {
        for( j = 0 ; j < n ; j++)
        {   
            sum = 0;
            for( k = 0 ; k < n ; k++)
            {
                sum = sum + s2->A[i][k] * s2->B[j][k];
            }
            s2 -> Result[i][j] = sum;
        }
    }

}

void printarr(int** arr , int n)
{
    int i,j;
    for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
        printf("%d  ", arr[i][j]);
        if (j == n - 1) printf("\n");
        }
    }
}
int main(int argc,char* argv[]) {
    int max_thread = atoi(argv[1]);
    fflush(stdin);
    int **arrayA;
    int **arrayB;
    int **result;
    int n = 0;
    pthread_t threads[max_thread];
    int i,j,thread_num = 0;
    //printf("Runing %d thread(s)\n",max_thread);
    //Get input
    getInput(&arrayA , &arrayB , &result ,  &n);
    //Declare Array of parameter to be input of a thread
    struct parameter param[max_thread];
    struct parameter *param_address[max_thread];  
    // create thread
    if( max_thread >= n)
    {
        max_thread = n;
    }
    int rpt = n / max_thread; // rows per thread
    for(thread_num = 0 ; thread_num < max_thread ; thread_num++)
    {
        param[thread_num].start = thread_num * rpt;
        if(thread_num == max_thread - 1)
            param[thread_num].end = n;
        else
            param[thread_num].end = thread_num * rpt + rpt;
        param[thread_num].n = n;
        param[thread_num].A = arrayA;
        param[thread_num].B = arrayB;
        param[thread_num].Result = result;
        param_address[thread_num] = &param[thread_num];
        pthread_create(&threads[thread_num], NULL, Multiply, param_address[thread_num]);
    }
    for(thread_num = 0 ; thread_num < max_thread ; thread_num++)
    {
        pthread_join(threads[thread_num], NULL);
    }
    printarr(result,n);
    pthread_exit(NULL);
    return 0;
}