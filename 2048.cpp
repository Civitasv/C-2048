#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

void update(int array[4][4]);
void randTwo(int array[4][4]);
int hasEmpty(int array[4][4]);
int isFull(int array[4][4]);
void slide(char c, int array[4][4]);

// ����
static int score = 0;
// ������
static int maxScore = 0;

//��־�Ƿ������ĳ�ֲ���
int operate = 1;

int main() {

	int array[4][4] = {0};
	char c = ' ';
	while (true) {
		if (hasEmpty(array)==1&&operate==1) {
			randTwo(array);
		}
		update(array);
		if (hasEmpty(array)==0 && isFull(array)==1) {
			break;
		}
		Sleep(400);
		c = _getch();
		if (c == 'q' || c == 'Q')
			exit(0);
		while (c != 'w'&&c != 'W'&&c != 's'&&c != 'S'&&c != 'd'&&c != 'D'&&c != 'a'&&c != 'A') {
			c = _getch();
		}
		slide(c, array);
		system("cls");
	}
	printf("\nʧ��!");
	system("pause");
}

// ����ҳ��,����ҳ����Ϣ
void update(int array[4][4]) {
	printf("GAME: 2048\tScore:%d" , score);
	printf("\t\tBEST:%d",  maxScore);
	printf("\n---------------------------------------\n");
	for (int j = 0; j < 4; j++) {
		printf(" ________");
	}
	printf("\n");
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			printf("|        ");
		}
		printf("|\n");
		for (int j = 0; j < 4; j++) {
			if (array[i][j] == 0) {
				printf("|        ");
			}
			else {
				//���������µ�˳���ӡ��ά����
				printf("| %4d   ", array[i][j]);
			}
		}
		printf("|\n");
		for (int j = 0; j < 4; j++) {
			printf("|________");
		}
		printf("|\n");
	}
	printf("\n---------------------------------------\n");
	printf("��W��:UP ��S��:DOWN ��A��:LEFT ��D��:RIGHT ��Q��:EXIT");
}

// �������2
void randTwo(int array[4][4]) {
	//��ʱ��Ϊ���ӣ����������
	srand((unsigned)time(NULL));
	int i = abs(rand() % 4);
	int j = abs(rand() % 4);
	//�������Ѿ��Ǵ���0��λ������2
	while (array[i][j] != 0) {
		i = abs(rand() % 4);
		j = abs(rand() % 4);
	}
	array[i][j] = 2;
}

