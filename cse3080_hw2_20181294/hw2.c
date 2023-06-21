#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENTS 1000001

// heap 생성
typedef struct {
    int key;
}element;
element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
element copy_max[MAX_ELEMENTS];
element copy_min[MAX_ELEMENTS];
int n1 = 0;
int n2 = 0;

// 함수 생성
void insert_max_heap(element item);
void insert_min_heap(element item);
void copy_heap(element *h1, element *h2);
void sort_max(element *h);
void sort_min(element *h);


int main(int argc, char **argv) {

    double start, end;
    start = (double)clock() / CLOCKS_PER_SEC;

    if (argc != 2) {
        printf("usage : ./hw2 input_filename\n");
        return 0;
    }

    // 파일 오픈
    FILE* fp_r;
    fp_r = fopen(argv[1], "r");
    if (fp_r == NULL) {
        printf("The input file does not exist\n");
        return 0;
    }
    
    FILE* fp_w;
    fp_w = fopen("hw2_result.txt", "w");
    if (fp_w == NULL) {
        printf("Result_file open error\n");
        return 0;
    }
    
    //파일에서 읽고 시작
    char s[10];
    int k;
    element item;

    while(1) {
        fscanf(fp_r, "%s %d", s, &k);
        int i;

        // INSERT
        if ( (s[0] == 'I') && (k) ) {
            item.key = k;
            insert_max_heap(item);
            insert_min_heap(item);
        }
        
        // ASCEND
        else if (s[0] == 'A') {
            //copy
            copy_heap(min_heap, copy_min);
            //print
            sort_min(min_heap);
            for (i = 1; i<n2+1; i++ ) {
                fprintf(fp_w, "%d ", min_heap[i].key);
            }
            fprintf(fp_w, "\n");
            copy_heap(copy_min, min_heap);
        }

        //DESCEND
        else if (s[0] == 'D') {
            //copy
            copy_heap(max_heap, copy_max);
            //print
            sort_max(max_heap);
            for (i = 1; i< n1+1 ; i++) {
                fprintf(fp_w, "%d ", max_heap[i].key);
            }
            fprintf(fp_w, "\n");
            copy_heap(copy_max, max_heap);
        }

        if (feof(fp_r))
            break;
    }


    int s1, s2;
    s1 = fclose(fp_r);
    s2 = fclose(fp_w);
    if ( (s1 != 0) || (s2 != 0) ) {
        printf("file close error\n");
        return 0;
    }

    end = (double)clock()/CLOCKS_PER_SEC;
    printf("output written to hw2_result.txt\n");
    printf("running time : %lf seconds\n", end - start);

}



void insert_max_heap(element item) {

    int i;
    if (n1 == MAX_ELEMENTS - 1) {
        printf("the heap is full.\n");
        exit(1);
    }
    n1 = n1+1;
    i = n1;
    while ( (i != 1) && (item.key > max_heap[i/2].key) ) {
        max_heap[i] = max_heap[i/2];
        i /= 2;
    }
    max_heap[i] = item;
}



void insert_min_heap(element item) {
    int i;
    if (n2 == MAX_ELEMENTS - 1) {
        printf("the heap is full\n");
        exit(1);
    }
    n2 = n2+1;
    i = n2;
    while ( (i != 1) && (item.key < min_heap[i/2].key) ) {
        min_heap[i] = min_heap[i/2];
        i /= 2;
    }
    min_heap[i] = item;
}

void copy_heap(element *h1, element *h2) {
    int i;
    for (i = 0; i< MAX_ELEMENTS; i++ ) {
        h2[i] = h1[i];
    }
}



void sort_max(element *h) {
    int i, j, temp;
    int k = n1+1;

    for (i = 1; i < k-1 ; i++ ) {
        for (j = 1; j< k-1 ; j++) {
            if (h[j].key < h[j+1].key) {
                temp = h[j].key;
                h[j].key = h[j+1].key;
                h[j+1].key = temp;
            }
        }
    }
}

void sort_min(element *h) {
    int i, j, temp;
    int k = n2+1;

    for (i = 1; i < k; i++ ) {
        for (j = 1; j < k-1; j++) {
            if (h[j].key > h[j+1].key) {
                temp = h[j].key;
                h[j].key = h[j+1].key;
                h[j+1].key = temp;
            }
        }
    }
}

