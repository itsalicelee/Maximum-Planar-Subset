// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2019 fall Algorithm PA2]
// **************************************************************************

#include<iostream>
#include<fstream>
#include"maxPlanarSubset.h"
#include<utility>
#include "../lib/tm_usage.h"
using namespace std;


void help_message() {
    cout << "usage: ./bin/mps inputs/<input file> outputs/<output file>" << endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3){
        help_message(); 
        return 0;
    }
    CommonNs::TmUsage tmusg;  // for time usage 
    CommonNs::TmStat stat;
    //////////// read the input file /////////////
    
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    int n;
    int start, junk, end;
    fin >> n;  // n = 2N - 1
    vector< pair<int, int> > data(n);  

    // data is a vector which stores chord pairs
    // 0 1 2  3 4 5 6 7  8 9 10 11  
    // 4 9 6 10 0 7 2 5 11 1  3  8 

    for(int i = 0; i < n/2 ; i++)
    {
        pair<int, int> temp;
        fin >> start >> end;
        data[start] = make_pair(start, end);
        data[end] = make_pair(end, start);
    }
    fin >> junk;

    // cout << "initial data" << endl;
    // for (int i=0; i<n; i++) // print the data
    // { 
    //     // "first" and "second" are used to access 
    //     // 1st and 2nd element of pair respectively 
    //     cout << data[i].first << " "
    //          << data[i].second << endl; 
    // } 
    

    //////////// algorithm start ////////////////
    tmusg.periodStart();
    vector<int> output = findPair(data, n);

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    //cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    //////////// write the output file ///////////

    int cnt = output.back();   // the last element in output is the number of output line
    output.pop_back();
    //cout << output.size();
    sort(output.begin(), output.begin()+cnt);
    fout << cnt << endl;

    for (int i = 0; i < output.size(); i++) 
    {
        fout << output[i] << " " << data[output[i]].second << endl; // is the order correct??
    }
    fin.close();
    fout.close();
    return 0;

return 0;
}



/*
// Input
12 
0 4 
1 9
2 6 
3 10 
5 7 
8 11 
0
*/
