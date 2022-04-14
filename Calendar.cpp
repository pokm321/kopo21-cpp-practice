///////////  1900년 1월1일이 월요일  ///////////////////
//////////  년도가 4의 배수이면 윤년. 예외로는 100의 배수중에 400의 배수만 윤년, 나머지 100의 배수는 평년.  //////////
#include <stdio.h> 
int year, month, dayOfWeek;
int lastDay[12] = {31, 28, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31}; // 각 월의 마지막날

// 입력한 년도 1월1일의 요일을 구하는 함수 
void addYears() {			
	dayOfWeek = 1; //1900년 1월1일은 월요일이고, 월요일을 1로 둘거임
	for (int i = 1900; i < year; i++) { // 1900년도부터 입력한 직전 년도 까지의 윤년여부 확인 
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) { // 만약 윤년이라면 
			dayOfWeek += 366; // 요일값dayOfWeek 에 윤년의 일수을 더한다. 
		} else {
			dayOfWeek += 365; // 평년이라면 평년의 일수를 더함 
		}
	}
}

// 입력한 월의 1일의 요일을 구하는 함수 
void addMonths() {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		lastDay[1] = 29; // 만약 입력한 년도가 윤년이라면 2월을 29일로 변경 
	}
	
	for (int i = 1; i < month; i++) {
		dayOfWeek += lastDay[i - 1]; //그해의 1월부터 입력월 직전까지의 일수를 다 더한다. 
	}
	
	dayOfWeek = dayOfWeek % 7; // 7로 나눈 나머지값이 입력한 년, 월의 1일의 요일을 나타냄 (0은 일요일, 1은 월요일, 2은 화요일, ...,)
	printf("%d", dayOfWeek);
}

//결과값 출력함수 
void printCalendar() {
	printf("\n======== %d년 %d월 ========\n", year, month);
	printf("  일  월  화  수  목  금  토\n");
	
	for (int j = 0; j < dayOfWeek; j++) { // 처음에 요일값만큼 공백을 줌 
		printf("%4s", "");
	}
	
	for (int i = 1; i <= lastDay[month - 1]; i++) { // 선택년도의 1일부터 마지막일까지 출력할거임 
		printf("%4d", i);
		dayOfWeek++;
		if (dayOfWeek > 6) { // 달력 오른쪽 끝에오면 줄바꿈 
			printf("\n");
			dayOfWeek = 0;
		}
	}
}
	
int main() {
	printf("년도 입력 : ");
	scanf("%d", &year); // year : 입력한 년도 
	printf("\n월 입력 : ");
	scanf("%d", &month); // month : 입력한 월
	
	addYears(); //입력년도 1월1일의 요일
	addMonths(); // 입력년도, 입력월 1일의 요일 
	printCalendar(); //결과값 출력 

	return 0;
}
