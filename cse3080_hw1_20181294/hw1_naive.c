#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_s 10000000
#define MAX_p 3000
char str[MAX_s];
char pat[MAX_p];
int ans_arr[MAX_s];


int main()
{
	// ���� ����
	FILE* fp_r1, * fp_r2, * fp_w;

	fp_r1 = fopen("string.txt", "r");
	fp_r2 = fopen("pattern.txt", "r");
	fp_w = fopen("result_naive.txt", "w");

	if ((fp_r1 == NULL) || (fp_r2 == NULL)){
		printf("Both string file and pattern file don't exist\n");
		return 0;
	}
	else if (fp_r1 == NULL){
		printf("The string file does not exist\n");
		return 0;
	}
	else if (fp_r2 == NULL){
		printf("The pattern file does not exist\n");
		return 0;
	}

	if (fp_w == NULL) {
		printf("file open error\n");
		return 0;
	}
	
	// ��ǲ ���Ͽ��� �� ���ڿ� �б�
	fgets(str, MAX_s, fp_r1);
	fgets(pat, MAX_p, fp_r2);


	// pat�� str�� �� �� �ִ��� ã��
	int i = 0;
	int j = 0;
	int start = 0;
	int cnt = 0;

	int lasts = strlen(str) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (start = 0; endmatch <= lasts; endmatch++, start++) {
		if (str[endmatch] == pat[lastp])
			for (j = 0, i = start; (j < lastp) && (str[i] == pat[j]); i++, j++)
				;
		if (j == lastp) {
			ans_arr[cnt] = start;
			cnt++;
			j = 0;
		}
	}
	ans_arr[cnt] = -1;

	// �ƿ�ǲ ���Ͽ� ��� ����
	fprintf(fp_w, "%d\n", cnt);

	int t = 0;
	while (ans_arr[t] != -1) {
		fprintf(fp_w, "%d ", ans_arr[t]);
		t++;
	}


	// ���� �ݱ�
	int s1, s2;
	s1 = fclose(fp_r1);
	s2 = fclose(fp_r2);
	if ((s1 != 0) || (s2 != 0)) {
		printf("file close error\n");
		return 0;
	}

	int s;
	s = fclose(fp_w);
	if (s != 0) {
		printf("file close error\n");
		return 1;
	}
}
