#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a[50],n,i;
    printf("How many elements?");
    scanf("%d",&n);
    printf("\nEnter array elements:");

    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

    quicksort(a,0,n-1);

    for(i = 0;i < n; i++){
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}


int partition(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }
    }

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }

    return p + lt_n;
}

void quicksort(int * a, int p, int r)
{
    int div;

    if(p < r){
        div = partition(a, p, r);

#pragma omp parallel sections
        {
#pragma omp section
            quicksort(a, p, div - 1);
#pragma omp section
            quicksort(a, div + 1, r);

        }
    }
}

