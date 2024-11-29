#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//typedef struct _score  //typedef 안하면 매번 struct _score 해줘야함
//{
//	int id;
//	char name[10];
//	int jumsu;
//
//}SCORE;
////void func(SCORE *p)
////{
////	p->jumsu = 200; //(*p).jumsu = 200;이거를 화살표로 할수있는거여
////	
////}
////
////SCORE func(void)
////{
////	SCORE x = { 10,"Lim", 100 };
////	return x;
////
////}
////void main(void)
////{
////
////	//SCORE x;    //c초기화할때 SCORE x= {10,"Lim", 100} 으로 선언해도됨
////	//x.id = 10;
////	//x.jumsu = 100;
////	//strcpy(x.name, "Lim"); //문자열 복사함수 내가 넣고자하는 공간의 시작주소를 알려줘야함
////	////				// 널문자 나올때까지 복사해주는 strcpy
////
////
////	//func(&x);
////
////	//printf("%d\n%s\n%d", x.id, x.name, x.jumsu);
////
////	SCORE y = func();
////	printf("%d\n%s\n%d", y.id, y.name, y.jumsu);
////
////}
//
////void func(SCORE *p)
////{
////	p->jumsu = 200; //(*p).jumsu = 200;이거를 화살표로 할수있는거여
////	
////}
//
//SCORE *func(void)
//{
//	SCORE x = { 10,"Lim", 200 };
//	return &x;
//
//}
//void main(void)
//{
//
//	//SCORE x;    //c초기화할때 SCORE x= {10,"Lim", 100} 으로 선언해도됨
//	//x.id = 10;
//	//x.jumsu = 100;
//	//strcpy(x.name, "Lim"); //문자열 복사함수 내가 넣고자하는 공간의 시작주소를 알려줘야함
//	////				// 널문자 나올때까지 복사해주는 strcpy
//
//
//	//func(&x);
//
//	//printf("%d\n%s\n%d", x.id, x.name, x.jumsu);
//
//	SCORE *y = func();
//	printf("%d\n %s\n %d\n", y->id, y->name, y->jumsu);
//
//}



//#include <stdio.h>
//#include <string.h>
//
//typedef struct _score
//{
//	int id;
//	int jumsu;
//	char name[10];
//}SCORE;
//
//#define MAX_ST		20
//
//SCORE exam[MAX_ST]; //20개짜리 스코어 구조체 받겠다는 선형 자료구조에 사용할 저장공간
//
//SCORE test[22] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
//				   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"},\
//				   {22, 0, "choi"}, {12, 28, "mo"}, {18, 51, "lee"}, {14, 43, "lee"}, {11, 91, "min"},\
//				   {13, 41, "kim"}, {15, 15, "kong"}, {19, 100, "park"}, {17, 72, "seo"}, {16, 99, "lim"},\
//				   {20, 98, "do"}, {21, 100, "kong" }, };
//
//void Make_Test_Data(int n)
//{
//	int i;
//
//	for (i = 0; i < n; i++)
//	{
//		exam[i] = test[i];
//	}
//}
//
#if 0
#define _CRT_SECURE_NO_WARNINGS // Visual Studio의 경우 scanf 오류 방지용으로 실습자료 상단에 항상 추가
#include <stdio.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST		20

SCORE exam[MAX_ST];

SCORE test[22] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
				   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"},\
				   {22, 0, "choi"}, {12, 28, "mo"}, {18, 51, "lee"}, {14, 43, "lee"}, {11, 91, "min"},\
				   {13, 41, "kim"}, {15, 15, "kong"}, {19, 100, "park"}, {17, 72, "seo"}, {16, 99, "lim"},\
				   {20, 98, "do"}, {21, 100, "kong" }, };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Print_All_Data(void)
{
	for (int i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0)
			return i;
		printf("[%d]ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);
	}
}

int Print_Data(int no)
{
	int i;
	if (exam[no].id == 0)
		return -1;
	
	else
	{
		printf("ID=%d, NAME=%s, SCORE=%d\n", exam[no].id, exam[no].name, exam[no].jumsu);
		return 1;
	}
}

