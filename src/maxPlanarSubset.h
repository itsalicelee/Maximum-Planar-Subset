#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

vector<int> findPair(vector< pair<int,int> >& data, int n);
void findChord(vector< pair<int,int> >& data, vector<int>& result,  vector<vector<int> >& s, int i, int j);
