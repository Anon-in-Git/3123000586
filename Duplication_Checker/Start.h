#pragma once
#include<cmath>
#include<string>
#include<vector>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<iostream>
typedef std::vector<std::string> vs;
typedef unsigned char uc;

class DC {
public:
    //Distinguish UTF8-1 from UTF8-2, UTF8-3 and UTF8-4
    //分辨文本在UTF-8中多少个字符表示一个字
    static int ByteBundleLength(vs v, int i, int j) {
        //判断UTF8-2
        if (j + 1 < v[i].size()) {
            int t0, t1;
            if (v[i][j] < 0)
                t0 = 256 + v[i][j];
            else
                t0 = v[i][j];

            if (v[i][j + 1] < 0)
                t1 = 256 + v[i][j + 1];
            else
                t1 = v[i][j + 1];

            if (t0 >= 0xc2 && t0 <= 0xdf && t1 >= 0x80 && t1 <= 0xbf) {
                return 2;
            }
        }
        //判断UTF8-3
        if (j + 2 < v[i].size()) {
            int t0, t1, t2;
            if (v[i][j] < 0)
                t0 = 256 + v[i][j];
            else
                t0 = v[i][j];

            if (v[i][j + 1] < 0)
                t1 = 256 + v[i][j + 1];
            else
                t1 = v[i][j + 1];

            if (v[i][j + 2] < 0)
                t2 = 256 + v[i][j + 2];
            else
                t2 = v[i][j + 2];

            if (t0 == 0xe0 && t1 >= 0xa0 && t1 <= 0xbf && t2 >= 0x80 && t2 <= 0xbf)
                return 3;
            if (t0 >= 0xe1 && t0 <= 0xec && t1 >= 0x80 && t1 <= 0xbf && t2 >= 0x80 && t2 <= 0xbf)
                return 3;
            if (t0 == 0xed && t1 >= 0x80 && t1 <= 0x9f && t2 >= 0x80 && t2 <= 0xbf)
                return 3;
            if (t0 >= 0xee && t0 <= 0xef && t1 >= 0x80 && t1 <= 0xbf && t2 >= 0x80 && t2 <= 0xbf)
                return 3;
        }
        //判断UTF8-4
        if (j + 3 < v[i].size()) {
            int t0, t1, t2, t3;
            if (v[i][j] < 0)
                t0 = 256 + v[i][j];
            else
                t0 = v[i][j];

            if (v[i][j + 1] < 0)
                t1 = 256 + v[i][j + 1];
            else
                t1 = v[i][j + 1];

            if (v[i][j + 2] < 0)
                t2 = 256 + v[i][j + 2];
            else
                t2 = v[i][j + 2];

            if (v[i][j + 3] < 0)
                t3 = 256 + v[i][j + 3];
            else
                t3 = v[i][j + 3];

            if (t0 == 0xf0 && t1 >= 0x90 && t1 <= 0xbf && t2 >= 0x80 && t2 <= 0xbf && t3 >= 0x80 && t3 <= 0xbf)
                return 4;
            if (t0 >= 0xf1 && t0 <= 0xf3 && t1 >= 0x80 && t1 <= 0xbf && t2 >= 0x80 && t2 <= 0xbf && t3 >= 0x80 && t3 <= 0xbf)
                return 4;
            if (t0 == 0xf4 && t1 >= 0x80 && t1 <= 0x8f && t2 >= 0x80 && t2 <= 0xbf && t3 >= 0x80 && t3 <= 0xbf)
                return 4;
        }
        //判断UTF8-1
        return 1;
    }

    //文件输入
    static void File_in(int argc, char* argv[], std::string& Ori_Addr, std::string& Cmp_Addr, std::string& Out_Addr, vs& Ori_Text, vs& Cmp_Text) {
        //当命令行参数不为四个时，默认返回0
        if (argc != 4)
            return;
        //读入文件地址
        for (int i = 0; argv[1][i]; i++)
            Ori_Addr.push_back(argv[1][i]);
        for (int i = 0; argv[2][i]; i++)
            Cmp_Addr.push_back(argv[2][i]);
        for (int i = 0; argv[3][i]; i++)
            Out_Addr.push_back(argv[3][i]);

        //当文件无法打开或不存在时，默认返回0
        std::ifstream fin(Ori_Addr);
        std::string t;
        if (fin.is_open()) {
            while (fin >> t) {
                Ori_Text.push_back(t);
            }
        }
        fin.close();
        fin.open(Cmp_Addr);
        if (fin.is_open()) {
            while (fin >> t) {
                Cmp_Text.push_back(t);
            }
        }
        fin.close();
    }