void main(void)
{
	int r, n,m;
	scanf("%d %d", &n, &m);
	Make_Test_Data(n);
	//r = Print_All_Data();
	r = Print_Data(m);
	printf("%d\n", r);
}
#endif

#if 0
#include <stdio.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST		20

SCORE exam[MAX_ST];

SCORE test[22] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
				   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"},\
				   {22, 0, "choi"}, {12, 28, "mo"}, {18, 51, "lee"}, {14, 43, "lee"}, {11, 91, "min"},\
				   {13, 41, "kim"}, {15, 15, "kong"}, {19, 100, "park"}, {17, 72, "seo"}, {16, 99, "lim"},\
				   {20, 98, "do"}, {21, 100, "kong" }, };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);
	}

	return i;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("ID=%d, NAME=%s, SCORE=%d\n", exam[no].id, exam[no].name, exam[no].jumsu);
	return 1;
}

int Count_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
	}

	return i;
}

int Create_Data(SCORE * p)
{
	scanf("%d %s %d", &p->id, p->name, &p->jumsu);

	return 1;
}

int Insert_Data(SCORE *p)
{
	//빈자리 찾고 싶어
	int i;
	for (i = 0; i < MAX_ST; i++) //스무개 다돌았는데빈자리없으면 풀방이니 -1리턴
	{
		if (exam[i].id == 0) //들어갈자리 빈자리
		{
			exam[i] = *p;
			return i;
		}
		if (exam[i].id == p->id) //같은게 이미 있으면
		{
			return -2;
		}

	}
	return -1; // 풀방시 -1리턴
	
}

void main(void)
{
	int i, n;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("%d\n", Insert_Data(&test[i]));
		printf("%d\n", Print_All_Data());
	}

	printf("%d\n", Insert_Data(&test[i - 1]));
	printf("%d\n", Print_All_Data());
}
#endif

#if 0
#include <stdio.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST      20

SCORE exam[MAX_ST];

SCORE test[22] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
				   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"},\
				   {22, 0, "choi"}, {12, 28, "mo"}, {18, 51, "lee"}, {14, 43, "lee"}, {11, 91, "min"},\
				   {13, 41, "kim"}, {15, 15, "kong"}, {19, 100, "park"}, {17, 72, "seo"}, {16, 99, "lim"},\
				   {20, 98, "do"}, {21, 100, "kong" }, };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);
	}

	return i;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("ID=%d, NAME=%s, SCORE=%d\n", exam[no].id, exam[no].name, exam[no].jumsu);
	return 1;
}

int Count_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
	}

	return i;
}

int Create_Data(SCORE * p)
{
	scanf("%d %s %d", &p->id, p->name, &p->jumsu);

	return 1;
}

int Insert_Data(SCORE * p)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0)
		{
			exam[i] = (*p);
			return i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}

	return -1;
}

int Delete_Data(int id)
{
	int i;
	int j;

	if (exam[0].id == 0)
	{
		return -2;
	}

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == id)
		{
			for (j = i; j < (MAX_ST - 1); j++)
			{
				if (exam[j + 1].id == 0)
				{
					exam[j].id = 0;
					return i;
				}

				exam[j] = exam[j + 1];
			}

			exam[j].id = 0;
			return i;
		}
	}

	return -1;
}

int id[] = { 10,1,8,9,2,4,11 };

void main(void)
{
	int i;

	Make_Test_Data(5);
	printf("Data Count = %d\n", Print_All_Data());

	for (i = 0; i < 7; i++)
	{
		printf("Deleted Element = %d\n", Delete_Data(id[i]));
		printf("Data Count = %d\n", Print_All_Data());
	}
}
#endif

#if 0
#include <stdio.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST      20

SCORE exam[MAX_ST];

SCORE test[22] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
				   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"},\
				   {22, 0, "choi"}, {12, 28, "mo"}, {18, 51, "lee"}, {14, 43, "lee"}, {11, 91, "min"},\
				   {13, 41, "kim"}, {15, 15, "kong"}, {19, 100, "park"}, {17, 72, "seo"}, {16, 99, "lim"},\
				   {20, 98, "do"}, {21, 100, "kong" }, };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);
	}

	return i;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("ID=%d, NAME=%s, SCORE=%d\n", exam[no].id, exam[no].name, exam[no].jumsu);
	return 1;
}

