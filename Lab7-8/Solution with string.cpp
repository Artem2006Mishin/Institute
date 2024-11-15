#include <iostream>

#include <string>
#include <sstream>

using namespace std;

int find_string(string, string, string);

int main()
{
	setlocale(LC_ALL, "RU");

	string str = "AA BA AC CBB BBC ABBC";
	string str1 = "AA";
	string str2 = "BBC";

	int count = find_string(str, str1, str2);
	if (count != 0)
	{
		cout << "Кол-во: " << count;
	}
	else
	{
		cout << "Нет таких слов";
	}
	
}

int find_string(string s, string s1, string s2)
{
	stringstream str_stream(s);
	string temp;
	char del = ' ';
	int count = 0;
	size_t check1;
	size_t check2;

	while (getline(str_stream, temp, del))
	{
		check1 = temp.find(s1);
		check2 = temp.find(s2);
		if (check1 == string::npos && check2 != string::npos) {
			count++;
		}
	}

	return count;
}

