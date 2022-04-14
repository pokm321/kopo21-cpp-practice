#include <stdio.h>

const float RATE_USD = 1233.1; //�޷�ȯ�� 
const float RATE_JPY = 9.87; //��ȭȯ��
const float RATE_EUR = 1342.51; //����ȯ��
const float RATE_CNY = 193.5; //����ȯ�� 
const float RATE_GBP = 1603.15; //�Ŀ��ȯ�� 
int inputWon, output, change, currency;

//ó�� �޴� ���, �Է°��޴� �Լ�
int menu() {
	printf("ȯ���� ���ϴ� �ݾ��� �Է��ϼ���(��ȭ) : ");
	scanf("%d", &inputWon);	//������ ��ȭ �Է� 
	
	do {
		printf("ȯ���� ��ȭ�� �����ϼ��� (1:USD, 2:JPY, 3:EUR 4.CNY, 5:GBP) : ");
		scanf("%d", &currency); // ��ȭ ���� �Է� 
	} while (currency < 1 || currency > 5); //�Է°��� 1~5�϶� �Ѿ
	return 0;
}

// ȯ���ݾ�(output)�� �Ž�����(change)�� ����ϴ� �Լ� 
int exchange(float a, char *unit) { //a�� ȯ��, unit�� ȭ����� 
	printf("\n���� ȯ�� : %.2f KRW/%s\n\nȯ�� ���\n", a, unit); //����ȯ�� ��� 
	output = inputWon / a; //ȯ���ݾ� ��� 
	change = (int)(inputWon - output * a) / 10 * 10; //�Ž����� ��� 
	return 0;
}

// �Ž�����(change)�� �� ���󰹼� ��� �Լ� 
int ChangesToGive () {
	// �Ž����� ��� 
	printf("�Ž�����: %d�� ---> ", change);
	// ���󰹼� ��� 
	printf("1000��:%d,  ", change / 1000);
	change = change % 1000;
	printf("500��:%d,  ", change / 500);
	change = change % 500;
	printf("100��:%d,  ", change / 100);
	change = change % 100;
	printf("50��:%d,  ", change / 50); 
	change = change % 50;
	printf("10��:%d\n", change / 10);
	return 0; 
}

// ȯ���ݾ�(output)�� ���󰹼� ��� �Լ�
int BillsToGive(char *unit, int bill_1, int bill_2, int bill_3, int bill_4, int bill_5) { // (ȭ��, ������� 1,2,3,4,5) 
	// ȯ���ݾ� ��� (e.g. "�޷� : 40�޷�")
	printf("%s : %d%s ---> ", unit, output, unit);
	// ���󰹼� ��� 
	printf("%d%s:%d,  ", bill_1, unit, output / bill_1);
	output = output % bill_1;
	printf("%d%s:%d,  ", bill_2, unit, output / bill_2);
	output = output % bill_2;
	printf("%d%s:%d,  ", bill_3, unit, output / bill_3);
	output = output % bill_3;
	printf("%d%s:%d,  ", bill_4, unit, output / bill_4);
	output = output % bill_4;
	printf("%d%s:%d\n", bill_5, unit, output / bill_5);
	return 0; 
}

int main() {
	menu();
	
	if (currency == 1) { // 1:USD
		exchange(RATE_USD, "USD");
		BillsToGive("�޷�", 100, 50, 20, 5, 1);
	} else if (currency == 2) { // 2:JPY
		exchange(RATE_JPY, "JPY");
		BillsToGive("��", 5000, 1000, 100, 10, 1);
	} else if (currency == 3) { // 3:EUR
		exchange(RATE_EUR, "EUR");
		BillsToGive("����", 100, 50, 20, 5, 1);
	} else if (currency == 4) { // 4.CNY
		exchange(RATE_CNY, "CNY");
		BillsToGive("����", 100, 50, 20, 5, 1);
	} else if (currency == 5) { // 5:GBP
		exchange(RATE_GBP, "GBP");
		BillsToGive("�Ŀ��", 50, 20, 10, 5, 1);
	}
	
	ChangesToGive(); 
	return 0;
}  
