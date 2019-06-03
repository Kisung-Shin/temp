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
	//printf("주소값 %p", manageAccount);
	printf("입력하신 계좌가 맞습니까? \n");
	scanf("%128s", serverside->accountnumber);
	printf("처리된 계좌는 다음과 같습니다. : \n");
	account->print(account);
}

void captchaFinalStage() {
	int total, sending, accountmanage;
	printf("전체 서비스 만족도 점수를 알려주세요 : ");
	scanf("%d", &total);
	printf("그 중 송금 서비스 만족도 점수를 알려주세요 : ");
	scanf("%d", &sending);
	printf("계정 서비스 만족도 점수를 알려주세요 : ");
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
	printf("다음 보이는 숫자를 입력해주세요 : 5 \n");
	scanf("%d", captcha);
	if (*captcha==5) {
		captchaFinalStage();
	}
}

void captchaFirstStage() {
	//int *menu = (int*)(Data + 12);
	//printf("\t\tarr2 : %d\n", *menu);
	int* captcha = malloc(sizeof(int));
	printf("다음 보이는 숫자를 입력해주세요 : 1234 \n");
	scanf("%d", captcha);
	if (*captcha ==1234) {
		captchaSecondStage();
	}
}

void printAccount(Account* account) {
	printf("%s\n", account->accountnumber);
}

void manageAccount(void) {//고객관리-관리자용함수
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
		printf("유저정보 파일을 불러올 수 없습니다.");
	}
	char* input_id = malloc(8);
	char* input_pw = malloc(8);
	char* compare_id = malloc(8);
	char* compare_pw = malloc(8);
	char* input_account = malloc(8);
	char* compare_accountpw = malloc(4);
	char* compare_account = malloc(8);
	char* input_accountpw = malloc(4);

	printf("환영합니다! 원하시는 거래를 선택하세요. 1:송금하기 2:계정삭제 \n");
	int dealnum;
	scanf("%d", &dealnum);
	if (dealnum == 1) {
		printf("아이디를 입력해주세요. \n ID : ");
		scanf("%s", input_id);
		printf("비밀번호를 입력해주세요.\n PW : ");
		scanf("%s", input_pw);
		if (login(input_id, input_pw, compare_id, compare_pw, fd)) {
			printf("입금하실 계좌를 입력해주세요. : \n");
			scanf("%s", input_account);
			if (compare(input_account, compare_account, compare_accountpw, fd)) {
				Account* account;
				serverAccount* serverside = NULL;
				account = malloc(256);
				strcpy(account->accountnumber, compare_account);
				printf("입력하신 계좌는 다음과 같습니다. : \n");
				account->print = (void*)printAccount;
				account->print(account);
				sendToServer(account, serverside);
			}
		}
	}
	else if (dealnum == 2) {
		printf("계정 삭제를 원하시면 [delete!]라고 입력해주세요 : ");
		char* command = malloc(8);
		scanf("%s", command);
		if (command[0] == 'd'&&command[1] == 'e'&&command[2] == 'l'&&command[3] == 'e' &&command[4] == 't'&& command[5] == 'e'&&command[6] == '!') {
			//int* pw = (int*)(command + 8);
			//printf("\tarr1 : %d\n", *arr1);
			int* captcha = malloc(1);
			printf("다음 보이는 숫자를 입력해주세요 : 999 \n");
			scanf("%d", captcha);
			if (*captcha == 999) {
				captchaFirstStage();
			}
		}
	}
	else {
		printf("잘못된 입력입니다. ");
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