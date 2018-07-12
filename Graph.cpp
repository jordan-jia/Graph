#include<iostream>
#include<fstream>
#include <stdlib.h> 
using namespace std;
long long int A[500][500][500];
int R[500][500][500],num;
void path(ostream &fout, int start, int end){
	if (start == R[num][start][end]){
			fout << start << ' ';
			return;
	}
	path(fout, start, R[num][start][end]);
	path(fout, R[num][start][end], end);
}

int main(int argc, char* argv[]){
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);
	//fin.open("ex2.txt");
	//fout.open("output.txt");
	int start, end,cost;
	char first,last;
	bool negative_cycle=false;
	fin >> num;
	for (int i = 1; i <= num; i++){
		for (int j = 1; j <= num; j++){
			A[0][i][j] = 4294967294;
		}
	}
	while (1){
		fin >> first;
		if (first == '#')
			break;
		fin >> last;
		fin >> cost;
		A[0][int(first - '0')][int(last - '0')] = cost;
	}

	/*
	for (int i = 1; i <= num; i++){
		for (int j = 1; j <= num; j++){
			cout << A[0][i][j] << ' ';
		}
		cout << endl;
	}
	*/

	for (int i = 1; i <=num; i++){
		for (int j = 1; j <= num; j++){
			if (i == j || A[0][i][j] == 4294967294)
				R[0][i][j] = 0;
			else
				R[0][i][j] = i;
		}
	}
	
	for (int k = 1; k <= num; k++){
		for (int i = 1; i <= num; i++){
			for (int j = 1; j <= num; j++){
				if (i == j)
					A[k][i][j] = 0;
				else if (i == k || j == k)
					A[k][i][j] = A[k - 1][i][j];
				else{
					if ((A[k - 1][i][k] + A[k - 1][k][j]) < A[k - 1][i][j])
						A[k][i][j] = A[k - 1][i][k] + A[k - 1][k][j];
					else
						A[k][i][j] = A[k - 1][i][j];
				}

				if (A[k - 1][i][j] <= A[k - 1][i][k] + A[k - 1][k][j])
					R[k][i][j] = R[k - 1][i][j];
				else if (A[k - 1][i][j] > A[k - 1][i][k] + A[k - 1][k][j])
					R[k][i][j] = R[k - 1][k][j];
			}
		}
	}
	for (int i = 1; i <= num; i++){
		if (R[num][i][i] != 0)
			negative_cycle = true;
	}
	if (negative_cycle){
		fout << "Negative cycle" << endl;
	}
	else{
		while (fin >> start, fin >> end){
			if (A[num][start][end] > 2147483647){//無路徑
				fout << "No path" << endl;
				continue;
			}
			else{
				fout << A[num][start][end] << ' ';//有路徑
				path(fout, start, end);
				fout << end << endl;
			}
		}
	}
	fin.close();
	fout.close();
}