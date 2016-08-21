//main.cpp
#include <iostream>
#include <conio.h>
#include <cstring>
#include <iomanip>
#include <locale.h>
#include <string>
#include <vector>
using namespace std;

const int SIZE = 50;

//���������� ���������� ��������� �� ����� �� ��������� �� ��������
void getResult(char*);

//���������� ��������� ������ ������ �� ��������� ��������� �����
string solve(const string&);

//��� ���������� ��������
void inSolve(vector<string>&, char);

//�������� ����� �� ������������
void correctSentence(char []);

//��������� �� �������
void errorSentence(const char* err);


int main()
{
	setlocale(LC_CTYPE, "");
	char str[SIZE];

	cout << "\n������� ���������: ";
	//cin.getline(str, SIZE);
	strcpy_s(str, "-1 + 5 - 3 ");
	cout << str << endl;
	correctSentence(str);
	getResult(str);

	cout << "\n������� ���������: ";
	strcpy_s(str, " -10 + (8*2.5)- (3 / 1,5) ");
	cout << str << endl;
	correctSentence(str);
	getResult(str);
	
	cout << "\n������� ���������: ";
	strcpy_s(str, "1 +(2*(2.5 + 2.5 + (3 - 2))) - (3/1.5)");
	cout << str << endl;
	correctSentence(str);
	getResult(str);

	cout << "\n������� ���������: ";
	strcpy_s(str, "1.1 +2.1 + abc");
	cout << str << endl;
	correctSentence(str);
	getResult(str);
	_getche();

	return 0;
}


void getResult(char* str)
{
	vector<string> v;
	string temp;
	int i = 0; 

	while( i < strlen(str))
	{
		if (str[i] == '(')
		{ v.push_back("");	}

		else 
		{
			//����� ��������� ������ ������
			if(str[i] == ')')
			{
				temp = v.back();
				v.pop_back();
				temp = solve(temp);

				//���� ���� ��� ��������� �� �������� ����� 
				if(!v.empty())
				{
					temp = v.back() + temp;
					v.pop_back();
				}
				v.push_back(temp);
			}

			//��������� ������� ������ �����������
			else
			{
				//��� 1 ������� - ������ ���������� � ������
				if(i == 0)	
				{
					temp = str;
					v.push_back(temp.substr(0,1));
					i++; 
					continue;
				}

				temp = v.back() + str[i];
				v.pop_back();
				v.push_back(temp);
			}
		}
		i++;
	}
	//���������
	cout << "���������: " << setprecision(3) << stod(solve(v.back()));
}




string solve(const string& eq)
{
	vector<string> v2;
	string temp;
	char oper1, oper2;
	bool minus = false;

	oper1 = oper2 = ' ';
	v2.push_back(eq.substr(0,1));

	for(int i = 1; i < eq.length(); i++)
	{
		//���� ����� �������������
		if (minus)
		{
			temp = v2.back();
			v2.pop_back();
			temp += eq.substr(i,1);
			v2.push_back(temp);
			minus = false;
			continue;
		}

		//���� ����� �������������
		if(
			eq[i] == '-' && 
			(eq[i-1] == '+' || eq[i-1] == '-' || eq[i-1] == '*' || eq[i-1] == '/')
			)
		{
			v2.push_back(eq.substr(i,1));
			minus = true;
			continue;
		}


		//���� ������� ������� - �����
		if( (eq[i] >= '0' && eq[i] <= '9') || eq[i] == '.')
		{
			if (
				(eq[i-1] == '+' || eq[i-1] == '-' || eq[i-1] == '*' || eq[i-1] == '/')
				&& (i-1) != 0	 
				)
			{ v2.push_back(eq.substr(i,1));	}

			else
			{
				temp = v2.back() + eq.substr(i,1);
				v2.pop_back();
				v2.push_back(temp);
			}
		}


		//���� ������� ������� - �����. ��������
		if(
			(eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/')
			|| (i== eq.length()-1) )
		{

			if ( oper1 == ' ')
			{
				if (i == eq.length()-1)
					break;

				v2.push_back(eq.substr(i,1));
				oper1 = eq[i];
			}

			else
			{
				if (oper2 != ' ')
				{
					inSolve(v2, oper2);
					oper2 = ' ';
				}

				if((oper1 == '+' || oper1 == '-')
					&& (eq[i] == '*' || eq[i] == '/'))
				{
					oper2 = eq[i];
					v2.push_back(eq.substr(i,1));
				}

				else
				{	
					inSolve(v2, oper1);
					if(i==eq.length()-1)
						break;

					oper1 = eq[i];
					v2.push_back(eq.substr(i,1));
				}
			}
		}
	}
	return v2.back();
}


void inSolve(vector<string>& v2, char op)
{
	double d1, d2;
	d2 = stod(v2.back());

	if(abs(d2 > 10000000))
		errorSentence("����� � ��������� ��� ��������� ������ 10 000 000");

	v2.pop_back();
	v2.pop_back();
	d1 = stod(v2.back());

	if(abs(d1 > 10000000))
		errorSentence("����� � ��������� ��� ��������� ������ 10 000 000");

	v2.pop_back();

	switch (op)
	{
	case '+': d1 += d2;break;
	case '-': d1 -= d2;break;
	case '*': d1 *= d2;break;
	case '/': d1 /= d2;break;
	}

	if(abs(d1 > 10000000))
		errorSentence("����� � ��������� ��� ��������� ������ 10 000 000");

	v2.push_back(to_string(d1));
}

void errorSentence(const char* err)
{
	cerr << err;
	_getch();
	exit(1);
}



void correctSentence(char str[SIZE])
{
	char temp[SIZE];
	int i, j = 0;

	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] == ' ')  {continue;}
		if(str[i] == ',' || str[i] == '.')  {temp[j++] = '.'; continue;}

		if( 
			str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' 
			|| str[i] == '(' || str[i] == ')' || (str[i] >= '0' && str[i] <= '9')
			)
		{temp[j++] = str[i];}
		else 
		{errorSentence("��������� �����������!");}
	}


	for(i = 0; i < j ; i++)
		str[i] = temp[i];
	str[i] ='\0';
}
