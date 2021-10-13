#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

int priority(char symbol);
void translate(string& function);
bool summary(bool first, bool  second);
int from_binary_to(vector<bool> term);
bool decrypt_to_bool(string& function, vector<bool>& triple);

void sdnfprint(vector<vector<bool>>& sdnfprototype);
void sknfprint(vector<vector<bool>>& sknfprototype);
void truthtable(vector<bool>& answerstofunction);
void sdnf_sknf_to_numeral(vector<vector<bool>>& prototype);

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
	Result(vector<vector<bool>>sdnfprotatype, vector<vector<bool>>sknfprotatype) :
		sdnf(sdnfprotatype),
		sknf(sknfprotatype)
	{}
	vector<vector<bool>> GetSdnf()
	{
		return sdnf;
	}
	vector<vector<bool>> GetSknf()
	{
		return sknf;
	}
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
	bool operator== (Result& example)
	{
		if (example.number != number) return false;
		if (example.sdnf != sdnf) return false;
		if (example.sknf != sknf) return false;
		return true;
	}
};
Result transformator(string& name);

bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8();
bool Test9();
bool Test10();
bool Test11();
bool Test12();
bool Test13();
bool Test14();
bool Test15();
bool Test16();
bool Test17();
bool Test18();
bool Test19();
bool Test20();
bool Test21();
bool Test22();
bool Test23();
bool Test24();
bool Test25();
bool Test26();
bool Test27();
bool Test28();
bool Test29();
bool Test30();
int tests();
void our_own_input();