int Count_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
	}

	return i;
}

int Create_Data(SCORE * p)
{
	scanf("%d %s %d", &p->id, p->name, &p->jumsu);

	return 1;
}

int Insert_Data(SCORE * p)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0)
		{
			exam[i] = (*p);
			return i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}

	return -1;
}

int Delete_Data(int id)
{
	int i;
	int j;

	if (exam[0].id == 0)
	{
		return -2;
	}

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == id)
		{
			for (j = i; j < (MAX_ST - 1); j++)
			{
				if (exam[j + 1].id == 0)
				{
					exam[j].id = 0;
					return i;
				}

				exam[j] = exam[j + 1];
			}

			exam[j].id = 0;
			return i;
		}
	}

	return -1;
}

int Search_Complete_Data(SCORE * p)
{
	int i;

	if (exam[0].id == 0)
	{
		return -2;
	}

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) return -1;
		if ((exam[i].id == p->id) && (exam[i].jumsu == p->jumsu))
		{
			if (!strcmp(exam[i].name, p->name)) return i;
		}
	}

	return -1;
}

SCORE tmp[] = { {4, 45, "lee"} , {10, 50, "kim"}, {8, 50, "lew"}, {2, 80, "law"}, {2, 81, "lew"} };

void main(void)
{
	int i;

	Make_Test_Data(4);
	printf("Printed Data Count = %d\n", Print_All_Data());

	for (i = 0; i < 5; i++)
	{
		printf("Searched Element = %d\n", Search_Complete_Data(&tmp[i]));
	}

	for (i = 0; i < 4; i++)
	{
		Delete_Data(tmp[i].id);
	}

	printf("Searched Element = %d\n", Search_Complete_Data(&tmp[0]));
}
#endif

#include <stdio.h>
#include <string.h>
//
//void func(int *p)
//{
//	//*(p + 2) = 50;          // 같은소리임
//	p[2] = 50;
//}
//
//int * f2 (void)
//{
//	static int b[4] = { 10,20,30,40 };
//	return b;
//}
//void main()
//{
//
//	int a[4] = { 10,20,30,40 };
//	printf("%d\n", f2()[2]);
//	printf("%d\n", a[2]);
//	func(a);
//	printf("%d\n", a[2]);
//}
//void f(int(*p)[4]) //p==&a   *p==*&a 
//{
//	printf("%d\n", (*p)[2]);//a[2]
//	printf("%d\n", p[0][2]);//a[2]
//}
//
//void f1(int (*p)[3])
//{
//	printf("%d\n", p[1][2]);//a[1][2] == *(*(p+1)+2))
//}
//
//void main()
//{
//
//	int a[2][3] = { {10,20,30},{40,50,60} };
//	f1(a);
//	
//}

#if 0

int add(int a, int b)
{
	return a + b;
}

void f1(void)
{
	printf("func\n");
}

int * f2(void)
{
	static int a[4] = { 1,2,3,4 };

	return a;
}

void main(void)
{
	// p, q, r 선언

	int (*p)(int, int);
	
	void(*q)(void);

	int *(*r)(void);



	// p, q, r에 대응 함수 대입

	p = add;

	q = f1;

	r = f2;

	printf("%d\n", p(3,4));
	q();
 
	
	printf("%d\n", r()[2]);




	printf("%d\n", add(3, 4));
	f1();
	printf("%d\n", f2()[2]);

	// 위와 동일한 결과가 나오도록 p, q, r로 실행



}
#endif

//11월29일  자료구조

#if 0
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	int next;
}SCORE;

#define MAX_ST	20

SCORE exam[MAX_ST] = { {-1, 0, "", 0} };

