// ***** 롯데월드 매출분석 *****
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *fp;
const char *fileName = "LotteReport.csv";

////////// csv내용 그대로 출력 
void showBasics() {
	char data[20], divide;
	
	fp = fopen(fileName, "r"); // 읽기전용으로 csv파일 열기 
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

////////// 시간대별 데이터 계산, 출력
void reportByTime() {
	int index, time, data[2][7] = {}; // {주간매출, 주간총수량, 주간유아, 주간어린이, 주간청소년, 주간성인, 주간노인},
									   // {야간매출, 야간총수량, 야간유아, 야간어린이, 야간청소년, 야간성인, 야간노인} 
	char dayOrNight[10], type[10], age[10], discount[10] ,number[10], price[10];
	
	fp = fopen(fileName, "r"); // 읽기전용으로 csv파일 열기 
	printf("================= 시간대 별 판매현황 =================\n");
	fscanf(fp,"%*s\n"); // 첫줄 스킵 
	while (fscanf(fp, "%*[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%*s\n", &dayOrNight, &type, &age, &number, &price) > 0) {
		if (strcmp(dayOrNight, "주간") == 0) {
			time = 0; 
		} else if (strcmp(dayOrNight, "야간") == 0) {
			time = 1; 
		}
		
		data[time][0] += atoi(price);
		data[time][1] += atoi(number);
		
		if (strcmp(age, "유아") == 0) {
			data[time][2] += atoi(number); 
		} else if (strcmp(age, "어린이") == 0) {
			data[time][3] += atoi(number); 
		} else if (strcmp(age, "청소년") == 0) {
			data[time][4] += atoi(number); 
		} else if (strcmp(age, "성인") == 0) {
			data[time][5] += atoi(number); 
		} else if (strcmp(age, "노인") == 0) {
			data[time][6] += atoi(number); 
		} 
	}

	printf("주간권 총 %d매\n유아 %d매, 어린이 %d매, 청소년 %d매, 어른 %d매, 노인 %d매\n주간권 매출 : %d원\n\n", data[0][1], data[0][2], data[0][3], data[0][4], data[0][5], data[0][6], data[0][0]);
	printf("야간권 총 %d매\n유아 %d매, 어린이 %d매, 청소년 %d매, 어른 %d매, 노인 %d매\n야간권 매출 : %d원\n", data[1][1], data[1][2], data[1][3], data[1][4], data[1][5], data[1][6], data[1][0]);	
	printf("------------------------------------------------------\n\n");
	fclose(fp);
}

////////// 일자별 데이터 계산, 출력
void reportByDate() {
	int timeLast, year, month, date, sum;
	char time[10], price[10];
	
	fp = fopen(fileName, "r"); // 읽기전용으로 csv파일 열기 
	printf("========== 일자 별 판매현황 ===========\n");
	fscanf(fp,"%*s\n"); // 첫줄 스킵 
	
	while (fscanf(fp, "%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%*s\n", &time, &price) > 0) {
		if (atoi(time) != timeLast) {
			if (timeLast != 0) {
				printf("%10d원\n", sum);
			}
			date = atoi(time) % 100;
			month = atoi(time) % 10000 / 100;
			year =  atoi(time) / 10000;
			printf("%4d년 %2d월 %2d일 : 총 매출", year, month, date);
			sum = atoi(price); // 총 매출 계산 
			timeLast = atoi(time); 
		} else {
			sum += atoi(price);
		}
		
	}
	printf("%10d원\n", sum);
	printf("---------------------------------------\n\n");
	fclose(fp);
}

void reportByDiscount() {
	int sum = 0, numDiscount[6] = {}; //{"없음", "장애인", "국가유공자", "휴가장병", "임산부", "다자녀"};
	char number[10], discount[10];
	
	fp = fopen(fileName, "r"); // 읽기전용으로 csv파일 열기 
	printf("==== 우대권 판매현황 =====\n");
	fscanf(fp,"%*s\n"); // 첫줄 스킵 
	
	while (fscanf(fp, "%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%*[^,],%s\n", &number, &discount) > 0) {
		sum += atoi(number);
		if (strcmp(discount, "없음") == 0) {
			numDiscount[0] += atoi(number);
		} else if (strcmp(discount, "장애인") == 0) {
			numDiscount[1] += atoi(number);
		} else if (strcmp(discount, "국가유공자") == 0) {
			numDiscount[2] += atoi(number);
		} else if (strcmp(discount, "휴가장병") == 0) {
			numDiscount[3] += atoi(number);
		} else if (strcmp(discount, "임산부") == 0) {
			numDiscount[4] += atoi(number);
		} else if (strcmp(discount, "다자녀") == 0) {
			numDiscount[5] += atoi(number);
		}
	
	
	
	}
	printf("총 판매 티켓수  : %4d매\n우대 없음       : %4d매\n장애인          : %4d매\n국가유공자      : %4d매\n다자녀          : %4d매\n임산부          : %4d매\n", sum, numDiscount[0], numDiscount[1], numDiscount[2], numDiscount[3], numDiscount[4], numDiscount[5]);
	
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
