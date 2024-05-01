#include<iostream>
#include<windows.h>
#include<string>

using namespace std;

struct stoneXY {
	int x;
	int y;
	stoneXY* next;
};

struct stoneRow{
	int stcor;
	int stcnt;
	stoneXY * xy;

	stoneRow * next;
};

int delst(stoneXY* st) {
	stoneXY* temp1 = st;
	stoneXY* temp2 = st;
	st = NULL;

	while (temp1 != NULL) {
		temp2 = temp1->next;
		delete temp1;
		temp1 = temp2;
	}

	return 0;
}

int delrow(stoneRow* st) {
	stoneRow* temp1 = st;
	stoneRow* temp2 = st;
	st = NULL;

	while (temp1 != NULL) {
		temp2 = temp1->next;
		delst(temp1->xy);
		delete temp1;
		temp1 = temp2;
	}

	return 0;
}

//
int printmap(int map[19][19], int a, int b) {
	system("cls");
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (map[i][j] == 0) {
				cout.width(3);
				cout << "+";
			}
			else if (map[i][j] == 1) {
				cout.width(3);
				cout << "@";
			}
			else if (map[i][j] == 2) {
				cout.width(3);
				cout << "#";
			}
		}
		cout << endl;
	}
	//
	cout << "�浹�� ����: " << a << "      �鵹�� ����: " << b << endl;
	return 0;
}
//
int inputstone(int map[19][19], int& a, int& b, int& turn) {
	//

	if (turn % 2 == 0) {
		cout << "�浹�� ���� �Դϴ�" << endl;
	}
	else if (turn % 2 == 1) {
		cout << "�鵹�� ���� �Դϴ�" << endl;
	}
	//string chI;
	int x, y;
xy1:

	cout << "x��ǥ�� �Է��ϼ���." << endl;
x1:
	cin >> x;
	if (x < 0 || x>18) {
		cout << "�ٽ� �Է��ϼ���" << endl;
		goto x1;
	}

	cout << "y��ǥ�� �Է��ϼ���." << endl;
y1:
	cin >> y;
	if ( !(y >= 0 && y<=18)) {
		cout << "�ٽ� �Է��ϼ���" << endl;
		goto y1;
	}

	//
	if (map[x][y] == 1 || map[x][y] == 2) {
		cout << "�̹� ���� ���� �ֽ��ϴ�." << endl;
		goto xy1;
	}
	else {
		if (turn % 2 == 0) {
			map[x][y] = 1;
			a++;
			turn++;
		}
		else if (turn % 2 == 1) {
			map[x][y] = 2;
			b++;
			turn++;
		}
	}

	return 0;
}

int checkStone(int map[19][19] ,int a,int b) {
	int Bcnt ;
	int Wcnt ;
	for (int i = 0; i < 19; i++) {
		Bcnt = 0;
		Wcnt = 0;
		cout << "����" << i << "��° ��:";
		for (int j = 0; j < 19; j++) {
			if (map[i][j] == 1) {
				Bcnt++;
			}
			else if (map[i][j] == 2) {
				Wcnt++;
			}
		}
		cout << "������:" << Bcnt << "��    ��: " << Wcnt << "��" << endl;
	}
	cout << endl;
	for (int i = 0; i < 19; i++) {
		Bcnt = 0;
		Wcnt = 0;
		cout << "����" << i << "��° ��:";
		for (int j = 0; j < 19; j++) {
			if (map[j][i] == 1) {
				Bcnt++;
			}
			else if (map[j][i] == 2) {
				Wcnt++;
			}
		}
		cout << "������:" << Bcnt << "��    ��: " << Wcnt << "��" << endl;
	}

	return 0;
}

