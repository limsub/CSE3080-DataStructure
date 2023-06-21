#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_STRING_SIZE 1000000
#define MAX_PATTERN_SIZE 3000

int failure[MAX_PATTERN_SIZE];
char str[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int ans_arr[MAX_STRING_SIZE];


int *pmatch(char*, char*);
void fail(char*);

int  main()
{
	// ���� ����
	FILE* fp_r1, * fp_r2, * fp_w;

	fp_r1 = fopen("string.txt", "r");
	fp_r2 = fopen("pattern.txt", "r");
	fp_w = fopen("result_kmp.txt", "w");

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
	fgets(str, MAX_STRING_SIZE, fp_r1);
	fgets(pat, MAX_PATTERN_SIZE, fp_r2);

	// fail �Լ� ����
	fail(pat);

	// pat�� str�� �� �� �ִ��� ã��
	int i = 0, j = 0;
	int lens = strlen(str);
	int lenp = strlen(pat);
	int cnt = 0;

	while (i < lens && j < lenp) {
		if (str[i] == pat[j]) {
			i++;
			j++;
		}
		else if (j == 0)
			i++;
		else j = failure[j - 1] + 1;

		if (j == lenp) {
			ans_arr[cnt] = (i - lenp);
			cnt++;
			j = failure[j - 1] + 1;
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
		return 0;
	}
}

void fail(char* pat)
{
	int i, j, n = strlen(pat);
	failure[0] = -1;

	for (j = 1; j < n; j++)
	{
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}

