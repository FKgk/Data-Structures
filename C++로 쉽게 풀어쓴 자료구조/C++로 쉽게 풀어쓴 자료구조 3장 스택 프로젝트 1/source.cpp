#pragma warning(disable:4996)
#include "ArrayStack.h"

bool checkMatching(const char * filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		error("Error : 파일 존재하지 않습니다.");

	int nLine = 1; // 읽은 라인의 개수
	int nChar = 0; // 읽은 문자 개수
	int prev; // 이전

	bool stringCheck = false;// '' or "" 안에 있는 지 검사 1
	bool remark = false; // 주석인지 검사 2
	
	ArrayStack stack;
	char ch;

	while ((ch = getc(fp)) != EOF)
	{
		
		if (ch == '\n')
		{
			nLine++;
			if (remark == true)
				remark = false;
		}
		nChar++;

		if (stack.isEmpty() != true)
			prev = stack.peek();

		if (stack.isEmpty() == false && prev == '\\' && stringCheck == true && remark == false)
		{
			stack.pop();
		}
		else if (stack.isEmpty() == false && prev == '/' && stringCheck == true && ch == '*')
		{
			remark = true;
		}
		else if (ch == '\'' || ch == '\"')
		{
			if (stringCheck == false) // 문자열 시작
			{
				stack.push(ch);
				stringCheck = true;
			}
			else
			{
				if (stack.isEmpty() == true)
					continue;
				prev = stack.pop();
				if (prev == '\\')
					continue;
				if ((ch == '\'' && prev == '\'') ||
					ch == '\"' && prev == '\"')
				{
					stringCheck = false;
				}
				else
					break;
			}
		}
		else if (ch == '\\' && remark == false)
		{
			stack.push(ch);
		}
		else if (ch == '/' && remark == false && stringCheck == false)
		{
			if (stack.isEmpty() == false)
			{
				prev = stack.peek();
				if (prev == '/')
				{
					remark = true;
					stack.pop();
				}
				else
					stack.push(ch);
			}
		}
		else if ( (ch == '[' || ch == '{' || ch == '(') && (stringCheck == false && remark == false))
		{	
			stack.push(ch);
		}
		else if ( (ch == ']' || ch == '}' || ch == ')') && (stringCheck == false && remark == false) )
		{
			prev = stack.pop();
			if ((ch == ']' && prev != '[') ||
				(ch == '}' && prev != '{') ||
				(ch == ')' && prev != '('))
			{
				break;
			}
		}
	}

	fclose(fp);
	printf("\n[%s] 파일 검사결과 : \n", filename);
	if (!stack.isEmpty())
		printf("Error: 문제 발견 (라인 수 = %d, 문자 수 = %d)\n\n", nLine, nChar);
	else
		printf("OK : 괄호 닫기 정상 (라인 수 = %d, 문자 수 = %d)\n\n", nLine, nChar);
	//EOF인데 ()))))) 1개가 남음
	printf("Error ; %c , %d\n", prev, ch == EOF);
	while (!stack.isEmpty())
	{
		printf("%c ", stack.pop());
	}
	printf("\n");
	return stack.isEmpty();
}

int main(void)
{
	checkMatching("ArrayStack.h");
	checkMatching("source.cpp");
}
/*
))
*/