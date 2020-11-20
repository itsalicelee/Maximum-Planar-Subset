#include<vector>
#include<utility>
#include<algorithm>
#include<iostream>
using namespace std;

vector<int> findPair(vector< pair<int,int> >& data, int n);
void findChord(vector< pair<int,int> >& data, vector<int>& result,  vector<vector<char> >& s, int i, int j);
