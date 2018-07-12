#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define max1 10000
using namespace std;

int n;
int k;
int table[max1][max1];
int table1[max1][max1];

//function to take input - read from console by redirection
void input(char filename[]){
	string tempa,tempb;
	ifstream in;
	in.open(filename);
	if (!in.is_open()){
		cout << "File not found.\n";
	}
	else{
		in >> tempa;
		int t = 0;
		int j = 0;
		char ch[max1];
		while(tempa[t]!=',')
		{
			ch[j]=tempa[t];
			j++;t++;
		}
		ch[j]='\0';
		n = atoi(ch);
		
		t++;
		j = 0;
		char ch1[max1];
		while(tempa[t]!='\0')
		{
			ch1[j]=tempa[t];
			j++;t++;
		}
		ch1[j]='\0';
		k = atoi(ch1);
	}
}

int maxTrialsClassic(int n1,int k1){
	//cout << table[n1-1][k1-1];
	if (k1==0 || n1==0)
		return 0;
	if (table1[n1-1][k1-1] != -1)
		return table1[n1-1][k1-1]; 
	if (n1 == 1){
		table1[0][k1-1] = 1;
		return 1;
	}
	if (k1 == 1){
		table1[n1-1][k1-1] = n1;
		return (n1);
	}
	int minimum = n1;
	for (int i = 2; i <= n1; i++)
		minimum = std::min(minimum,(1+ std::max(maxTrialsClassic(n1-i,k1),maxTrialsClassic(i-1,k1-1))));
	table1[n1-1][k1-1] = minimum;
	return minimum;
}

int maxTrials(int n1,int k1){
	//cout << table[n1-1][k1-1];
	if (k1==0 || n1==0)
		return 0;
	if (table[n1-1][k1-1] != -1)
		return table[n1-1][k1-1]; 
	if (n1 == 1){
		table[0][k1-1] = 0;
		return 0;
	}
	if (k1 == 1){
		table[n1-1][k1-1] = n1-1;
		return (n1-1);
	}
	int minimum = n1-1;
	for (int i = 2; i < n1; i++)
		minimum = std::min(minimum,(1+ std::max(maxTrials(n1-i,k1),maxTrialsClassic(i-1,k1-1))));
	table[n1-1][k1-1] = minimum;
	return minimum;
}

void output(char filename[], int ans){
	ofstream out(filename, ios::out);
	out << ans;
	out << "\n";
	out.close();
}

int main(int argc, char * argv[]){
	char* infile = argv[1];
	char* outfile = argv[2];
	input(infile);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < k; j++){
			table[i][j] = -1;
			table1[i][j] = -1;
		}
	}
	int ans = maxTrials(n,k);
	output(outfile, ans);
	return 0;
}