int checkMax(int map[19][19], stoneRow * hd) {
	stoneRow* NewNode;
	stoneXY* newst;
	//����
	for (int i = 0; i < 19; i++) {
		cout << "����" << i << "��° ��:";
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		//NewNode->xy->next = NULL;
		
		for (int j = 0; j < 20; j++) {
			//������ ����
			if (map[i][j] == 1) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 1;
					NewNode->stcnt = 1;

					newst= new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
					//newst = NULL;
					//delete newst;
				}
				else if (NewNode->stcor == 1) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
					//delete newst;
				}
				else if (NewNode->stcor == 2) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						//delete hd; //����� ��� ����
						delrow(hd); 
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 1;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else if (map[i][j] == 2) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 2;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 2) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 1) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 2;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else {
				if (NewNode->stcor != 0) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 0;
					NewNode->stcnt = 0;
					NewNode->next = NULL;
				}
			}
		}

		if (hd == NULL) {
			cout << "���� �����ϴ�" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "�浹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY * pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "�鵹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
			delrow(hd);
		}
		
	}
	//����
	for (int j = 0; j < 19; j++) {
		cout << "����" << j << "��° ��:";
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		//NewNode->xy->next = NULL;

		for (int i = 0; i < 20; i++) {
			//������ ����
			if (map[i][j] == 1) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 1;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
					//newst = NULL;
					//delete newst;
				}
				else if (NewNode->stcor == 1) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
					//delete newst;
				}
				else if (NewNode->stcor == 2) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						//delete hd; //����� ��� ����
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 1;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else if (map[i][j] == 2) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 2;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 2) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 1) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 2;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else {
				if (NewNode->stcor != 0) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 0;
					NewNode->stcnt = 0;
					NewNode->next = NULL;
				}
			}
		}

		if (hd == NULL) {
			cout << "���� �����ϴ�" << endl;
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "�浹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "�鵹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
		}

	}
	//�밢�� ���� �Ʒ�
	for (int i = 0; i < 19; i++) {
		//cout << "�밢��" << i << ":";
		int j = 0;
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		cout << "���� �Ʒ� �밢��" << j << " , " << j + i << " :";
		for (j = 0; j+i < 20; j++) {
			//������ ����
			if (map[j][j+i] == 1) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 1;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = j;
					newst->y = j+i;
					newst->next = NULL;

					NewNode->xy = newst;
					//newst = NULL;
					//delete newst;
				}
				else if (NewNode->stcor == 1) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = j;
					newst->y = j+i;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
					//delete newst;
				}
				else if (NewNode->stcor == 2) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						//delete hd; //����� ��� ����
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 1;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = j;
					newst->y = j+i;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else if (map[j][j + i] == 2) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 2;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = j;
					newst->y = j+i;
					newst->next = NULL;

					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 2) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = j;
					newst->y = j+i;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 1) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 2;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = j;
					newst->y = j+i;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else {
				if (NewNode->stcor != 0) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 0;
					NewNode->stcnt = 0;
					NewNode->next = NULL;
				}
			}
			//map[j+i][j];
		}
		if (hd == NULL) {
			cout << "���� �����ϴ�" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "�浹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "�鵹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
			//delrow(hd);
		}
		delrow(hd);
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		j = 0;
		cout << "���� �Ʒ� �밢��" << j + i << " , " << j << " :";
		for (j = 0; j + i < 20; j++) {
			if (map[j+i][j] == 1) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 1;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = j+i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
					//newst = NULL;
					//delete newst;
				}
				else if (NewNode->stcor == 1) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = j+i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
					//delete newst;
				}
				else if (NewNode->stcor == 2) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						//delete hd; //����� ��� ����
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 1;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = j+i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else if (map[j+i][j] == 2) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 2;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = j+i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 2) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = j+i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 1) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 2;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = j+i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else {
				if (NewNode->stcor != 0) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 0;
					NewNode->stcnt = 0;
					NewNode->next = NULL;
				}
			}
			//map[j+i][j];

		}
		if (hd == NULL) {
			cout << "���� �����ϴ�" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "�浹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "�鵹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
		}
		//delrow(hd);
	}
	//�밢�� �� �Ʒ�
	for (int i = 0; i < 19; i++) {
		int j = 18;
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		cout << "�� �Ʒ� �밢��" << 18-j << " , " <<  j-i << " :";
		for (j = 18; j-i > -2; j--) {
			//������ ����
			if (map[18-j][j-i] == 1) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 1;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = 18-j;
					newst->y = j-i;
					newst->next = NULL;

					NewNode->xy = newst;
					//newst = NULL;
					//delete newst;
				}
				else if (NewNode->stcor == 1) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = 18-j;
					newst->y = j-i;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
					//delete newst;
				}
				else if (NewNode->stcor == 2) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						//delete hd; //����� ��� ����
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 1;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = 18-j;
					newst->y = j-i;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else if (map[18-j][j-i] == 2) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 2;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = 18-j;
					newst->y = j-i;
					newst->next = NULL;

					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 2) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = 18-j;
					newst->y = j-i;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 1) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 2;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = 18-j;
					newst->y = j-i;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else {
				if (NewNode->stcor != 0) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 0;
					NewNode->stcnt = 0;
					NewNode->next = NULL;
				}
			}
		}
		if (hd == NULL) {
			cout << "���� �����ϴ�" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "�浹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "�鵹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
			//delrow(hd);
		}

		delrow(hd);
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		j = 18;
		cout << "�� �Ʒ� �밢��" << 18 - j + i << " , " << j << " :";
		for (j = 18; j-i >-2; j--) {
			if (map[18-j +i][j] == 1) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 1;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = 18-j + i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
					//newst = NULL;
					//delete newst;
				}
				else if (NewNode->stcor == 1) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = 18-j + i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
					//delete newst;
				}
				else if (NewNode->stcor == 2) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						//delete hd; //����� ��� ����
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 1;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = 18-j + i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else if (map[18-j + i][j] == 2) {
				if (NewNode->stcor == 0) {
					NewNode->stcor = 2;
					NewNode->stcnt = 1;

					newst = new stoneXY;
					newst->x = 18-j + i;
					newst->y = j;
					newst->next = NULL;

					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 2) {
					NewNode->stcnt++;

					newst = new stoneXY;
					newst->x = 18-j + i;
					newst->y = j;

					newst->next = NewNode->xy;
					NewNode->xy = newst;
				}
				else if (NewNode->stcor == 1) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 2;
					NewNode->stcnt = 1;
					NewNode->next = NULL;

					newst = new stoneXY;
					newst->x = 18-j + i;
					newst->y = j;
					newst->next = NULL;
					NewNode->xy = newst;
					//delete newst;
				}
			}
			//�� ����
			else {
				if (NewNode->stcor != 0) {
					if (hd == NULL) {
						hd = NewNode;
					}
					else if (NewNode->stcnt > hd->stcnt) {
						delrow(hd);
						hd = NewNode;
					}
					else if (NewNode->stcnt == hd->stcnt) {
						NewNode->next = hd;
						hd = NewNode;
					}
					else if (NewNode->stcnt < hd->stcnt) {
						delst(NewNode->xy);
						delete NewNode;
					}
					NewNode = new stoneRow;
					NewNode->stcor = 0;
					NewNode->stcnt = 0;
					NewNode->next = NULL;
				}
			}
			//map[j+i][j];

		}
		
		if (hd == NULL) {
			cout << "���� �����ϴ�" << endl;
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "�浹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "�鵹 " << p->stcnt << "�� ����  ��ǥ:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
		}
		//delrow(hd);
	}

	return 0;
}

int main() {

	int map[19][19] = { 0 };

	stoneRow * hd;
	//hd = (stoneRow*)malloc(sizeof(stoneRow));
	hd = NULL;
	//hd->next = NULL;

	int a = 0;
	int b = 0;
	int turn = 0;

	while (1) {
		printmap(map, a, b);
		checkStone(map, a, b);
		checkMax(map, hd);
		inputstone(map, a, b, turn);
		//checkStone(map, a, b);
	}


}