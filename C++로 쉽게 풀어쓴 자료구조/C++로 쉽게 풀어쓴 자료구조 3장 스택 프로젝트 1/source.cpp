#pragma warning(disable:4996)
#include "ArrayStack.h"

bool checkMatching(const char * filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		error("Error : ���� �������� �ʽ��ϴ�.");

	int nLine = 1; // ���� ������ ����
	int nChar = 0; // ���� ���� ����
	int prev; // ����

	bool stringCheck = false;// '' or "" �ȿ� �ִ� �� �˻� 1
	bool remark = false; // �ּ����� �˻� 2
	
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
			if (stringCheck == false) // ���ڿ� ����
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
	printf("\n[%s] ���� �˻��� : \n", filename);
	if (!stack.isEmpty())
		printf("Error: ���� �߰� (���� �� = %d, ���� �� = %d)\n\n", nLine, nChar);
	else
		printf("OK : ��ȣ �ݱ� ���� (���� �� = %d, ���� �� = %d)\n\n", nLine, nChar);
	//EOF�ε� ()))))) 1���� ����
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