// �ж��������Ƿ��п�λ��
int hasEmpty(int array[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (array[i][j] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

// �ж��Ƿ��Ѿ���λ���Ҳ��ɺϲ�������Ϸ����
int isFull(int array[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (array[i][j] == array[i][k] || array[i][j] == array[k][j]) {
					return 0;
				}
			}
		}
	}
	return 1;
}

/* �ж�����ĳ��˿�λ�õ����������ܷ����
int isAvaliableAdd(int i, int j) {
	if (i == j) {
		return 1;
	}
	else {
		return 0;
	}
}*/

void slide(char c, int array[4][4]) {
	if (c == 'a' || c == 'A') {
		operate = 0;
		//ɨ�迪ʼ
		for (int i = 0; i<4; i++) {
			//ͬһ�еĲ�������
			int op = 0;
			//�������


			if (array[i][0]!=0&&array[i][2]!=0&&array[i][0] == array[i][1] && array[i][2] == array[i][3]) {
				array[i][0] *= 2;
				array[i][1] = array[i][2]*2;
				array[i][2] = 0;
				array[i][3] = 0;
				continue;
			}
			for (int j = 0; j < 4; j++) {
				int k = j;
				//����ߴ���0ʱ�������ƶ�
				while (k>0 && array[i][k] > 0 && array[i][k - 1] == 0) {
					array[i][k - 1] = array[i][k];
					array[i][k] = 0;
					k--;
					operate = 1;
				}
				//k = j;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				if (k>0 && array[i][k] == array[i][k - 1]&&op==0) {
					if (array[i][k] != 0) {
						operate = 1;
						score += array[i][k];
						op++;
					}
					array[i][k - 1] *= 2;
					array[i][k] = 0;
				}
			}
		}
		/*
		//Ϊ�˷�ֹ���ֵ�bug�����ұ���ɨ��һ��
		for (int i = 0; i<4; i++) {
			for (int j = 3; j>=0; j--) {
				int k = j;
				
				while (k>0 && array[i][k - 1] == 0) {
					array[i][k - 1] = array[i][k];
					array[i][k] = 0;
					k--;
				}
				k = j;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				while (k>0 && array[i][k] == array[i][k - 1]) {
					if (array[i][k] != 0) {
						score += array[i][k];
					}
					array[i][k - 1] *= 2;
					array[i][k] = 0;
					k--;
				}
			}
		}
		*/
		
	}
	else if (c == 'd' || c == 'D') {
		operate = 0;
		for (int i = 0; i<4; i++) {
			//ͬһ�еĲ�������
			int op = 0;
			//�������
			if (array[i][0] != 0 && array[i][2] != 0 && array[i][2] != 0 && array[i][0] == array[i][1] && array[i][2] == array[i][3]) {
				array[i][3] *= 2;
				array[i][2] = array[i][1]*2;
				array[i][1] = 0;
				array[i][0] = 0;
				continue;
			}
			for (int j = 3; j >= 0; j--) {
				int k = j;

				while (k<3 && array[i][k] > 0 &&array[i][k + 1] == 0) {
					array[i][k + 1] = array[i][k];
					array[i][k] = 0;
					k++;
					operate = 1;
				}
				//k = j;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				if (k<3 && array[i][k] == array[i][k + 1]&&op==0) {
					if (array[i][k] != 0) {
						operate = 1;
						score += array[i][k];
						op++;
					}
					array[i][k + 1] *= 2;
					array[i][k] = 0;
			
				}
			}
		}
		/*
		for (int i = 0; i<4; i++) {
			for (int j = 0; j <4; j++) {
				int k = j;
				
				while (k<3 && array[i][k + 1] == 0) {
					
					array[i][k + 1] = array[i][k];
					array[i][k] = 0;
					k++;
				}
				k = j;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				while (k<3 && array[i][k] == array[i][k + 1]) {
					if (array[i][k] != 0) {
						score += array[i][k];
					}
					array[i][k + 1] *= 2;
					array[i][k] = 0;
					k++;
				}
			}
		}
		*/
	}

	else if (c == 'w' || c == 'W') {
		operate = 0;
		for (int j = 0; j < 4; j++) {
			
			//���������ͬһ��4������ȫ��ͬ
			if (array[0][j] != 0 && array[0][j] == array[1][j] && array[2][j] == array[3][j]) {
				array[0][j] *= 2;
				array[1][j] = array[2][j]*2;
				array[2][j] = 0;
				array[3][j] = 0;
				continue;
			}
			//ͬһ�еĲ�������
			int op = 0;
			for (int i = 0; i<4; i++) {
				int k = i;
				while (k>0 && array[k][j] > 0 && array[k - 1][j] == 0) {
					array[k - 1][j] = array[k][j];
					array[k][j] = 0;
					k--;
					operate = 1;
				}
				//k = i;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				if (k>0 && array[k][j] == array[k - 1][j]&&op==0) {
					if (array[k][j] != 0) {
						score += array[k][j];
						operate = 1;
						op++;
					}
					array[k - 1][j] *= 2;
					array[k][j] = 0;
				}
			}
		}
		/*
		for (int i = 3; i >=0; i--) {
			for (int j = 0; j<4; j++) {
				int k = i;
				
				while (k>0 && array[k - 1][j] == 0) {
					array[k - 1][j] = array[k][j];
					array[k][j] = 0;
					k--;
				}
				k = i;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				while (k>0 && array[k][j] == array[k - 1][j]) {
					if (array[k][j] != 0) {
						score += array[k][j];
					}
					array[k - 1][j] *= 2;
					array[k][j] = 0;
					k--;
				}
			}
		}*/
		
	}
	else if (c == 's' || c == 'S') {
		operate = 0;
		for (int j = 3; j >= 0; j--) {
			//�������
			if (array[0][j] != 0 && array[0][j] == array[1][j] && array[2][j] == array[3][j]) {
				array[2][j] = array[1][j] * 2;
				array[1][j] = 0;
				array[0][j] = 0;
				array[3][j] *= 2;
				continue;
			}
			int op = 0;
			for (int i = 3; i>=0; i--) {
				int k = i;

				while (k<3 && array[k][j] > 0 && array[k + 1][j] == 0) {
					array[k + 1][j] = array[k][j];
					array[k][j] = 0;
					k++;
					operate = 1;
				}
				//k = i;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				if (k<3 && array[k][j] == array[k + 1][j]&&op==0) {
					if (array[k][j] != 0) {
						score += array[k][j];
						operate = 1;
						op++;
					}
					array[k + 1][j] *= 2;
					array[k][j] = 0;
				}
			}
		}
		/*
		for (int i = 0; i<4; i++) {
			for (int j = 0; j<4; j++) {
				int k = i;
				
				while (k<3&&array[k + 1][j] == 0) {
					array[k + 1][j] = array[k][j];
					array[k][j] = 0;
					k++;
				}
				k = i;
				//�ж����ڵ������Ƿ���ȣ���ȼ������ƶ�
				while (k<3&&array[k][j] == array[k + 1][j]) {
					if (array[k][j] != 0) {
						score += array[k][j];
					}
					array[k + 1][j] *= 2;
					array[k][j] = 0;
					k++;
				}
			}
		}
		*/
	}
	
}

/* ����֮��Ľ���ж�
void slideResult(char c, int array[4][4]) {


		slide(c, array);

	
}*/
