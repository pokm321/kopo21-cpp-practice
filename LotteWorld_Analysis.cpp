// ***** �Ե����� ����м� *****
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *fp;
const char *fileName = "LotteReport.csv";

////////// csv���� �״�� ��� 
void showBasics() {
	char data[20], divide;
	
	fp = fopen(fileName, "r"); // �б��������� csv���� ���� 
	printf("================================ %s ================================\n", fileName);
	while (fscanf(fp, "%[^,\n]%c", &data, &divide) > 0) {
		printf("%-12s", data);
		
		if (divide == '\n') {
			printf("\n");
		}
	}
	printf("\n---------------------------------------------------------------------------------\n\n");
	fclose(fp);
}

////////// �ð��뺰 ������ ���, ���
void reportByTime() {
	int index, time, data[2][7] = {}; // {�ְ�����, �ְ��Ѽ���, �ְ�����, �ְ����, �ְ�û�ҳ�, �ְ�����, �ְ�����},
									   // {�߰�����, �߰��Ѽ���, �߰�����, �߰����, �߰�û�ҳ�, �߰�����, �߰�����} 
	char dayOrNight[10], type[10], age[10], discount[10] ,number[10], price[10];
	
	fp = fopen(fileName, "r"); // �б��������� csv���� ���� 
	printf("================= �ð��� �� �Ǹ���Ȳ =================\n");
	fscanf(fp,"%*s\n"); // ù�� ��ŵ 
	while (fscanf(fp, "%*[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%*s\n", &dayOrNight, &type, &age, &number, &price) > 0) {
		if (strcmp(dayOrNight, "�ְ�") == 0) {
			time = 0; 
		} else if (strcmp(dayOrNight, "�߰�") == 0) {
			time = 1; 
		}
		
		data[time][0] += atoi(price);
		data[time][1] += atoi(number);
		
		if (strcmp(age, "����") == 0) {
			data[time][2] += atoi(number); 
		} else if (strcmp(age, "���") == 0) {
			data[time][3] += atoi(number); 
		} else if (strcmp(age, "û�ҳ�") == 0) {
			data[time][4] += atoi(number); 
		} else if (strcmp(age, "����") == 0) {
			data[time][5] += atoi(number); 
		} else if (strcmp(age, "����") == 0) {
			data[time][6] += atoi(number); 
		} 
	}

	printf("�ְ��� �� %d��\n���� %d��, ��� %d��, û�ҳ� %d��, � %d��, ���� %d��\n�ְ��� ���� : %d��\n\n", data[0][1], data[0][2], data[0][3], data[0][4], data[0][5], data[0][6], data[0][0]);
	printf("�߰��� �� %d��\n���� %d��, ��� %d��, û�ҳ� %d��, � %d��, ���� %d��\n�߰��� ���� : %d��\n", data[1][1], data[1][2], data[1][3], data[1][4], data[1][5], data[1][6], data[1][0]);	
	printf("------------------------------------------------------\n\n");
	fclose(fp);
}

////////// ���ں� ������ ���, ���
void reportByDate() {
	int timeLast, year, month, date, sum;
	char time[10], price[10];
	
	fp = fopen(fileName, "r"); // �б��������� csv���� ���� 
	printf("========== ���� �� �Ǹ���Ȳ ===========\n");
	fscanf(fp,"%*s\n"); // ù�� ��ŵ 
	
	while (fscanf(fp, "%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%*s\n", &time, &price) > 0) {
		if (atoi(time) != timeLast) {
			if (timeLast != 0) {
				printf("%10d��\n", sum);
			}
			date = atoi(time) % 100;
			month = atoi(time) % 10000 / 100;
			year =  atoi(time) / 10000;
			printf("%4d�� %2d�� %2d�� : �� ����", year, month, date);
			sum = atoi(price); // �� ���� ��� 
			timeLast = atoi(time); 
		} else {
			sum += atoi(price);
		}
		
	}
	printf("%10d��\n", sum);
	printf("---------------------------------------\n\n");
	fclose(fp);
}

void reportByDiscount() {
	int sum = 0, numDiscount[6] = {}; //{"����", "�����", "����������", "�ް��庴", "�ӻ��", "���ڳ�"};
	char number[10], discount[10];
	
	fp = fopen(fileName, "r"); // �б��������� csv���� ���� 
	printf("==== ���� �Ǹ���Ȳ =====\n");
	fscanf(fp,"%*s\n"); // ù�� ��ŵ 
	
	while (fscanf(fp, "%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%*[^,],%s\n", &number, &discount) > 0) {
		sum += atoi(number);
		if (strcmp(discount, "����") == 0) {
			numDiscount[0] += atoi(number);
		} else if (strcmp(discount, "�����") == 0) {
			numDiscount[1] += atoi(number);
		} else if (strcmp(discount, "����������") == 0) {
			numDiscount[2] += atoi(number);
		} else if (strcmp(discount, "�ް��庴") == 0) {
			numDiscount[3] += atoi(number);
		} else if (strcmp(discount, "�ӻ��") == 0) {
			numDiscount[4] += atoi(number);
		} else if (strcmp(discount, "���ڳ�") == 0) {
			numDiscount[5] += atoi(number);
		}
	
	
	
	}
	printf("�� �Ǹ� Ƽ�ϼ�  : %4d��\n��� ����       : %4d��\n�����          : %4d��\n����������      : %4d��\n���ڳ�          : %4d��\n�ӻ��          : %4d��\n", sum, numDiscount[0], numDiscount[1], numDiscount[2], numDiscount[3], numDiscount[4], numDiscount[5]);
	
	printf("--------------------------\n");
	fclose(fp);
}


int main() {
	showBasics();
	reportByTime();
	reportByDate(); 
	reportByDiscount();
	return 0;
}
