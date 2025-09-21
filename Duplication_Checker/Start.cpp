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

    //文件输入
    DC::File_in(argc, argv, Ori_Addr, Cmp_Addr, Out_Addr, Ori_Text, Cmp_Text);
    //根据语言不同处理文档
    DC::Chinese_Process(Ori_Text, Cmp_Text);

    //通过核心查重函数 LCS 最长公共子序列 得到抄袭率
    rate = DC::LCS(Ori_Text, Cmp_Text);
    //答案为百分数形式 不带百分号
    rate *= 100;

    //文件输出同时控制输出小数点后两位
    DC::File_out(rate, Out_Addr);

    return 0;
}