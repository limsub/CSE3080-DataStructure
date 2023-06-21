#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct{
    int s;
    int e;
    int w;
} element;

int *parent;
element *E;
element *T;
int n = 0;

// Required functions
int collapsingFind(int i);
void weightedUnion(int i, int j);
void insert_min_heap(element item, int q);
element delete_min_heap();


// argc,  설정하기.
int main(int argc, char **argv) {

    // Check start time
    double start, end;
    start = (double)clock() / CLOCKS_PER_SEC;

    
    // Open file
    if (argc != 2) {
        printf("usage : ./hw3 input_filename\n");
        return 0;
    }

    FILE *fp_r;
    fp_r = fopen(argv[1], "r");
    if (fp_r == NULL) {
        printf("The input file does not exist\n");
        return 0;
    }
    FILE *fp_w;
    fp_w = fopen("hw3_result.txt", "w");
    if (fp_w == NULL) {
        printf("Result file open error\n");
        return 0;
    }
    

    // Read input file
    int p, q, i;
    fscanf(fp_r, "%d", &p);
    fscanf(fp_r, "%d", &q);

    parent = (int*)malloc(p * sizeof(int));
    for (i = 0; i< p; i++) parent[i] = -1;
    E = (element*)malloc((q+1) * sizeof(element));
    T = (element*)malloc( (p) * sizeof(element));

    while(1) {
        element k;
        fscanf(fp_r, "%d %d %d", &(k.s), &(k.e), &(k.w));
        insert_min_heap(k, q+1);

        if (feof(fp_r))
            break;
    }

    int k = 0;
    int sum = 0;
    while ( (k < p - 1) && (n != 0) ) {
        
        element add_to_T = delete_min_heap();
        if  ( collapsingFind(add_to_T.s) != collapsingFind(add_to_T.e) ) {
            weightedUnion(collapsingFind(add_to_T.s), collapsingFind(add_to_T.e));
            T[k] = add_to_T;
            sum += add_to_T.w;
            k++;
        }
    }

    // Start printing
    // Spanning Tree
    for (int j = 0; j<p-1; j++) {
        fprintf(fp_w, "%d %d %d \n", T[j].s, T[j].e, T[j].w);
    }

    // Sum of weight
    fprintf(fp_w, "%d\n", sum);

    // Whether connected or disconnected
    if (k == p-1) {
        fprintf(fp_w, "CONNECTED\n");
    }
    else {
        fprintf(fp_w, "DISCONNECTED\n");
    }

    
    // Done
    int s1, s2;
    s1 = fclose(fp_r);
    s2 = fclose(fp_w);
    if ( (s1 != 0 ) || (s2 != 0) ) {
        printf("File close error\n");
        return 0;
    }

    free(parent);
    free(E);
    free(T);

    end = (double)clock() / CLOCKS_PER_SEC;

    printf("output written to hw3_result.txt\n");
    printf("running time : %lf seconds\n", end - start);
}

int collapsingFind(int i) {
    int r, t, l;
    for (r = i; parent[r]>= 0; r = parent[r])
        ;
    for (t = i; t != r; t = l) {
        l = parent[t];
        parent[t] = r;
    }
    return r;
}

void weightedUnion(int i, int j) {

    int tmp = parent[i] + parent[j];
    if (parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = tmp;
    }
    else {
        parent[j] = i;
        parent[i] = tmp;
    }
}

void insert_min_heap(element item, int q) {
    int i;
    if (n == q) {
        printf("the heap is full\n");
        exit(1);
    }
    n = n+1;
    i = n;
    while ( (i != 1) && (item.w < E[i/2].w) ) {
        E[i] = E[i/2];
        i /= 2;
    }
    E[i] = item;
}

element delete_min_heap() {

    int parent, child;
    element item, temp;

    if (n == 0) {
        printf("the heap is empty\n");
        // the edges are done 이런 식으로 바꿔야 하지 않을까
        exit(1);
    }

    item = E[1];
    temp = E[n];
    n--;

    parent = 1;
    child = 2;

    while (child <= n) {
        if ( (child <n ) && (E[child].w > E[child+1].w) ) child++;
        if (temp.w <= E[child].w) break;
        E[parent] = E[child];
        parent = child;
        child *= 2;
    }

    E[parent] = temp;

    return item;
}


