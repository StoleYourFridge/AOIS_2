#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

void deny_to_the_end(string& function)
{
	for (int i = 0; i < function.size(); i++)
	{
		if (function[i] == ' ') {
			function.erase(function.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < function.size(); i++)
	{
		if (function[i] == '!' && function[i + 1] == '(') {
			function.erase(function.begin() + i);
			stack<char>stack;
			stack.push('(');
			int index = i + 1;
			while (stack.size() != 0)
			{
				if (function[index] == '(') stack.push('(');
				else if (function[index] == ')') stack.pop();
				index++;
			}
			function.insert(function.begin() + index, '!');
		}
		else if (function[i] == '!' && (function[i + 1] == 'a' || function[i + 1] == 'b' || function[i + 1] == 'c')) {
			function.erase(function.begin() + i);
			function.insert(function.begin() + i + 1, '!');
		}
	}
}
void translate(string& function)
{
	deny_to_the_end(function);
	stack<char> stack;
	string result;
	for (int i = 0; i < function.size(); i++)
	{
		if (function[i] == 'a' || function[i] == 'b' || function[i] == 'c') {
			result.push_back(function[i]);
		}
		else if (function[i] == '!') result.push_back('!');
		else if (function[i] == ')') {
			while (stack.top() != '(')
			{
				result.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
			if (stack.size() != 0 && stack.top() == '*') {
				if (function[i + 1] != '!') {
					result.push_back('*');
					stack.pop();
				}
				else {
					result.push_back(function[i + 1]);
					result.push_back('*');
					stack.pop();
					i++;
				}
			}
		}
		else if (function[i] == '*') {
			if (function[i + 1] == 'a' || function[i + 1] == 'b' || function[i + 1] == 'c') {
				if (function[i + 2] != '!') {
					result.push_back(function[i + 1]);
					result.push_back(function[i]);
					i++;
				}
				else {
					result.push_back(function[i + 1]);
					result.push_back(function[i + 2]);
					result.push_back(function[i]);
					i += 2;
				}
			}
			else stack.push(function[i]);
				
		}
		else stack.push(function[i]);
	}
	while (!stack.empty())
	{
		result.push_back(stack.top());
		stack.pop();
	}
	function = result;
}

int priority(char symbol)
{
	if (symbol == '!') return 4;
	else if (symbol == '*') return 3;
	else if (symbol == '+') return 2;
	return 1;
}
void translate2(string& function)
{
	string result;
	stack<char>stack;
	for (int i = 0; i < function.size(); i++)
	{
		if (function[i] == 'a' || function[i] == 'b' || function[i] == 'c') {
			result.push_back(function[i]);
		}
		else if (function[i] == '(') stack.push(function[i]);
		else if (function[i] == ')') {
			while (stack.top() != '(')
			{
				result.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
		}
		else if (function[i] == '!') stack.push(function[i]);
		else if (function[i] == '+' || function[i] == '*') {
			while (priority(stack.top()) >= priority(function[i])) {
				result.push_back(stack.top());
				stack.pop();
			}
			stack.push(function[i]);
		}
	}
	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}
	function = result;
}

bool summary(bool first, bool  second)
{
	if (first && second) return true;
	else return (first + second);
}
int from_binary_to(vector<bool> term)
{
	int result = 0, index = term.size()  - 1;
	for (int i = 0; i < term.size(); i++)
	{
		result += term[i] * pow(2, index);
		index--;
	}
	return result;
}
bool decrypt_to_bool(string& function, vector<bool>& triple)
{
	stack<bool>result;
	bool first, second;
	for (int i = 0; i < function.size(); i++)
	{
		if (function[i] == 'a') result.push(triple[0]);
		else if (function[i] == 'b') result.push(triple[1]);
		else if (function[i] == 'c') result.push(triple[2]);
		else if (function[i] == '!') {
			first = result.top();
			result.pop();
			result.push(!first);
		}
		else if (function[i] == '+') {
			first = result.top();
			result.pop();
			second = result.top();
			result.pop();
			result.push(summary(first, second));
		}
		else if (function[i] == '*') {
			first = result.top();
			result.pop();
			second = result.top();
			result.pop();
			result.push(first * second);
		}
	}
	return result.top();
}

void sdnfprint(vector<vector<bool>>& sdnfprototype)
{
	cout << "F(sdnf)(a,b,c) = ";
	for (int i = 0; i < sdnfprototype.size(); i++)
	{
		cout << "(";
		if (sdnfprototype[i][0]) cout << "a*";
		else cout << "!a*";
		if (sdnfprototype[i][1]) cout << "b*";
		else cout << "!b*";
		if (sdnfprototype[i][2]) cout << "c";
		else cout << "!c";
		cout << ")";
		if (i != (sdnfprototype.size() - 1)) cout << " + ";
		
	}
	cout << ";" << endl;
}
void sknfprint(vector<vector<bool>>& sknfprototype)
{
	cout << "F(sknf)(a,b,c) = ";
	for (int i = 0; i < sknfprototype.size(); i++)
	{
		cout << "(";
		if (!sknfprototype[i][0]) cout << "a+";
		else cout << "!a+";
		if (!sknfprototype[i][1]) cout << "b+";
		else cout << "!b+";
		if (!sknfprototype[i][2]) cout << "c";
		else cout << "!c";
		cout << ")";
		if (i != (sknfprototype.size() - 1)) cout << " * ";
	}
	cout << ";" << endl;
}
void truthtable(vector<bool>& answerstofunction)
{
	cout << "Truth table : " << endl << "------------------------------------------" << endl
		<< "a      : | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 1 |" << endl
		<< "b      : | 0 | 0 | 1 | 1 | 0 | 0 | 1 | 1 |" << endl
		<< "c      : | 0 | 1 | 0 | 1 | 0 | 1 | 0 | 1 |" << endl
		<< "------------------------------------------" << endl << "result : |";
	for (int i = 0; i < answerstofunction.size(); i++)
	{
		cout << " " << answerstofunction[i] << " |";
	}
	cout << endl << "------------------------------------------" << endl;
}
void sdnf_sknf_to_numeral(vector<vector<bool>>& prototype)
{
	cout << "(";
	for (int i = 0; i < prototype.size(); i++)
	{
		cout << from_binary_to(prototype[i]);
		if (i != prototype.size() - 1) cout << ",";
	}
	cout << ");" << endl;
}

class Result  
{
	vector<vector<bool>> sdnf;
	vector<vector<bool>> sknf;
	vector<bool>number;
public:	
	Result(vector<vector<bool>>sdnfprotatype, vector<vector<bool>>sknfprotatype, vector<bool>numberprotatype) : 
		sdnf(sdnfprotatype), 
		sknf(sknfprotatype),  
		number(numberprotatype)
	{}
	void print()
	{
		truthtable(number);
		sdnfprint(sdnf);
		sknfprint(sknf);
		int index = from_binary_to(number);
		cout << "Index : " << index << endl;
		cout << "F(" << index << ")(a,b,c) = V";
		sdnf_sknf_to_numeral(sdnf);
		cout << "F(" << index << ")(a,b,c) = A";
		sdnf_sknf_to_numeral(sknf);
	}
	bool operator== (Result &example)
	{
		if (example.number != number) return false;
		if (example.sdnf != sdnf) return false;
		if (example.sknf != sknf) return false;
		return true;
	}
};
Result transformator(string& name)
{
	vector<vector<bool>> data { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
	vector<vector<bool>> sdnfprototype;
	vector<vector<bool>> sknfprototype;
	vector<bool>number;
	translate2(name);
	int index;
	for (int i = 0; i < data.size(); i++)
	{
		if (decrypt_to_bool(name, data[i])) {
			sdnfprototype.push_back(data[i]);
			number.push_back(1);
		}
		else {
			sknfprototype.push_back(data[i]);
			number.push_back(0);
		}
	}
	Result output(sdnfprototype, sknfprototype, number);
	return output;
}

bool Test1()
{
	string function = "!((!a+!b)*!(!a*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,1,0}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {0,1,1}, {1,0,0}, {1,0,1} };
	vector<bool>numberexample{1,0,1,0,0,0,1,1};
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 1 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 1 incorrect!" << endl;
		return false;
	}
}
bool Test2()
{
	string function = "!((!a+!b)*!(!a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {0,1,1}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,1,0}, {1,0,0}, {1,0,1} };
	vector<bool>numberexample{ 0,1,0,1,0,0,1,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 2 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 2 incorrect!" << endl;
		return false;
	}
}
bool Test3()
{
	string function = "!((!a+b)*!(!a*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,1,0}, {1,0,0}, {1,0,1} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {0,1,1}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 1,0,1,0,1,1,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 3 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 3 incorrect!" << endl;
		return false;
	}
}
bool Test4()
{
	string function = "!((!a+b)*!(!a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {0,1,1}, {1,0,0}, {1,0,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,1,0}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 0,1,0,1,1,1,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 4 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 4 incorrect!" << endl;
		return false;
	}
}
bool Test5()
{
	string function = "!((a+!b)*!(a*!c))";
	vector<vector<bool>>sdnfexample{ {0,1,0}, {0,1,1}, {1,0,0}, {1,1,0} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {1,0,1}, {1,1,1} };
	vector<bool>numberexample{ 0,0,1,1,1,0,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 5 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 5 incorrect!" << endl;
		return false;
	}
}
bool Test6()
{
	string function = "!((a+!b)*!(a*c))";
	vector<vector<bool>>sdnfexample{ {0,1,0}, {0,1,1}, {1,0,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {1,0,0}, {1,1,0} };
	vector<bool>numberexample{ 0,0,1,1,0,1,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 6 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 6 incorrect!" << endl;
		return false;
	}
}
bool Test7()
{
	string function = "!((a+b)*!(a*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {1,0,0}, {1,1,0} };
	vector<vector<bool>>sknfexample{ {0,1,0}, {0,1,1}, {1,0,1}, {1,1,1} };
	vector<bool>numberexample{ 1,1,0,0,1,0,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 7 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 7 incorrect!" << endl;
		return false;
	}
}
bool Test8()
{
	string function = "!((a+b)*!(a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {1,0,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,1,0}, {0,1,1}, {1,0,0}, {1,1,0} };
	vector<bool>numberexample{ 1,1,0,0,0,1,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 8 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 8 incorrect!" << endl;
		return false;
	}
}
bool Test9()
{
	string function = "!((!a+!b)*!(!b*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {1,0,0}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {0,1,0}, {0,1,1}, {1,0,1} };
	vector<bool>numberexample{ 1,0,0,0,1,0,1,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 9 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 9 incorrect!" << endl;
		return false;
	}
}
bool Test10()
{
	string function = "!((!a+!b)*!(!b*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {1,0,1}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,1,0}, {0,1,1}, {1,0,0} };
	vector<bool>numberexample{ 0,1,0,0,0,1,1,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 10 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 10 incorrect!" << endl;
		return false;
	}
}
bool Test11()
{
	string function = "!((!a+b)*!(b*!c))";
	vector<vector<bool>>sdnfexample{ {0,1,0}, {1,0,0}, {1,0,1}, {1,1,0} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {0,1,1}, {1,1,1} };
	vector<bool>numberexample{ 0,0,1,0,1,1,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 11 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 11 incorrect!" << endl;
		return false;
	}
}
bool Test12()
{
	string function = "!((!a+b)*!(b*c))";
	vector<vector<bool>>sdnfexample{ {0,1,1}, {1,0,0}, {1,0,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {0,1,0}, {1,1,0} };
	vector<bool>numberexample{ 0,0,0,1,1,1,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 12 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 12 incorrect!" << endl;
		return false;
	}
}
bool Test13()
{
	string function = "!((a+!b)*!(!b*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,1,0}, {0,1,1}, {1,0,0} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {1,0,1}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 1,0,1,1,1,0,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 13 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 13 incorrect!" << endl;
		return false;
	}
}
bool Test14()
{
	string function = "!((a+!b)*!(!b*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {0,1,0}, {0,1,1}, {1,0,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {1,0,0}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 0,1,1,1,0,1,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 14 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 14 incorrect!" << endl;
		return false;
	}
}
bool Test15()
{
	string function = "!((a+b)*!(b*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {0,1,0}, {1,1,0} };
	vector<vector<bool>>sknfexample{ {0,1,1}, {1,0,0}, {1,0,1}, {1,1,1} };
	vector<bool>numberexample{ 1,1,1,0,0,0,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 15 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 15 incorrect!" << endl;
		return false;
	}
}
bool Test16()
{
	string function = "!((a+b)*!(b*c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {0,1,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,1,0}, {1,0,0}, {1,0,1}, {1,1,0} };
	vector<bool>numberexample{ 1,1,0,1,0,0,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 16 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 16 incorrect!" << endl;
		return false;
	}
}
bool Test17()
{
	string function = "!((!b+!c)*!(!a*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,1,0}, {0,1,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {1,0,0}, {1,0,1}, {1,1,0} };
	vector<bool>numberexample{ 1,0,1,1,0,0,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 17 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 17 incorrect!" << endl;
		return false;
	}
}
bool Test18()
{
	string function = "!((!b+c)*!(!a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {0,1,0}, {0,1,1}, {1,1,0} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {1,0,0}, {1,0,1}, {1,1,1} };
	vector<bool>numberexample{ 0,1,1,1,0,0,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 18 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 18 incorrect!" << endl;
		return false;
	}
}
bool Test19()
{
	string function = "!((b+!c)*!(!a*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {0,1,0}, {1,0,1} };
	vector<vector<bool>>sknfexample{ {0,1,1}, {1,0,0}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 1,1,1,0,0,1,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 19 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 19 incorrect!" << endl;
		return false;
	}
}
bool Test20()
{
	string function = "!((b+c)*!(!a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {0,1,1}, {1,0,0} };
	vector<vector<bool>>sknfexample{ {0,1,0}, {1,0,1}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 1,1,0,1,1,0,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 20 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 20 incorrect!" << endl;
		return false;
	}
}
bool Test21()
{
	string function = "!((!b+!c)*!(a*!c))";
	vector<vector<bool>>sdnfexample{ {0,1,1}, {1,0,0}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {0,1,0}, {1,0,1} };
	vector<bool>numberexample{ 0,0,0,1,1,0,1,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 21 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 21 incorrect!" << endl;
		return false;
	}
}
bool Test22()
{
	string function = "!((!b+c)*!(a*!c))";
	vector<vector<bool>>sdnfexample{ {0,1,0}, {1,0,0}, {1,1,0}};
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,1} };
	vector<bool>numberexample{ 0,0,1,0,1,0,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 22 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 22 incorrect!" << endl;
		return false;
	}
}
bool Test23()
{
	string function = "!((b+!c)*!(a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {1,0,1}, {1,1,1}};
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,1,0}, {0,1,1}, {1,0,0}, {1,1,0} };
	vector<bool>numberexample{ 0,1,0,0,0,1,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 23 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 23 incorrect!" << endl;
		return false;
	}
}
bool Test24()
{
	string function = "!((b+c)*!(a*c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {1,0,0}, {1,0,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {0,1,0}, {0,1,1}, {1,1,0} };
	vector<bool>numberexample{ 1,0,0,0,1,1,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 24 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 24 incorrect!" << endl;
		return false;
	}
}
bool Test25()
{
	string function = "!((!a+!c)*!(!b*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {1,0,0}, {1,0,1}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,1}, {0,1,0}, {0,1,1}, {1,1,0} };
	vector<bool>numberexample{ 1,0,0,0,1,1,0,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 25 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 25 incorrect!" << endl;
		return false;
	}
}
bool Test26()
{
	string function = "!((!a+c)*!(!b*c))";
	vector<vector<bool>>sdnfexample{ {0,0,1}, {1,0,0}, {1,0,1}, {1,1,0} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,1,0}, {0,1,1}, {1,1,1} };
	vector<bool>numberexample{ 0,1,0,0,1,1,1,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 26 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 26 incorrect!" << endl;
		return false;
	}
}
bool Test27()
{
	string function = "!((!a+!c)*!(b*!c))";
	vector<vector<bool>>sdnfexample{ {0,1,0}, {1,0,1}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {0,1,1}, {1,0,0} };
	vector<bool>numberexample{ 0,0,1,0,0,1,1,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 27 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 27 incorrect!" << endl;
		return false;
	}
}
bool Test28()
{
	string function = "!((!a+c)*!(b*c))";
	vector<vector<bool>>sdnfexample{ {0,1,1}, {1,0,0}, {1,1,0}, {1,1,1} };
	vector<vector<bool>>sknfexample{ {0,0,0}, {0,0,1}, {0,1,0}, {1,0,1} };
	vector<bool>numberexample{ 0,0,0,1,1,0,1,1 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 28 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 28 incorrect!" << endl;
		return false;
	}
}
bool Test29()
{
	string function = "!((a+!c)*!(!b*!c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {0,1,1}, {1,0,0} };
	vector<vector<bool>>sknfexample{ {0,1,0}, {1,0,1}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 1,1,0,1,1,0,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 29 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 29 incorrect!" << endl;
		return false;
	}
}
bool Test30()
{
	string function = "!((a+c)*!(!b*c))";
	vector<vector<bool>>sdnfexample{ {0,0,0}, {0,0,1}, {0,1,0}, {1,0,1} };
	vector<vector<bool>>sknfexample{ {0,1,1}, {1,0,0}, {1,1,0}, {1,1,1} };
	vector<bool>numberexample{ 1,1,1,0,0,1,0,0 };
	Result example(sdnfexample, sknfexample, numberexample), output = transformator(function);
	if (example == output) {
		cout << "Test 30 correct!" << endl;
		return true;
	}
	else {
		cout << "Test 30 incorrect!" << endl;
		return false;
	}
}
int tests()
{
	int counter = 0;
	counter += Test1();
	counter += Test2();
	counter += Test3();
	counter += Test4();
	counter += Test5();
	counter += Test6();
	counter += Test7();
	counter += Test8();
	counter += Test9();
	counter += Test10();
	counter += Test11();
	counter += Test12();
	counter += Test13();
	counter += Test14();
	counter += Test15();
	counter += Test16();
	counter += Test17();
	counter += Test18();
	counter += Test19();
	counter += Test20();
	counter += Test21();
	counter += Test22();
	counter += Test23();
	counter += Test24();
	counter += Test25();
	counter += Test26();
	counter += Test27();
	counter += Test28();
	counter += Test29();
	counter += Test30();
	cout << "Tests passed : " << counter << endl;
	if (counter == 30) cout << "(All tests passed correctly)!" << endl;
	return counter;
}
void our_own_input()
{
	string functionname;
	cout << "Enter your function : ";
	getline(cin, functionname);
	transformator(functionname).print();
}

int main()
{
	tests();
}