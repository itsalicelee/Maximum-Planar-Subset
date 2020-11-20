// **************************************************************************
//  File       [main.cpp]
//  Author     [Pin-Hua Lee]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
//  Date       2020/11/14
// **************************************************************************

#include<iostream>
#include<fstream>
#include"maxPlanarSubset.h"
#include<utility>
#include "../lib/tm_usage.h"
using namespace std;


void help_message() {
    cout << "usage: ./bin/mps inputs/<input file> outputs/<output file>" << "\n";
}

int main(int argc, char* argv[])
{
    if (argc != 3){
        help_message(); 
        return 0;
    }
    CommonNs::TmUsage tmusg; 
    CommonNs::TmStat stat;
    //////////// read the input file /////////////
    
    //char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    int n;
    int start, junk, end;
    fin >> n;  // n = 2N - 1

    /*
    data is a vector which stores chord "pairs" like this
    0 1 2  3 4 5 6 7  8 9 10 11  
    4 9 6 10 0 7 2 5 11 1  3  8 
    Note: access element in pairs by using aPair.first, aPair.second
    */

   // store the input data as vectors and pair 
    vector< pair<int, int> > data(n);  
    for(size_t i = 0; i < n/2 ; ++i)
    {
        fin >> start >> end;
        data[start] = make_pair(start, end);
        data[end] = make_pair(end, start);
    }
    fin >> junk;

    //////////// algorithm start ////////////////
    tmusg.periodStart();
    vector<int> output = findPair(data, n);
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << "\n";
    

    //////////// write the output file ///////////

    int cnt = output.front();   // the first element in output is the number of output line
    output.erase(output.begin());  // delete the first element
    for(size_t i = 0; i < output.size(); ++i)
        output[i] = data[output[i]].second;
    sort(output.begin(), output.begin()+cnt);  // sort by the first element
    
    fout << cnt << endl;  // write in the total chord number

    for (size_t i = 0; i < output.size(); ++i) 
    {
        fout << output[i] << " " << data[output[i]].second << "\n";
    }
    fin.close();
    fout.close();
    
    return 0;
}
