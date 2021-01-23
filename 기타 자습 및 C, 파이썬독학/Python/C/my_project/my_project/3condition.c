#include <stdio.h>
#include <time.h>

int main_condition(void)
{
	int age = 10;
	if (age >= 20) // if (조건) {}
	{
		printf("성인\n");
	}
	else if (age >= 14 && age <= 16)
	{ // 파이썬 and가 여기선 &&
		printf("중학생\n");
	}
	else if (age >= 17)
	{
		printf("고등학생\n");
	}
	else // else {}
	{
		printf("초등이하\n");
	}
	// 조건에 맞으면 if 구문을 탈출
	// 이하 else if나 else는 찾지X
	for (int stu = 1; stu <= 30; stu++)
	{
		if (stu > 5)
		{
			printf("여기까지\n");
			break; // for문 탈출
		}
		printf("%d 번 출석\n", stu);
	}

	for (int stu = 1; stu <= 30; stu++)
	{
		if (stu >= 10 && stu <= 15)
		{
			if (stu == 14)
			{
				printf("%d 번 학생은 결석\n", stu);
				continue; // for문 다음번호로
			}
			printf("%d 번 출석2\n", stu);			
		}
	}
	int al = 12;
	if (al <= 15 && al >= 10)
	{ // &&는 and
		printf("al은 10이상 15이하\n");
	}
	else
	{
		printf("al은 10미만이거나 15초과\n");
	}
	if (al > 15 || al < 10)
	{ // ||는 or
		printf("al은 10미만이거나 15초과\n");
	}
	else
	{
		printf("al은 10이상 15이하\n");
	}
	srand(time(NULL)); // 3+random.c참고
	int num1 = rand() % 3;
	if (num1 == 0)
	{
		printf("가위\n");
	}
	else if (num1 == 1)
	{
		printf("바위\n");
	}
	else
	{
		printf("보\n");
	}

	int num2 = rand() % 3;
	switch (num2) // 값을 받는다
	{
	case 0:printf("가위\n"); break;
	// break 없으면 이하구문은 조건 안보고 실행
	case 1:printf("바위\n"); break;
	case 2:printf("보\n"); break;
	default:printf("??\n");
	}
	
	age = 10;
	switch (age) // 값을 받는다
	{
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13: printf("초등학생입니다.\n"); break;
	case 14:
	case 15:
	case 16: printf("중학생입니다.\n"); break;
	case 17:
	case 18:
	case 19: printf("고등학생입니다.\n"); break;
	default:  printf("학생 아님\n"); break;
	}

	srand(time(NULL));
	int ud = rand() % 100 + 1;
	printf("숫자: %d\n", ud);
	int answer = 0;
	int chance = 5;
	while (chance > 0) // 제한 없애려면 괄호안에
		// 1(참)을 넣으면 됨 while (1) (무한루프)
	{
		printf("남은 기회: %d\n", chance--);
		printf("숫자입력(1~100): \n");
		scanf_s("%d", &answer);

		if (answer > ud)
		{
			printf("DOWN\n\n");
		}
		else if (answer < ud)
		{
			printf("UP\n\n");
		}
		else if(answer == ud)
		{
			printf("Correct");
			break;
		}
		else
		{
			printf("오류발생");
			break;
		}
		if (chance == 0)
		{
			printf("Fail");
			break;
		}
	}
	return 0;
}