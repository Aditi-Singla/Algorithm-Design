#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_set>
#define max1 10000
using namespace std;

int n;
int sizeA;
int sizeB;
vector<vector<int>> input_map;
map<int,vector<int>> graph;
vector<int> B_set;
unordered_set<int> used;

//function to take input - read from console by redirection
void input(char filename[]){
	string tempa;
	ifstream in;
	in.open(filename);
	sizeA = 0;
	sizeB = 0;
	if (!in.is_open()){
		cout << "File not found.\n";
	}
	else{
		in >> n;
		for (int i=0; i<n; i++){
			in >> tempa;
			vector<int> a;
			for (int j=0; j<n; j++){
				a.push_back((tempa[j]-'0'));
			}
			input_map.push_back(a);
		}
	}
}
int giveId(int x, int y){
	return ((n*x) + (y+1));
}

string getCoordinates(int id){
	if (id>0){
		string st = "(";
		if (id%n==0)
			st += to_string(id/n);
		else
			st += to_string((id/n)+1);
		st += ",";
		if (id%n==0)
			st += to_string(n);
		else
			st += to_string(id%n);
		st += ")";
		return st; 
	}
	else
		return "";
}

vector<int> giveNeighbours(int x, int y){
	vector<int> list;
	if (x == 0){
		if (y == 0){
			if (n>1){
				if (input_map[x][y+1] == 1)
					list.push_back(giveId(x,y+1));
				if (input_map[x+1][y] == 1)
					list.push_back(giveId(x+1,y));
			}
		}
		else if (y == n-1){
			if (n>1){
				if (input_map[x][y-1] == 1)
					list.push_back(giveId(x,y-1));
				if (input_map[x+1][y] == 1)
					list.push_back(giveId(x+1,y));
			}
		}
		else{
			if (input_map[x][y-1] == 1)
				list.push_back(giveId(x,y-1));
			if (input_map[x][y+1] == 1)
				list.push_back(giveId(x,y+1));
			if (input_map[x+1][y] == 1)
				list.push_back(giveId(x+1,y)); 
		}
	}
	else if (x == n-1){
		if (y == 0){
			if (n>1){
				if (input_map[x-1][y] == 1)
					list.push_back(giveId(x-1,y)); 
				if (input_map[x][y+1] == 1)
					list.push_back(giveId(x,y+1));
			}
		}
		else if (y == n-1){
			if (n>1){
				if (input_map[x-1][y] == 1)
					list.push_back(giveId(x-1,y));
				if (input_map[x][y-1] == 1)
					list.push_back(giveId(x,y-1));
			}
		}
		else{
			if (input_map[x-1][y] == 1)
				list.push_back(giveId(x-1,y));
			if (input_map[x][y-1] == 1)
				list.push_back(giveId(x,y-1));
			if (input_map[x][y+1] == 1)
				list.push_back(giveId(x,y+1));
		}
	}
	else{
		if (y == 0){
			if (input_map[x-1][y] == 1)
				list.push_back(giveId(x-1,y));
			if (input_map[x][y+1] == 1)
				list.push_back(giveId(x,y+1));
			if (input_map[x+1][y] == 1)
				list.push_back(giveId(x+1,y)); 
		}
		else if (y == n-1){
			if (input_map[x-1][y] == 1)
				list.push_back(giveId(x-1,y));
			if (input_map[x][y-1] == 1)
				list.push_back(giveId(x,y-1));
			if (input_map[x+1][y] == 1)
				list.push_back(giveId(x+1,y)); 
		}
		else{
			if (input_map[x-1][y] == 1)
				list.push_back(giveId(x-1,y));
			if (input_map[x][y-1] == 1)
				list.push_back(giveId(x,y-1));
			if (input_map[x][y+1] == 1)
				list.push_back(giveId(x,y+1));
			if (input_map[x+1][y] == 1)
				list.push_back(giveId(x+1,y)); 
		}
	}
	return list;
}

void convertToBipartite(){
	vector<int> a;
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (input_map[i][j] == 1 && (i+j)%2==0){
				sizeA++;
				a.push_back(giveId(i,j));
				graph[giveId(i,j)] = giveNeighbours(i,j);
			}
			else if (input_map[i][j] == 1 && (i+j)%2==1){
				B_set.push_back(giveId(i,j));
				sizeB++;
				vector<int> b;
				b.push_back(0);
				graph[giveId(i,j)] = b;
			} 
		}
	}
	graph[-1] = a;
}

bool dfs(int s, int t){
	if (s == t)
		return true;
	unordered_set<int>::iterator it = used.find(s);
	if (it != used.end()){
		return false;
	}
	used.insert(s);
	vector<int> list = graph[s];
	for (vector<int>::iterator it1 = list.begin(); it1 != list.end(); ++it1){
		if (dfs(*it1,t)){
			graph[s].erase(std::remove(graph[s].begin(), graph[s].end(), *it1), graph[s].end());
			graph[*it1].push_back(s);
			return true;
		}
	}
	return false;
}

int max_flow(int s, int t){
	int flow = 0;
	while (dfs(s, t)){
		flow++;                      
		used.clear();
	}
	return flow;
}

void output(char filename[], int ans){
	ofstream out(filename, ios::out);
	out << ans;
	out << "\n";
	out.close();
}

void output(char filename[], string ans){
	ofstream out(filename, ios::app);
	out << ans;
	out << "\n";
	out.close();
}

int main(int argc, char * argv[]){
	char* infile = argv[1];
	char* outfile = argv[2];
	input(infile);
	convertToBipartite();
	if (sizeA != sizeB){
		output(outfile, 0);
		return 0;
	}
	int maxFlow = max_flow(-1,0);
	cout << "MaxFlow : " << maxFlow << endl;
	if (maxFlow == sizeA){
		output(outfile, 1);
		for (std::vector<int>::iterator it = B_set.begin(); it != B_set.end(); ++it){
			output(outfile, getCoordinates(*it)+getCoordinates(graph[*it][0]));
		}
	}
	else{
		output(outfile, 0);
	}

	///////////////////////////////////////////
	// Checking purposes : Print the graph
	///////////////////////////////////////////

	// cout << n << endl;
	// for (int i=0; i<n; i++){
	// 	for (int j=0; j<n; j++){
	// 		cout << input_map[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << "Bipartite : " << endl;
	// for (std::map<int,unordered_set<int>>::iterator it = graph.begin(); it != graph.end(); ++it){
	// 	cout << it->first << " -> ";
	// 	for ( auto itr = (it->second).begin(); itr != (it->second).end(); ++itr ){
	// 		std::cout << " " << *itr;
	// 	}
	// 	cout << endl;
	// }
	// output(ans);
	return 0;
}
