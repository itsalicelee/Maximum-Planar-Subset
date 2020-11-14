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
vector< vector< vector<int> > > s;  // s is a 3d vector stores startpoint of output chords, every s[i][j] is a list 


for(int i = 0; i < n; ++i)  // initialize s table 
{
    vector< vector<int> > temp;
    s.push_back(temp);
    for(int j = 0;  j < n; ++j)
        {
            vector<int> temp2;
            s[i].push_back(temp2);
        }
}
//cout << "s:"<< s.size() << endl;

for(int d = 1; d < n; ++d)
{   
    for(int i = 0; i < n-d; ++i)
    {   
        
        int j = i + d;
        int k = data[j].second;

        if(k < i || k > j)
        {
            m[i][j] = m[i][j-1];
            s[i][j].assign(s[i][j-1].begin(), s[i][j-1].end());
        }
        else if (k == i)  
        {
            m[i][j] = m[i+1][j-1] + 1;
            s[i][j].assign(s[i+1][j-1].begin(), s[i+1][j-1].end());
            s[i][j].push_back(k);

        }
        else
        {
           
            if(m[i][j-1] < m[i][k-1]+ 1 + m[k+1][j-1])
            {
                m[i][j] = m[i][k-1]+ 1 + m[k+1][j-1];
                s[i][j].assign(s[i][k-1].begin(), s[i][k-1].end());
                s[i][j].insert(s[i][j].end(), s[k+1][j-1].begin(), s[k+1][j-1].end());
                s[i][j].push_back(k);
            }
            else
            {
                m[i][j] = m[i][j-1];
                s[i][j].assign(s[i][j-1].begin(), s[i][j-1].end());
            }
            
        }
    }
}

// cout << "m table" << endl;
// for(int i = 0; i < n; ++i)
// {   
//     for(int j = 0; j < n; ++j)
//         cout << m[i][j] << " ";
//     cout << endl;
// }

// cout << "s result" << endl;
// for(int i = 0; i < n; ++i)
// {   
//     for(int j = 0; j < n; ++j)
//     {   
//         cout << "size" << s[i][j].size() << endl;
//         for(int k = 0; k < s[i][j].size(); k++)
//             cout << "i " << i << ", j " << j  << ": " << s[i][j][k] << " " << endl;
//     }
//     cout << endl;
// }

vector<int> output(s[0][n-1]); // add the chord list to a new vector output
// for(int i = 0; i < output.size(); i++)
//     cout << output[i] << " ";
output.push_back(m[0][n-1]);  // add the total chord count to the last element

return output;
}
