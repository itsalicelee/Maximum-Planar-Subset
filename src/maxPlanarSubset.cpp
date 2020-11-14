#include<iostream>
#include"maxPlanarSubset.h"
using namespace std;

/*
TODO:
1. sometimes s[i][j] needs to assign(j), not k
    because we do not want to let chord (1,2) becomes(2,1)
2. find a new way to overcome memory problem! (no 3dim vector)
3. Using vector, it is better to use "reserve" than "push_back"(memory issue)
*/

vector<int> findPair(vector< pair<int,int> >& data, int n)
{
    vector<vector<int> > m( n , vector<int> (n, 0));  // m is for storing count of chords
    vector<vector<int> > s( n , vector<int> (n, 1));  // s is for saving which case, initialize with case1

    for(int d = 1; d < n; ++d)
    {   
        for(int i = 0; i < n-d; ++i)
        {   
            int j = i + d;
            int k = data[j].second;

            if(k < i || k > j)  // case1
                m[i][j] = m[i][j-1];
            else if (k == i)  // case2
            {
                m[i][j] = m[i+1][j-1] + 1;
                s[i][j] = 2;
            }
            else  
            {
                if(m[i][j-1] < m[i][k-1]+ 1 + m[k+1][j-1]) // case3(what if m[i][j-1] = m[i][k-1]+ 1 + m[k+1][j-1])
                {
                    m[i][j] = m[i][k-1]+ 1 + m[k+1][j-1];
                    s[i][j] = 3; 
                }
                else  // case1
                    m[i][j] = m[i][j-1];
            }
        }
    }

    vector<int> result;
    findChord(data, result, s, 0, n-1);  // find from (0,n-1), trace back the chord
    result.push_back(m[0][n-1]);  // add total chord count to the last element
    return result;
}

void findChord(vector< pair<int,int> >& data,  vector<int>& result, vector< vector<int> >& s, int i, int j)
{
    while(s[i][j] == 1 && j > 0) // if case1: we dont want this j
        j--;
    int size = s.size();

    if(i >= size || j <= 0) // terminate condition
        return;
    else
    {
        if(s[i][j] == 2) // if case2
        {
            result.push_back(j);
            findChord(data, result, s,  i+1, j-1);    
        }
        
        else if(s[i][j] == 3)  // if case3
        {
        result.push_back(j);
        findChord(data, result, s,  i, data[j].second-1);
        findChord(data, result, s, data[j].second + 1, j-1);
        }
    }
}
