#include <stdio.h>
#include <stdlib.h>



int main() {


    // section I : initialize matrix, do not modifie this section 
	int n;
	scanf("%d", &n);

	int **arrayA;
    int **arrayB;
    int **result;

	arrayA = malloc(n * sizeof(int *));
    arrayB = malloc(n * sizeof(int *));
    result = malloc(n * sizeof(int *));
    
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
            scanf("%d", &arrayB[i][j]);
        }
    }

    // end of section I : initialize matrix, do not modifie this section 




    // section II : matrix multiplication modifie this section 
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            for (k = 0; k < n; ++k) {
                result[i][j] += arrayA[i][k] * arrayB[k][j];
            }
        }
    }

    // end of section II : matrix multiplication modifie this section 


    //Section III : Visualize 
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%d  ", result[i][j]);
            if (j == n - 1)
                printf("\n");
        }
    }

    // To print the matrix uncomment this section. 

    return 0;

}