SCORE test[22] = { {10, 50, "kim", 0}, {2, 80, "lew", 0}, {8, 50, "lew", 0}, {4, 45, "lee", 0}, {1, 90, "song", 0},\
				   {3, 45, "kim", 0}, {5, 50, "song", 0 }, {9, 100, "lee", 0}, {7, 75, "moon", 0}, {6, 90, "park", 0},\
				   {22, 0, "choi", 0}, {12, 28, "mo", 0 }, {18, 51, "lee", 0}, {14, 43, "lee", 0}, {11, 91, "min", 0},\
				   {13, 41, "kim", 0}, {15, 15, "kong", 0}, {19, 100, "park", 0}, {17, 72, "seo", 0}, {16, 99, "lim", 0},\
				   {20, 98, "do", 0}, {21, 100, "kong", 0} };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Create_Data(SCORE * p)
{
	printf("\n사번을 입력하시오 => ");
	scanf(" %d", &p->id);
	printf("이름을 입력하시오 => ");
	scanf(" %s", p->name);
	printf("점수를 입력하시오 => ");
	scanf("%d", &p->jumsu);
	p->next = 0;

	return 1;
}

int Print_All_Data(void)
{
	int i, cnt = 0;

	printf("Head.next = %d\n", exam[0].next);

	for (i = 1; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) continue;
		printf("[%d] ID=%d, NAME=%s, SCORE=%d, next = %d\n", i, exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next);
		cnt++;
	}

	return cnt;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("[%d] ID=%d, NAME=%s, SCORE=%d, next = %d\n", no, exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next);
	return 1;
}

int Count_Data(void)
{
	int i, cnt = 0;

	for (i = 1; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) continue;
		cnt++;
	}

	return cnt;
}

int Insert_Data(SCORE * p)   //빈방을 찾아서 찾은방의 번호를 리턴해주는 기능 차거나 기존에 같으면 에러코드 
{
	int i, empty = 0;

	for (i = 1; i < MAX_ST; i++)
	{
		if (empty == 0 && exam[i].id == 0)
		{
			empty = i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}

	if (empty != 0)
	{
		exam[empty] = *p;
		return empty;
	}

	return -1;
}

int Insert_Node(SCORE * d)
{
	/*int i, empty = 0;

	int current = 0;
	int next ;


	int r = Insert_Data(d);

	if (r < 0)
		return r;

	r = exam[0].next;
	current = exam[r].next;
	if(exam[next].id > exam[r].id)
*/
	//r? 링크따라 스캔하면서 자리를 넣어주면됨
	// 코드 작성

	int r = Insert_Data(d);

	if (r < 0)
		return r;

	int curr = 0;//헤드니깐 커런트 0
	int next = exam[curr].next; //헤드의 아이디니깐 0으로 세팅해놓으면 안돼용

	for(;;)  //while 같은겨
	{
		if ((next ==0) ||(exam[next].id > (d->id))) //찾았으면 
		{
			exam[r].next = next;
			exam[curr].next = r;
			return 1;
		}

		curr = next;
		next = exam[curr].next; //못찾았으면 한발 전진
	}
}

void main(void)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Data Count = %d\n", Count_Data());
	}
}
#endif

#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	int next;
}SCORE;

#define MAX_ST	20

SCORE exam[MAX_ST] = { {-1, 0, "", 0} };

SCORE test[22] = { {10, 50, "kim", 0}, {2, 80, "lew", 0}, {8, 50, "lew", 0}, {4, 45, "lee", 0}, {1, 90, "song", 0},\
				   {3, 45, "kim", 0}, {5, 50, "song", 0 }, {9, 100, "lee", 0}, {7, 75, "moon", 0}, {6, 90, "park", 0},\
				   {22, 0, "choi", 0}, {12, 28, "mo", 0 }, {18, 51, "lee", 0}, {14, 43, "lee", 0}, {11, 91, "min", 0},\
				   {13, 41, "kim", 0}, {15, 15, "kong", 0}, {19, 100, "park", 0}, {17, 72, "seo", 0}, {16, 99, "lim", 0},\
				   {20, 98, "do", 0}, {21, 100, "kong", 0} };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Create_Data(SCORE * p)
{
	printf("\n사번을 입력하시오 => ");
	scanf(" %d", &p->id);
	printf("이름을 입력하시오 => ");
	scanf(" %s", p->name);
	printf("점수를 입력하시오 => ");
	scanf("%d", &p->jumsu);
	p->next = 0;

	return 1;
}

