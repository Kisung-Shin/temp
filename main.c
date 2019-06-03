#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
//#include <unistd.h>

void manageAccount();
typedef enum { false, true } bool;

typedef struct {
	char accountnumber[10];
	void(*print)(void*);
} Account;

typedef struct {
	char accountnumber[128];
} serverAccount;

void sendToServer(Account* account, serverAccount* serverside) {
	free(account);
	serverside = malloc(256);
	//printf("�ּҰ� %p", manageAccount);
	printf("�Է��Ͻ� ���°� �½��ϱ�? \n");
	scanf("%128s", serverside->accountnumber);
	printf("ó���� ���´� ������ �����ϴ�. : \n");
	account->print(account);
}

void captchaFinalStage() {
	int total, sending, accountmanage;
	printf("��ü ���� ������ ������ �˷��ּ��� : ");
	scanf("%d", &total);
	printf("�� �� �۱� ���� ������ ������ �˷��ּ��� : ");
	scanf("%d", &sending);
	printf("���� ���� ������ ������ �˷��ּ��� : ");
	scanf("%d", &accountmanage);
	int* hashTable = (int*)malloc(total);
	for (int i = 0; i < sending; i++) {
		hashTable[i] = i;
		printf("%d ", hashTable[i]);
		if (i % 10 == 9)
			printf("\n");
	}

	free(hashTable);

	for (int i = 0; i < accountmanage; i++) {
		printf("%d ", hashTable[i]);
		if (i % 10 == 9)
			printf("\n");
	}
}
void captchaSecondStage() {
	//int *account = (int*)(Data + 16);
	//printf("\t\tarr3 : %d\n", *account);
	int* captcha = malloc(sizeof(int));
	printf("���� ���̴� ���ڸ� �Է����ּ��� : 5 \n");
	scanf("%d", captcha);
	if (*captcha==5) {
		captchaFinalStage();
	}
}

void captchaFirstStage() {
	//int *menu = (int*)(Data + 12);
	//printf("\t\tarr2 : %d\n", *menu);
	int* captcha = malloc(sizeof(int));
	printf("���� ���̴� ���ڸ� �Է����ּ��� : 1234 \n");
	scanf("%d", captcha);
	if (*captcha ==1234) {
		captchaSecondStage();
	}
}

void printAccount(Account* account) {
	printf("%s\n", account->accountnumber);
}

void manageAccount(void) {//������-�����ڿ��Լ�
	FILE* fd = fopen("userInfo.txt", "r");
	//printf("This is Shell\n");
	char* pstr;
	char strTemp[33];
	while (!feof(fd)) {
		pstr = fgets(strTemp, sizeof(strTemp) + 1, fd);
		//printf("%s",strTemp);
		char* a = strtok(strTemp, " ");
		char* b = strtok(NULL, " ");
		char* c = strtok(NULL, " ");
		char* d = strtok(NULL, " ");
		//printf("%s %s %s %s ",a, b, c, d);
		printf("%s", b);
	}
}

bool login(char* input_id, char* input_pw, char* compare_id, char* compare_pw, FILE* fd) {
	char* pstr;
	char strTemp[33];
	while (!feof(fd)) {
		pstr = fgets(strTemp, sizeof(strTemp) + 1, fd);
		compare_id = strtok(strTemp, " ");
		compare_pw = strtok(NULL, " ");

		if (!strcmp(input_id, compare_id)) {
			if (!strcmp(input_pw, compare_pw)) {
				return true;
			}
			else {
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool compare(char* input_account, char* compare_account, char* compare_accountpw, FILE* fd) {
	char* pstr;
	char strTemp[33];
	rewind(fd);
	while (!feof(fd)) {
		pstr = fgets(strTemp, sizeof(strTemp) + 1, fd);
		strtok(strTemp, " ");
		strtok(NULL, " ");
		strcpy(compare_account, strtok(NULL, " "));
		if (!strncmp(input_account, compare_account, 8)) {
			strcpy(compare_accountpw, strtok(NULL, " "));
			return true;
		}
	}
	return false;
}
int main(void)
{
	FILE* fd = fopen("userInfo.txt", "r");
	if (fd == NULL)
	{
		printf("�������� ������ �ҷ��� �� �����ϴ�.");
	}
	char* input_id = malloc(8);
	char* input_pw = malloc(8);
	char* compare_id = malloc(8);
	char* compare_pw = malloc(8);
	char* input_account = malloc(8);
	char* compare_accountpw = malloc(4);
	char* compare_account = malloc(8);
	char* input_accountpw = malloc(4);

	printf("ȯ���մϴ�! ���Ͻô� �ŷ��� �����ϼ���. 1:�۱��ϱ� 2:�������� \n");
	int dealnum;
	scanf("%d", &dealnum);
	if (dealnum == 1) {
		printf("���̵� �Է����ּ���. \n ID : ");
		scanf("%s", input_id);
		printf("��й�ȣ�� �Է����ּ���.\n PW : ");
		scanf("%s", input_pw);
		if (login(input_id, input_pw, compare_id, compare_pw, fd)) {
			printf("�Ա��Ͻ� ���¸� �Է����ּ���. : \n");
			scanf("%s", input_account);
			if (compare(input_account, compare_account, compare_accountpw, fd)) {
				Account* account;
				serverAccount* serverside = NULL;
				account = malloc(256);
				strcpy(account->accountnumber, compare_account);
				printf("�Է��Ͻ� ���´� ������ �����ϴ�. : \n");
				account->print = (void*)printAccount;
				account->print(account);
				sendToServer(account, serverside);
			}
		}
	}
	else if (dealnum == 2) {
		printf("���� ������ ���Ͻø� [delete!]��� �Է����ּ��� : ");
		char* command = malloc(8);
		scanf("%s", command);
		if (command[0] == 'd'&&command[1] == 'e'&&command[2] == 'l'&&command[3] == 'e' &&command[4] == 't'&& command[5] == 'e'&&command[6] == '!') {
			//int* pw = (int*)(command + 8);
			//printf("\tarr1 : %d\n", *arr1);
			int* captcha = malloc(1);
			printf("���� ���̴� ���ڸ� �Է����ּ��� : 999 \n");
			scanf("%d", captcha);
			if (*captcha == 999) {
				captchaFirstStage();
			}
		}
	}
	else {
		printf("�߸��� �Է��Դϴ�. ");
	}
	free(input_id);
	free(input_pw);
	free(compare_id);
	free(compare_pw);
	free(input_account);
	free(compare_accountpw);
	free(compare_account);
	free(input_accountpw);
	system("pause");
}