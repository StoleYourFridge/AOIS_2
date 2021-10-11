#include <iostream>
#include <vector>
#include <cmath>

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

int translate(vector<bool> term)
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
		cout << translate(term[i]);
		if (i != term.size() - 1) cout << ",";
	}
	cout << ");" << endl;
}

pair<vector<vector<bool>>, vector<vector<bool>>> transformator()
{
	vector<vector<bool>> data { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
	vector<vector<bool>> sdnfprototype;
	vector<vector<bool>> sknfprototype;
	vector<bool>number;
	int index;
	for (int i = 0; i < data.size(); i++)
	{
		if (function(data[i])) {
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
	index = translate(number);
	cout << "Index : " << index << endl;
	cout << "F(" << index << ")(a,b,c) = V";
	numeral(sdnfprototype);
	cout << "F(" << index << ")(a,b,c) = A";
	numeral(sknfprototype);
	pair<vector<vector<bool>>, vector<vector<bool>>> result(sdnfprototype, sknfprototype);
	return result;
}

int main()
{
	/*sdnf(transformator().first);
	cout << endl << endl << "----------------" << endl << endl;
	sknf(transformator().second);*/
	transformator();
}