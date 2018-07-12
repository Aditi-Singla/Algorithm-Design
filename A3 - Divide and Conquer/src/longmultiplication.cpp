#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
using namespace std;

int n;
vector<int> a;
vector<int> b;
vector<int> sum;

//function to take input - read from console by redirection
void input(char filename[]){
	string tempa,tempb;
	ifstream in;
	in.open(filename);
	if (!in.is_open()){
		cout << "File not found.\n";
	}
	else{
		in >> n;
		in >> tempa;
		int t = 0;
		bool check = true;
		while(tempa[t]!='\0')
		{
			if (check && tempa[t]=='0'){
				t++;				
				continue;
			}
			else{
				check = false;				
				if (tempa[t] == '0')
					a.push_back(0);
				else
					a.push_back(1);
				t++;
			}
		}
		if (check){
			a.push_back(0);
		}
		
		in >> tempb;
		t = 0;
		check = true;
		while(tempb[t]!='\0')
		{
			if (check && tempb[t]=='0'){
				t++;				
				continue;
			}
			else{
				check = false;				
				if (tempb[t] == '0')
					b.push_back(0);
				else
					b.push_back(1);
				t++;
			}
		}
		if (check){
			b.push_back(0);
		}
	}
}

vector<int> add(vector<int> v1, vector<int> v2){
	int index1 = v1.size()-1;
	int index2 = v2.size()-1;
	int s = 0;
	int c = 0;
	vector<int> sum;
	while (index1 >= 0 && index2 >= 0){
		if (v1[index1]==1 && v2[index2]==1){
			s = (c==1?1:0);
			c = 1;
		}
		else if (v1[index1]==0 && v2[index2]==1){
			s = (c==1?0:1);
			c = (c==1?1:0);
		}
		else if (v1[index1]==1 && v2[index2]==0){
			s = (c==1?0:1);
			c = (c==1?1:0);
		}
		else{
			s = (c==1?1:0);
			c = 0;
		}
		index1--;
		index2--;
		sum.push_back(s);
	}	
	while (index1 >= 0){
		if (c == 1){
			if (v1[index1] == 1){
				sum.push_back(0);
				index1--;	
			}
			else{
				sum.push_back(1);
				c = 0;
				index1--;
			}
		}
		else{
			sum.push_back(v1[index1]);
			index1--;
		}	
	}
	while (index2 >= 0){
		if (c == 1){
			if (v2[index2] == 1){
				sum.push_back(0);
				index2--;	
			}
			else{
				sum.push_back(1);
				c = 0;
				index2--;
			}
		}
		else{
			sum.push_back(v2[index2]);
			index2--;
		}
	}
	if (c == 1)
		sum.push_back(1);
	reverse(sum.begin(),sum.end());
	return sum;	
}

void longmultiply(){
	for (int i = b.size()-1; i>=0; i--){
		if (b[i] == 1){
			sum = add(sum,a);
			a.push_back(0);
		}
		else{
			a.push_back(0);
		}
	}
}

void output(char filename[]){
	ofstream out(filename, ios::out);
	for (int  i = 0; i < sum.size(); i++){
		out << sum[i];
	}
	out << "\n";
	out.close();
}

int main(int argc, char * argv[]){
	char* infile = argv[1];
	char* outfile = argv[2];
	input(infile);
	longmultiply();
	output(outfile);
	return 0;
}
