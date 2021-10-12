#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

bool summary(bool first, bool  second)
{
	if (first && second) return true;
	else return (first + second);
}

bool function(vector<bool>term)
{
	bool result = !(summary(!term[0], !term[1]) * !((!term[0]) * term[2]));
	return result;
}

void sdnf(vector<vector<bool>> term)
{
	cout << "F(sdnf)(a,b,c) = ";
	for (int i = 0; i < term.size(); i++)
	{
		cout << "(";
		if (term[i][0]) cout << "a*";
		else cout << "!a*";
		if (term[i][1]) cout << "b*";
		else cout << "!b*";
		if (term[i][2]) cout << "c";
		else cout << "!c";
		cout << ")";
		if (i != (term.size() - 1)) cout << " + ";
		
	}
	cout << ";" << endl;
}

void sknf(vector<vector<bool>> term)
{
	cout << "F(sknf)(a,b,c) = ";
	for (int i = 0; i < term.size(); i++)
	{
		cout << "(";
		if (!term[i][0]) cout << "a+";
		else cout << "!a+";
		if (!term[i][1]) cout << "b+";
		else cout << "!b+";
		if (!term[i][2]) cout << "c";
		else cout << "!c";
		cout << ")";
		if (i != (term.size() - 1)) cout << " * ";
	}
	cout << ";" << endl;
}

int calculator(vector<bool> term)
{
	int result = 0, index = term.size()  - 1;
	for (int i = 0; i < term.size(); i++)
	{
		result += term[i] * pow(2, index);
		index--;
	}
	return result;
}

void numeral(vector<vector<bool>> term)
{
	cout << "(";
	for (int i = 0; i < term.size(); i++)
	{
		cout << calculator(term[i]);
		if (i != term.size() - 1) cout << ",";
	}
	cout << ");" << endl;
}

bool encode(string reverse, vector<bool>triple)
{
	stack<bool>result;
	bool first, second;
	for (int i = 0; i < reverse.size(); i++)
	{
		if (reverse[i] == 'a') result.push(triple[0]);
		else if (reverse[i] == 'b') result.push(triple[1]);
		else if (reverse[i] == 'c') result.push(triple[2]);
		else if (reverse[i] == '!') {
			first = result.top();
			result.pop();
			result.push(!first);
		}
		else if (reverse[i] == '+') {
			first = result.top();
			result.pop();
			second = result.top();
			result.pop();
			result.push(summary(first, second));
		}
		else if (reverse[i] == '*') {
			first = result.top();
			result.pop();
			second = result.top();
			result.pop();
			result.push(first * second);
		}
	}
	return result.top();
}

void deny(string& name)
{
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] == ' ') {
			name.erase(name.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] == '!' && name[i + 1] == '(') {
			name.erase(name.begin() + i);
			stack<char>stack;
			stack.push('(');
			int index = i + 1;
			while (stack.size() != 0)
			{
				if (name[index] == '(') stack.push('(');
				else if (name[index] == ')') stack.pop();
				index++;
			}
			name.insert(name.begin() + index, '!');
		}
		else if (name[i] == '!' && (name[i + 1] == 'a' || name[i + 1] == 'b' || name[i + 1] == 'c')) {
			name.erase(name.begin() + i);
			name.insert(name.begin() + i + 1, '!');
		}
	}
}

string translate()
{
	string name;
	cout << "Enter your function : ";
	getline(cin , name);
	deny(name);
	stack<char> stack;
	string result;
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] == 'a' || name[i] == 'b' || name[i] == 'c') {
			result.push_back(name[i]);
		}
		else if (name[i] == '!') result.push_back('!');
		else if (name[i] == ')') {
			while (stack.top() != '(')
			{
				result.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
			if (stack.size() != 0 && stack.top() == '*') {
				if (name[i + 1] != '!') {
					result.push_back('*');
					stack.pop();
				}
				else {
					result.push_back(name[i + 1]);
					result.push_back('*');
					stack.pop();
					i++;
				}
			}
		}
		else if (name[i] == '*') {
			if (name[i + 1] == 'a' || name[i + 1] == 'b' || name[i + 1] == 'c') {
				if (name[i + 2] != '!') {
					result.push_back(name[i + 1]);
					result.push_back(name[i]);
					i++;
				}
				else {
					result.push_back(name[i + 1]);
					result.push_back(name[i + 2]);
					result.push_back(name[i]);
					i += 2;
				}
			}
			else stack.push(name[i]);
				
		}
		else stack.push(name[i]);
	}
	while (!stack.empty())
	{
		result.push_back(stack.top());
		stack.pop();
	}
	return result;
}

void transformator()
{
	vector<vector<bool>> data { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
	vector<vector<bool>> sdnfprototype;
	vector<vector<bool>> sknfprototype;
	vector<bool>number;
	string function = translate();
	cout << function << endl;
	int index;
	for (int i = 0; i < data.size(); i++)
	{
		if (encode(function, data[i])) {
			sdnfprototype.push_back(data[i]);
			number.push_back(1);
		}
		else {
			sknfprototype.push_back(data[i]);
			number.push_back(0);
		}
	}
	sdnf(sdnfprototype);
	sknf(sknfprototype);
	index = calculator(number);
	cout << "Index : " << index << endl;
	cout << "F(" << index << ")(a,b,c) = V";
	numeral(sdnfprototype);
	cout << "F(" << index << ")(a,b,c) = A";
	numeral(sknfprototype);
}

int main()
{
	transformator();
}