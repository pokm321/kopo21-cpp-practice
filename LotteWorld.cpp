// ***** �Ե����� Ƽ�Ϲ߱ޱ� *****
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
int dayOrNight, type, ssn, ssn_t, number, discount, age, timeRN, price, sum;
FILE *fp;

////////// �޴� ��� 
void printMenu() {
	printf("�ð��븦 �����ϼ���.\n1. �ְ���\n2. �߰��� (4�� ���� �����)\n-> ");
	scanf("%d", &dayOrNight);
	printf("\n������ �����ϼ���.\n1. �����̿�� (�Ե����� + �μӹڹ���)\n2. ��ũ�̿�� (�Ե�����)\n-> ");
	scanf("%d", &type);
	ssn_t = 0;
	while (ssn_t < 1 || ssn_t > 4) {  //�ֹι�ȣ ���ڸ� ù���ڰ� 1~4�� �ƴϸ� �ٽ��Է��ض�. 
		printf("\n�ֹι�ȣ�� �Է��ϼ���. (-����)\n-> ");
		scanf("%7d%*d", &ssn); //�Է��� �ֹι�ȣ ���ڸ� + ���ڸ��� ù���ڸ� �޴´�. (�� 7��) 
		ssn_t = ssn  % 10; // ssn_t : ���ڸ��� ù����
		if (ssn_t < 1 || ssn_t > 4) {
			printf("��Ȯ�� �ֹι�ȣ�� �Է����ּ���.\n");
		}
	}
	
	printf("\n��� �ֹ��Ͻðڽ��ϱ�? (�ִ� 10��)\n-> ");
	scanf("%d", &number);
	printf("\n�������� �����ϼ���.\n1. ���� (���� ���� �ڵ�ó��)\n2. �����\n3. ����������\n4. �ް��庴\n5. �ӻ��\n6. ���ڳ�\n-> ");
	scanf("%d", &discount);
}

////////// ������ ���ѵ� �/���/û�ҳ� ���� �ľ� 
int getAge() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
		
	if (ssn_t == 1 || ssn_t == 2) { //ssn_t�� 1�̳� 2�� 2000�� ���� ���, 
		ssn = (ssn / 10) + 19000000; // ssn/10 �� �ֹι�ȣ ���ڸ�, �ű⿡ ���� ���ڴ� 950522�� 19950522�� �ٲ��� 
	} else { //ssn_t�� 3�̳� 4�� 2000�� ���� ��� 
		ssn = (ssn / 10) + 20000000; // 020123�� 20020123���� �ٲ۴�. 
	}
	
	timeRN = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + (tm.tm_mday); // ���� ��¥ 
	int age = (timeRN - ssn) / 10000; // ������ 
	
	if (age > 12 && age < 19) { // û�ҳ� 13~18�� 
		age = 1;
	} else if ((age > 2 && age < 13) || age > 64) { // ��� ��� 3~12�� Ȥ�� 65���̻� 
		age = 2;
	} else if (age < 3) { // ���̺� ��� 0~2�� 
		age = 3;	
	} else { // ���ο�� 
		age = 0;
	}
	return age;
}

////////// ���� ���
int getPrice() {
	int const priceList[4][4] = {
		{62000, 54000, 47000, 15000}, // �ְ� �����̿�� , ���ʺ��� �, û�ҳ�, ���, ���̺� �� 
		{50000, 43000, 36000, 15000}, // �߰� �����̿��
		{59000, 52000, 46000, 15000}, // �ְ� ��ũ�̿�� 
		{47000, 41000, 35000, 15000}  // �߰� ��ũ�̿�� 
	};
	
	int price = priceList[dayOrNight + 2 * type - 3][age] * number; //�ش��ϴ� ������ priceList���� �̾ƿ��� ������ ���� 
	
	if (discount == 2 || discount == 3) { // �����, ���������� ����/��ũ�̿�� 50% ��� 
		price = price / 2; 
	} else if (discount == 4 && type == 1) { // �ް��庴 �����̿�� 49% ��� (����ǥ���� ���������� 50% ���ο� 500�� �߰��� �Ǿ�����.) 
		price = price / 2 + 500;
	} else if (discount == 5 && type == 1) { // �ӻ�� �����̿�� 50% ���
		price = price / 2;
	} else if (discount == 6 && type == 1) { // ���ڳ� �����̿�� 30% ��� 
		price = price * .7;
	}
	sum += price;
	return price;
}

////////// �ϳ��� �ֹ��� ���������� �޸��忡 ���پ� ��� 
void writeIt() {
	char const *dayOrNightList[2] = {"�ְ�", "�߰�"}; // �������·� ����Ǿ��ִ� ���������� ���ڿ��� �ٲ㼭 ����ϱ����� 
	char const *typeList[2] = {"�����̿��", "��ũ�̿��"};
	char const *ageList[4] = {"����", "û�ҳ�", "���", "���̺�"};
	char const *discountList[6] = {"����", "�����", "����������", "�ް��庴", "�ӻ��", "���ڳ�"};
	
	fprintf(fp, "%d,%s,%s,%s,%d,%d,%s\n", timeRN, dayOrNightList[dayOrNight - 1], typeList[type - 1], ageList[age], number, price, discountList[discount - 1]);
}

////////// ��ϵ� �޸��忡�� �����͸� �ҷ��ͼ� �� ���â�� ���
void readIt() {
	printf("======================== �Ե����� ==========================\n");
	char dayOrNightStr[10], typeStr[10], ageStr[10], discountStr[10] ,numberStr[10], priceStr[10];
	
	while (fscanf(fp, "%*[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", &dayOrNightStr, &typeStr, &ageStr, &numberStr, &priceStr, &discountStr) > 0) {
		printf("%s %s %s X\t%s\t%s��\t ������� %s\n", dayOrNightStr, typeStr, ageStr, numberStr, priceStr, discountStr);
	}
	printf("\n����� �Ѿ��� %d�� �Դϴ�.\n", sum);
	printf("============================================================");
}

////////// �����Լ�
int main() {
	int keep;
	fp = fopen("LotteReport.txt", "w");
	//fprintf(fp, "%s\n", "��¥,�ð���,����,���ɱ���,����,����,������");
	
	while (keep != 2) {
		printMenu();
		age = getAge();
		price = getPrice();
		printf("������ %d �� �Դϴ�.\n�����մϴ�.\n\n", price);
		writeIt();
		printf("��� �߱� �Ͻðڽ��ϱ�?\n1. Ƽ�� �߱�\n2. ����\n->");
		scanf("%d", &keep);		
	}
	fclose(fp);
	printf("\nƼ�� �߱��� �����մϴ�. �����մϴ�.\n\n");
	
	fp = fopen("LotteReport.txt", "r");
	readIt();
	fclose(fp);
	return 0;	
}
