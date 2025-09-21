#include<cmath>
#include<string>
#include<vector>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<iostream>
#include "Start.h"
using namespace std;

int main(int argc, char* argv[]) {
    string Ori_Addr, Cmp_Addr, Out_Addr;
    vs Ori_Text, Cmp_Text;
    double rate = 0;

    DC::File_in(argc, argv, Ori_Addr, Cmp_Addr, Out_Addr, Ori_Text, Cmp_Text);
    // Test_LCS(Ori_Text, Cmp_Text);
    DC::Chinese_Process(Ori_Text, Cmp_Text);

    rate = DC::LCS(Ori_Text, Cmp_Text);
    rate *= 100;
    // cerr << fixed << setprecision(2) << rate << endl;
    DC::File_out(rate, Out_Addr);
    // cout << fixed << setprecision(2) << rate << endl;
    //system("pause");
    return 0;
}