    static void Chinese_Process(vs& Ori_Text, vs& Cmp_Text) {
        vs replace;
        //处理原文
        for (int i = 0; i < Ori_Text.size(); i++) {
            std::string t;
            for (int j = 0; j < Ori_Text[i].size(); j++) {
                int num = ByteBundleLength(Ori_Text, i, j);
                //如果一个字占了多个字符，将多个字符打包为一个string类型
                if (num >= 2) {
                    if (!t.empty())
                        replace.push_back(t);
                    t.clear();
                    for (int k = 0; k < num; k++)
                        t.push_back(Ori_Text[i][j + k]);
                    replace.push_back(t);
                    t.clear();
                    j += num - 1;
                    continue;
                }
                //英文一个单词结束时，将单词打包问一个string类型
                if (ispunct((uc)Ori_Text[i][j]) || isspace((uc)Ori_Text[i][j]) || Ori_Text[i][j] == '\n') {
                    if (!t.empty())
                        replace.push_back(t);
                    t.clear();
                    continue;
                }
                //英文默认大写转小写
                if (isupper((uc)Ori_Text[i][j]))
                    Ori_Text[i][j] = tolower(Ori_Text[i][j]);
                t.push_back(Ori_Text[i][j]);
            }
            if (!t.empty())
                replace.push_back(t);
        }
        Ori_Text = replace;
        replace.clear();

        //处理抄袭文本，方式与原文相同
        for (int i = 0; i < Cmp_Text.size(); i++) {
            std::string t;
            for (int j = 0; j < Cmp_Text[i].size(); j++) {
                int num = ByteBundleLength(Cmp_Text, i, j);
                if (num >= 2) {
                    if (!t.empty())
                        replace.push_back(t);
                    t.clear();
                    for (int k = 0; k < num; k++)
                        t.push_back(Cmp_Text[i][j + k]);
                    replace.push_back(t);
                    t.clear();
                    j += num - 1;
                    continue;
                }
                if (ispunct((uc)Cmp_Text[i][j]) || isspace((uc)Cmp_Text[i][j]) || Cmp_Text[i][j] == '\n') {
                    if (!t.empty())
                        replace.push_back(t);
                    t.clear();
                    continue;
                }
                if (isupper((uc)Cmp_Text[i][j]))
                    Cmp_Text[i][j] = tolower(Cmp_Text[i][j]);
                t.push_back(Cmp_Text[i][j]);
            }
            if (!t.empty())
                replace.push_back(t);
        }
        Cmp_Text = replace;
    }

    //文件输出
    static void File_out(double rate, const std::string& Out_Addr) {
        std::ofstream Ori_Out(Out_Addr);
        //输出控制为小数点后两位
        if(Ori_Out.is_open())
            Ori_Out << std::fixed << std::setprecision(2) << rate;
        Ori_Out.close();
    }

    //最长公共子序列
    static double LCS(const vs& Ori_Text, const vs& Cmp_Text) {
        if (Ori_Text.empty() || Cmp_Text.empty())
            return 0;
        //使用滚动数组节省占用空间
        std::vector<std::vector<int>> dp(2, std::vector<int>(std::max(Ori_Text.size(), Cmp_Text.size()) + 10, 0));
        int t = 0;
        //使用动态规划
        //i表示考虑到原文的第i位置
        //j表示考虑到抄袭文本的第j位置
        for (int i = 1; i <= Ori_Text.size(); i++, t ^= 1) {
            for (int j = 1; j <= Cmp_Text.size(); j++) {
                //dp转移方程
                if (Ori_Text[i - 1] == Cmp_Text[j - 1])
                    dp[t ^ 1][j] = dp[t][j - 1] + 1;
                else
                    dp[t ^ 1][j] = std::max(dp[t][j], dp[t ^ 1][j - 1]);
            }
        }
        //计算查重率
        double ans = (double)dp[t][Cmp_Text.size()] / (double)Cmp_Text.size();
        return ans;
    }

};