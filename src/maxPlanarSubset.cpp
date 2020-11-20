#include<iostream>
#include"maxPlanarSubset.h"
using namespace std;

vector<int> findPair(vector< pair<int,int> >& data, int n)
{   
    /*Given input data and number of chords, fill in m table and s table 
    call the findChord function to  trace back the chords and return the result as a vector*/

    vector<vector<unsigned short> > m( n , vector<unsigned short> (n, 0));  // m is for storing count of chords
    vector<vector<char> > s( n , vector<char> (n, 1));  // s is for saving which case, initialize with case1

    for(size_t d = 1; d < n; ++d)
    {   
        for(size_t i = 0; i < n-d; ++i)
        {   
            int j = i + d;
            int k = data[j].second;

            if(k < i || k > j)  // case1: k is not in (i,j)
                m[i][j] = m[i][j-1];
            else if (k == i)  // case2: k is i, so we must choose k
            {
                m[i][j] = m[i+1][j-1] + 1;
                s[i][j] = 2;
            }
            else  
            {
                if(m[i][j-1] <= m[i][k-1]+ 1 + m[k+1][j-1]) // case3 (but what if m[i][j-1] = m[i][k-1]+ 1 + m[k+1][j-1])
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
    result.push_back(m[0][n-1]);  // add total chord count to the last element
    // free the memory space
    // for(int i = 0; i < m.size(); i++)
    //     vector<unsigned short>().swap(m[i]);
    // vector< vector<unsigned short> > ().swap(m);

    findChord(data, result, s, 0, n-1);  // find from (0,n-1) trace back the chord
    
    return result;
}

void findChord(vector< pair<int,int> >& data,  vector<int>& result, vector< vector<char> >& s, int i, int j)
{   /*Save the start point of the chord into result and recursively call itself*/
    //cout << "i: " << i << ", j: " << j << endl;
    while(s[i][j] == 1 && j > 0) // if case1: we dont want this j
        --j;

    if(i >= s.size() || j <= 0) // terminate condition
        return;
    unsigned short temp = j;
    if(s[i][j] == 2) // if case2: k is i, so we must choose k
    {
        result.push_back(temp);
        findChord(data, result, s,  i+1, j-1);    
    }
    
    else if(s[i][j] == 3)  // if case3: 
    {
        result.push_back(temp);
        findChord(data, result, s,  i, data[j].second-1);
        findChord(data, result, s, data[j].second + 1, j-1);
    }
    
}
