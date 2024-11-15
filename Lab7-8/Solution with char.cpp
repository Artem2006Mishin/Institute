#include <iostream>

using namespace std;

int find_string(char[], char[], char[]);

int main()
{
	setlocale(LC_ALL, "RU");

	char str[] = "AAB BCCA CCB BABCC";
	char str1[] = "AA"; // НЕ содержит
	char str2[] = "BC"; // содержит
	
	int count = find_string(str, str1, str2);
	if (count != 0)
	{
		cout << "Кол-во: " << count;
	}
	else
	{
		cout << "Слов нет";
	}
	
}

int find_string(char s[], char s1[], char s2[])
{
	int count = 0;
	char* sub, * p = nullptr, * check1, * check2;
	sub = strtok_s(s, " ", &p);

	while (sub != NULL)
	{
		check1 = strstr(sub, s1); 
		check2 = strstr(sub, s2);
		if (check1 == NULL && check2 != NULL) {
			count++;
		}

		sub = strtok_s(NULL, " ", &p);
	}

	return count;
}
