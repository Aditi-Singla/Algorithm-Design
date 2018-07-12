#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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
		while(tempa[t]!='\0')
		{
			if (tempa[t] == '0')
				a.push_back(0);
			else
				a.push_back(1);
			t++;
		}
		
		in >> tempb;
		t = 0;
		while(tempb[t]!='\0')
		{
			if (tempb[t] == '0')
				b.push_back(0);
			else
				b.push_back(1);
			t++;
		}
	}
}

vector<int> getSubVector(vector<int> v, int left, int right){
	vector<int> ans;
	for (int i=left; i<right; i++){
		ans.push_back(v[i]);
	}
	return ans;
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

vector<int> twoComplement(vector<int> v, int l){
	for (int i=0; i<v.size(); i++){
		if (v[i]==0)
			v[i] = 1;
		else
			v[i] = 0;	
	}
	for (int i=l-v.size(); i>0; i--){
		v.insert(v.begin(),1);
	}
	vector<int> temp;
	temp.push_back(1);
	temp = add(v,temp);
	return temp;
}

vector<int> subtract(vector<int> v1, vector<int> v2){		////assume v1>v2
	vector<int> temp = add(v1,twoComplement(v2,v1.size()));
	return (getSubVector(temp,temp.size()-v1.size(),temp.size()));
}

vector<int> longmultiply(vector<int> a, vector<int> b){
	vector<int> sum;
	for (int i = b.size()-1; i>=0; i--){
		if (b[i] == 1){
			sum = add(sum,a);
			a.push_back(0);
		}
		else{
			a.push_back(0);
		}
	}
	return sum;
}

vector<int> karatsuba(vector<int> a1, vector<int> b1, int size){
	vector<int> ans;
	if (a1.size() < 5)
		return (longmultiply(a1,b1));
	else{
		vector<int> aL,aR,bL,bR,aLaR,bLbR,p,q,r;
		if (size%2 == 0){ 
			aL = getSubVector(a1,0,size/2);
			bL = getSubVector(b1,0,size/2);
			aR = getSubVector(a1,size/2,size);
			bR = getSubVector(b1,size/2,size);
			p = karatsuba(aL, bL, size/2);
			q = karatsuba(aR, bR, size/2);
			aLaR = add(aL,aR);
			bLbR = add(bL,bR);
			int n1 = aLaR.size() - bLbR.size();
			if (n1>0){
				while (n1>0){
					bLbR.insert(bLbR.begin(),0);
					n1--;
				}
				r = karatsuba(aLaR,bLbR,aLaR.size());
			}
			else{
				while (n1<0){
					aLaR.insert(aLaR.begin(),0);
					n1++;
				}
				r = karatsuba(aLaR,bLbR,bLbR.size());
			}
			vector<int> temp = subtract(r,add(p,q));
			for (int i=0;i<size;i++){
				p.push_back(0);
				if (i<size/2)
					temp.push_back(0);
			}
			temp = add(p,temp);
			temp = add(temp,q);
			return temp;
		}
		else{
			aL = getSubVector(a1,0,size/2+1);
			bL = getSubVector(b1,0,size/2+1);
			aR = getSubVector(a1,size/2+1,size);
			bR = getSubVector(b1,size/2+1,size);
			p = karatsuba(aL, bL, size/2 +1);
			q = karatsuba(aR, bR, size/2);
			aLaR = add(aL,aR);
			bLbR = add(bL,bR);
			int n1 = aLaR.size() - bLbR.size();
			if (n1>0){
				while (n1>0){
					bLbR.insert(bLbR.begin(),0);
					n1--;
				}
				r = karatsuba(aLaR,bLbR,aLaR.size());
			}
			else{
				while (n1<0){
					aLaR.insert(aLaR.begin(),0);
					n1++;
				}
				r = karatsuba(aLaR,bLbR,bLbR.size());
			}
			vector<int> temp = subtract(r,add(p,q));
			for (int i=0;i<size-1;i++){
				p.push_back(0);
				if (i<size/2)
					temp.push_back(0);
			}
			temp = add(p,temp);
			temp = add(temp,q);
			return temp;
		}	
	}	
}

void output(char filename[], vector<int> v){
	ofstream out(filename, ios::out);
	for (int  i = 0; i < v.size(); i++){
		out << v[i];
	}
	out << "\n";
	out.close();
}

int main(int argc, char * argv[]){
	char* infile = argv[1];
	char* outfile = argv[2];
	input(infile); 
	vector<int> product =  karatsuba(a,b,n);
	while (product[0] == 0 && product.size()>1){
		product.erase(product.begin());
	}
	output(outfile, product);
	return 0;
}
