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
	cout << "흑돌의 갯수: " << a << "      백돌의 갯수: " << b << endl;
	return 0;
}
//
int inputstone(int map[19][19], int& a, int& b, int& turn) {
	//

	if (turn % 2 == 0) {
		cout << "흑돌의 차례 입니다" << endl;
	}
	else if (turn % 2 == 1) {
		cout << "백돌의 차례 입니다" << endl;
	}
	//string chI;
	int x, y;
xy1:

	cout << "x좌표를 입력하세요." << endl;
x1:
	cin >> x;
	if (x < 0 || x>18) {
		cout << "다시 입력하세요" << endl;
		goto x1;
	}

	cout << "y좌표를 입력하세요." << endl;
y1:
	cin >> y;
	if ( !(y >= 0 && y<=18)) {
		cout << "다시 입력하세요" << endl;
		goto y1;
	}

	//
	if (map[x][y] == 1 || map[x][y] == 2) {
		cout << "이미 돌이 놓여 있습니다." << endl;
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
		cout << "가로" << i << "번째 행:";
		for (int j = 0; j < 19; j++) {
			if (map[i][j] == 1) {
				Bcnt++;
			}
			else if (map[i][j] == 2) {
				Wcnt++;
			}
		}
		cout << "검은돌:" << Bcnt << "개    흰돌: " << Wcnt << "개" << endl;
	}
	cout << endl;
	for (int i = 0; i < 19; i++) {
		Bcnt = 0;
		Wcnt = 0;
		cout << "세로" << i << "번째 열:";
		for (int j = 0; j < 19; j++) {
			if (map[j][i] == 1) {
				Bcnt++;
			}
			else if (map[j][i] == 2) {
				Wcnt++;
			}
		}
		cout << "검은돌:" << Bcnt << "개    흰돌: " << Wcnt << "개" << endl;
	}

	return 0;
}

int checkMax(int map[19][19], stoneRow * hd) {
	stoneRow* NewNode;
	stoneXY* newst;
	//가로
	for (int i = 0; i < 19; i++) {
		cout << "가로" << i << "번째 행:";
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		//NewNode->xy->next = NULL;
		
		for (int j = 0; j < 20; j++) {
			//검은돌 만남
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
						//delete hd; //연결부 모두 삭제
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
			//흰돌 만남
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
			//돌 없음
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
			cout << "돌이 없습니다" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "흑돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY * pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "백돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
			delrow(hd);
		}
		
	}
	//세로
	for (int j = 0; j < 19; j++) {
		cout << "세로" << j << "번째 열:";
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		//NewNode->xy->next = NULL;

		for (int i = 0; i < 20; i++) {
			//검은돌 만남
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
						//delete hd; //연결부 모두 삭제
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
			//흰돌 만남
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
			//돌 없음
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
			cout << "돌이 없습니다" << endl;
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "흑돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "백돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
		}

	}
	//대각선 오른 아래
	for (int i = 0; i < 19; i++) {
		//cout << "대각선" << i << ":";
		int j = 0;
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		cout << "오른 아래 대각선" << j << " , " << j + i << " :";
		for (j = 0; j+i < 20; j++) {
			//검은돌 만남
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
						//delete hd; //연결부 모두 삭제
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
			//흰돌 만남
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
			//돌 없음
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
			cout << "돌이 없습니다" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "흑돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "백돌 " << p->stcnt << "개 연속  좌표:";
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
		cout << "오른 아래 대각선" << j + i << " , " << j << " :";
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
						//delete hd; //연결부 모두 삭제
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
			//흰돌 만남
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
			//돌 없음
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
			cout << "돌이 없습니다" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "흑돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "백돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
			}
			cout << endl;
		}
		//delrow(hd);
	}
	//대각선 왼 아래
	for (int i = 0; i < 19; i++) {
		int j = 18;
		hd = NULL;
		NewNode = new stoneRow;
		NewNode->stcor = 0;
		NewNode->stcnt = 0;
		NewNode->next = NULL;
		cout << "왼 아래 대각선" << 18-j << " , " <<  j-i << " :";
		for (j = 18; j-i > -2; j--) {
			//검은돌 만남
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
						//delete hd; //연결부 모두 삭제
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
			//흰돌 만남
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
			//돌 없음
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
			cout << "돌이 없습니다" << endl;
			//delrow(NewNode);
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "흑돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "백돌 " << p->stcnt << "개 연속  좌표:";
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
		cout << "왼 아래 대각선" << 18 - j + i << " , " << j << " :";
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
						//delete hd; //연결부 모두 삭제
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
			//흰돌 만남
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
			//돌 없음
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
			cout << "돌이 없습니다" << endl;
		}
		else {
			for (stoneRow* p = hd; p != NULL; p = p->next) {
				if (p->stcor == 1) {
					cout << "흑돌 " << p->stcnt << "개 연속  좌표:";
					for (stoneXY* pst = p->xy; pst != NULL; pst = pst->next) {
						cout << "(" << pst->x << " ," << pst->y << ")  ";
					}
				}
				else if (p->stcor == 2) {
					cout << "백돌 " << p->stcnt << "개 연속  좌표:";
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