int Print_All_Data(void)
{
	int i, cnt = 0;

	printf("Head.next = %d\n", exam[0].next);

	for (i = 1; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) continue;
		printf("[%d] ID=%d, NAME=%s, SCORE=%d, next = %d\n", i, exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next);
		cnt++;
	}

	return cnt;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("[%d] ID=%d, NAME=%s, SCORE=%d, next = %d\n", no, exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next);
	return 1;
}

int Count_Data(void)
{
	int i, cnt = 0;

	for (i = 1; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) continue;
		cnt++;
	}

	return cnt;
}

int Insert_Data(SCORE * p)
{
	int i, empty = 0;

	for (i = 1; i < MAX_ST; i++)
	{
		if (empty == 0 && exam[i].id == 0)
		{
			empty = i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}

	if (empty != 0)
	{
		exam[empty] = *p;
		return empty;
	}

	return -1;
}

int Insert_Node(SCORE * d)
{
	int prev = 0;
	int next = exam[0].next;
	int pos = Insert_Data(d);

	if (pos < 0)
	{
		return pos;
	}

	for (;;)
	{
		if ((next == 0) || (d->id < exam[next].id))
		{
			exam[pos].next = next;
			exam[prev].next = pos;
			return 1;
		}

		prev = next;
		next = exam[next].next;
	}
}

int Print_All_Node(void)
{
	int n = exam[0].next;
	int cnt = 0;

	for (;;)
	{
		if (n == 0) return cnt;
		Print_Data(n);
		n = exam[n].next;
		cnt++;
	}
}
int Search_Id_Node(int id)
{
	int next = exam[0].next;  // 첫 번째 노드를 가리킴

	for (;;)
	{
		if ((next == 0) || (exam[next].id > id))
		{
			return -1;  // 찾지 못한 경우
		}
		if (exam[next].id == id)
			return next;
		next = exam[next].next;
	}
}

void main(void)
{
	int i;
	int pos;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&test[i]));
	}

	printf("Printed Data Count = %d\n", Print_All_Node());

	printf("Searched Node Index = %d\n", pos = Search_Id_Node(8));

	if (pos != -1)
	{
		Print_Data(pos);
	}

	printf("Searched Node Index = %d\n", pos = Search_Id_Node(7));

	if (pos != -1)
	{
		Print_Data(pos);
	}
}
#endif

#if 0

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	int next;
}SCORE;

#define MAX_ST	20

SCORE exam[MAX_ST] = { {-1, 0, "", 0} };

SCORE test[22] = { {10, 50, "kim", 0}, {2, 80, "lew", 0}, {8, 50, "lew", 0}, {4, 45, "lee", 0}, {1, 90, "song", 0},\
				   {3, 45, "kim", 0}, {5, 50, "song", 0 }, {9, 100, "lee", 0}, {7, 75, "moon", 0}, {6, 90, "park", 0},\
				   {22, 0, "choi", 0}, {12, 28, "mo", 0 }, {18, 51, "lee", 0}, {14, 43, "lee", 0}, {11, 91, "min", 0},\
				   {13, 41, "kim", 0}, {15, 15, "kong", 0}, {19, 100, "park", 0}, {17, 72, "seo", 0}, {16, 99, "lim", 0},\
				   {20, 98, "do", 0}, {21, 100, "kong", 0} };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Create_Data(SCORE * p)
{
	printf("\n사번을 입력하시오 => ");
	scanf(" %d", &p->id);
	printf("이름을 입력하시오 => ");
	scanf(" %s", p->name);
	printf("점수를 입력하시오 => ");
	scanf("%d", &p->jumsu);
	p->next = 0;

	return 1;
}

int Print_All_Data(void)
{
	int i, cnt = 0;

	printf("Head.next = %d\n", exam[0].next);

	for (i = 1; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) continue;
		printf("[%d] ID=%d, NAME=%s, SCORE=%d, next = %d\n", i, exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next);
		cnt++;
	}

	return cnt;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("[%d] ID=%d, NAME=%s, SCORE=%d, next = %d\n", no, exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next);
	return 1;
}

int Count_Data(void)
{
	int i, cnt = 0;

	for (i = 1; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) continue;
		cnt++;
	}

	return cnt;
}

