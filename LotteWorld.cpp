// ***** 롯데월드 티켓발급기 *****
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
int dayOrNight, type, ssn, ssn_t, number, discount, age, timeRN, price, sum;
FILE *fp;

////////// 메뉴 출력 
void printMenu() {
	printf("시간대를 선택하세요.\n1. 주간권\n2. 야간권 (4시 이후 입장시)\n-> ");
	scanf("%d", &dayOrNight);
	printf("\n권종을 선택하세요.\n1. 종합이용권 (롯데월드 + 민속박물관)\n2. 파크이용권 (롯데월드)\n-> ");
	scanf("%d", &type);
	ssn_t = 0;
	while (ssn_t < 1 || ssn_t > 4) {  //주민번호 뒷자리 첫글자가 1~4가 아니면 다시입력해라. 
		printf("\n주민번호를 입력하세요. (-제외)\n-> ");
		scanf("%7d%*d", &ssn); //입력한 주민번호 앞자리 + 뒷자리의 첫글자만 받는다. (총 7자) 
		ssn_t = ssn  % 10; // ssn_t : 뒷자리의 첫글자
		if (ssn_t < 1 || ssn_t > 4) {
			printf("정확한 주민번호를 입력해주세요.\n");
		}
	}
	
	printf("\n몇개를 주문하시겠습니까? (최대 10개)\n-> ");
	scanf("%d", &number);
	printf("\n우대사항을 선택하세요.\n1. 없음 (나이 우대는 자동처리)\n2. 장애인\n3. 국가유공자\n4. 휴가장병\n5. 임산부\n6. 다자녀\n-> ");
	scanf("%d", &discount);
}

////////// 만나이 구한뒤 어른/어린이/청소년 여부 파악 
int getAge() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
		
	if (ssn_t == 1 || ssn_t == 2) { //ssn_t가 1이나 2면 2000년 이전 출생, 
		ssn = (ssn / 10) + 19000000; // ssn/10 은 주민번호 앞자리, 거기에 더한 숫자는 950522를 19950522로 바꿔줌 
	} else { //ssn_t가 3이나 4면 2000년 이후 출생 
		ssn = (ssn / 10) + 20000000; // 020123을 20020123으로 바꾼다. 
	}
	
	timeRN = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + (tm.tm_mday); // 현재 날짜 
	int age = (timeRN - ssn) / 10000; // 만나이 
	
	if (age > 12 && age < 19) { // 청소년 13~18세 
		age = 1;
	} else if ((age > 2 && age < 13) || age > 64) { // 어린이 요금 3~12세 혹은 65세이상 
		age = 2;
	} else if (age < 3) { // 베이비 요금 0~2세 
		age = 3;	
	} else { // 성인요금 
		age = 0;
	}
	return age;
}

////////// 가격 계산
int getPrice() {
	int const priceList[4][4] = {
		{62000, 54000, 47000, 15000}, // 주간 종합이용권 , 왼쪽부터 어른, 청소년, 어린이, 베이비 순 
		{50000, 43000, 36000, 15000}, // 야간 종합이용권
		{59000, 52000, 46000, 15000}, // 주간 파크이용권 
		{47000, 41000, 35000, 15000}  // 야간 파크이용권 
	};
	
	int price = priceList[dayOrNight + 2 * type - 3][age] * number; //해당하는 가격을 priceList에서 뽑아온후 갯수를 곱함 
	
	if (discount == 2 || discount == 3) { // 장애인, 국가유공자 종합/파크이용권 50% 우대 
		price = price / 2; 
	} else if (discount == 4 && type == 1) { // 휴가장병 종합이용권 49% 우대 (가격표에선 실질적으로 50% 할인에 500원 추가로 되어있음.) 
		price = price / 2 + 500;
	} else if (discount == 5 && type == 1) { // 임산부 종합이용권 50% 우대
		price = price / 2;
	} else if (discount == 6 && type == 1) { // 다자녀 종합이용권 30% 우대 
		price = price * .7;
	}
	sum += price;
	return price;
}

////////// 하나의 주문이 끝날때마다 메모장에 한줄씩 기록 
void writeIt() {
	char const *dayOrNightList[2] = {"주간", "야간"}; // 숫자형태로 저장되어있는 선택지들을 문자열로 바꿔서 기록하기위함 
	char const *typeList[2] = {"종합이용권", "파크이용권"};
	char const *ageList[4] = {"성인", "청소년", "어린이", "베이비"};
	char const *discountList[6] = {"없음", "장애인", "국가유공자", "휴가장병", "임산부", "다자녀"};
	
	fprintf(fp, "%d,%s,%s,%s,%d,%d,%s\n", timeRN, dayOrNightList[dayOrNight - 1], typeList[type - 1], ageList[age], number, price, discountList[discount - 1]);
}

////////// 기록된 메모장에서 데이터를 불러와서 총 결과창을 출력
void readIt() {
	printf("======================== 롯데월드 ==========================\n");
	char dayOrNightStr[10], typeStr[10], ageStr[10], discountStr[10] ,numberStr[10], priceStr[10];
	
	while (fscanf(fp, "%*[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", &dayOrNightStr, &typeStr, &ageStr, &numberStr, &priceStr, &discountStr) > 0) {
		printf("%s %s %s X\t%s\t%s원\t 우대적용 %s\n", dayOrNightStr, typeStr, ageStr, numberStr, priceStr, discountStr);
	}
	printf("\n입장료 총액은 %d원 입니다.\n", sum);
	printf("============================================================");
}

////////// 메인함수
int main() {
	int keep;
	fp = fopen("LotteReport.txt", "w");
	//fprintf(fp, "%s\n", "날짜,시간대,권종,연령구분,수량,가격,우대사항");
	
	while (keep != 2) {
		printMenu();
		age = getAge();
		price = getPrice();
		printf("가격은 %d 원 입니다.\n감사합니다.\n\n", price);
		writeIt();
		printf("계속 발권 하시겠습니까?\n1. 티켓 발권\n2. 종료\n->");
		scanf("%d", &keep);		
	}
	fclose(fp);
	printf("\n티켓 발권을 종료합니다. 감사합니다.\n\n");
	
	fp = fopen("LotteReport.txt", "r");
	readIt();
	fclose(fp);
	return 0;	
}