int Insert_Data(SCORE * p)
{
	int i, empty = 0;

	for (i = 1; i < MAX_ST; i++)
	{
		if (empty == 0 && exam[i].id == 0)
		{
			empty = i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}

	if (empty != 0)
	{
		exam[empty] = *p;
		return empty;
	}

	return -1;
}

int Insert_Node(SCORE * d)
{
	int prev = 0;
	int next = exam[0].next;
	int pos = Insert_Data(d);

	if (pos < 0)
	{
		return pos;
	}

	for (;;)
	{
		if ((next == 0) || (d->id < exam[next].id))
		{
			exam[pos].next = next;
			exam[prev].next = pos;
			return 1;
		}

		prev = next;
		next = exam[next].next;
	}
}

int Print_All_Node(void)
{
	int n = exam[0].next;
	int cnt = 0;

	for (;;)
	{
		if (n == 0) return cnt;
		Print_Data(n);
		n = exam[n].next;
		cnt++;
	}
}

int Search_Id_Node(int id)
{
	int n = exam[0].next;

	for (;;)
	{
		if (n == 0 || exam[n].id > id) return -1;
		if (exam[n].id == id) return n;
		n = exam[n].next;
	}
}

int Delete_Node(int id)
{/*
	int p = 0;
	int n = exam[0].next;

	for (;;)
	{
		if (n == 0 || (id > exam[n].id))
			return -1;
		if (exam[n].id == id)
		{
			exam[n].id = 0;
			
			exam[n].next = exam[n].next;
		}
		p = n;
		n = exam[n].next;
	}*/
	int n = exam[0].next;
	int prev = 0;

	for (;;)
	{
		if (n == 0 || exam[n].id > id) return -1;

		if (exam[n].id == id)
		{
			exam[n].id = 0;
			exam[prev].next = exam[n].next;
			return 1;
		}

		prev = n;
		n = exam[n].next;
	}


}

void main(void)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&test[i]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node());

	printf("Delete Node(%d) Result = %d\n", 8, Delete_Node(8));
	printf("Delete Node(%d) Result = %d\n", 7, Delete_Node(7));
	printf("Delete Node(%d) Result = %d\n", 1, Delete_Node(1));
	printf("Delete Node(%d) Result = %d\n", 10, Delete_Node(10));

	printf("Printed Node Count = %d\n", Print_All_Node());
}

#endif

//print 참조 코드 : printf("STACK[%d] = %d\n", i, Stack[i]);
#include <stdio.h>

#define MAX_STACK		10
#define STACK_EMPTY	MAX_STACK
#define STACK_FULL		0

int Push_Stack(int data);
int Pop_Stack(int *p);
int Print_Stack(void);
int Count_Full_Data_Stack(void);
int Count_Empty_Data_Stack(void);

int a[MAX_STACK + 1] = { 1,2,3,4,5,6,7,8,9,10,11 };
int Stack[MAX_STACK];
int Sptr = STACK_EMPTY;

int Push_Stack(int data)
{
	if (Sptr == STACK_FULL) //스택포인터가 1이면 
	{
		return -1;
	}

	Sptr--;
	Stack[Sptr] = data;
	return 1;
}

int Pop_Stack(int *p)
{
	if (Sptr == STACK_EMPTY)
	{
		return -1;
	}
	*p = Stack[Sptr];
	Sptr++;
	return 1;
}

int Print_Stack(void)
{
	for (int i = Sptr; i <= (STACK_EMPTY - 1); i++)
	{

		printf("STACK[%d] = %d\n", i, Stack[i]);
	}
		return STACK_EMPTY - Sptr;
}

int Count_Full_Data_Stack(void)
{
	return STACK_EMPTY - Sptr;
}

int Count_Empty_Data_Stack(void)
{
	return Sptr - STACK_FULL;
}

void main(void)
{
	int i;

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < 5; i++)
	{
		printf("Push Result = %d\n", Push_Stack(a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < 5; i++)
	{
		printf("Pop Result = %d\n", Pop_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("Push Result = %d\n", Push_Stack(a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("Pop Result = %d\n", Pop_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");
}