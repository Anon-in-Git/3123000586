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
    static int ByteBundleLength(vs v, int i, int j) {
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
        return 1;
    }

    static void File_in(int argc, char* argv[], std::string& Ori_Addr, std::string& Cmp_Addr, std::string& Out_Addr, vs& Ori_Text, vs& Cmp_Text) {
        // cout << argc << endl;
        // for (int i = 0; i < argc; i++)
        //     cout << argv[i] << endl;
        if (argc != 4)
            return;
        for (int i = 0; argv[1][i]; i++)
            Ori_Addr.push_back(argv[1][i]);
        for (int i = 0; argv[2][i]; i++)
            Cmp_Addr.push_back(argv[2][i]);
        for (int i = 0; argv[3][i]; i++)
            Out_Addr.push_back(argv[3][i]);

        // cout << "Ori_Addr = " << Ori_Addr << endl;
        // cout << "Cmp_Addr = " << Cmp_Addr << endl;
        // cout << "Out_Addr = " << Out_Addr << endl;


        std::ifstream fin(Ori_Addr);
        std::string t;
        // cout << fin.is_open() << endl;
        if (fin.is_open()) {
            // cout << "!" << endl;
            // cout << t << endl;
            while (fin >> t) {
                // cout << "!" << endl;
                // cout << t << endl;
                Ori_Text.push_back(t);
            }
        }
        fin.close();
        fin.open(Cmp_Addr);
        // cout << fin.is_open() << endl;
        if (fin.is_open()) {
            // cout << '!' << endl;
            while (fin >> t) {
                // cout << "!" << endl;
                // cout << t << endl;
                Cmp_Text.push_back(t);
            }
        }
        fin.close();
    }

    static void Chinese_Process(vs& Ori_Text, vs& Cmp_Text) {
        vs replace;
        for (int i = 0; i < Ori_Text.size(); i++) {
            std::string t;
            for (int j = 0; j < Ori_Text[i].size(); j++) {
                int num = ByteBundleLength(Ori_Text, i, j);
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
                if (ispunct((uc)Ori_Text[i][j]) || isspace((uc)Ori_Text[i][j]) || Ori_Text[i][j] == '\n') {
                    if (!t.empty())
                        replace.push_back(t);
                    t.clear();
                    continue;
                }
                if (isupper((uc)Ori_Text[i][j]))
                    Ori_Text[i][j] = tolower(Ori_Text[i][j]);
                t.push_back(Ori_Text[i][j]);
            }
            if (!t.empty())
                replace.push_back(t);
        }
        Ori_Text = replace;
        replace.clear();

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

    static void File_out(double rate, const std::string& Out_Addr) {
        std::ofstream Ori_Out(Out_Addr);
        Ori_Out << std::fixed << std::setprecision(2) << rate;
        Ori_Out.close();
    }

    static double LCS(const vs& Ori_Text, const vs& Cmp_Text) {
        if (Ori_Text.empty() || Cmp_Text.empty())
            return 0;
        std::vector<std::vector<int>> dp(2, std::vector<int>(std::max(Ori_Text.size(), Cmp_Text.size()) + 10, 0));
        int t = 0;
        for (int i = 1; i <= Ori_Text.size(); i++, t ^= 1) {
            for (int j = 1; j <= Cmp_Text.size(); j++) {
                if (Ori_Text[i - 1] == Cmp_Text[j - 1])
                    dp[t ^ 1][j] = dp[t][j - 1] + 1;
                else
                    dp[t ^ 1][j] = std::max(dp[t][j], dp[t ^ 1][j - 1]);
                // cerr << dp[t ^ 1][j] << ' ';
            }
            // cerr << endl;
        }
        double ans = (double)dp[t][Cmp_Text.size()] / (double)Cmp_Text.size();
        // cerr << dp[t][Cmp_Text.size()] << endl;
        return ans;
    }

    void Test_LCS(vs& Ori_Text, vs& Cmp_Text) {
        // Ori_Text.emplace_back("I love you China! 我爱你中国！");
        Ori_Text.emplace_back("i");
        Ori_Text.emplace_back("love");
        Ori_Text.emplace_back("you");
        Ori_Text.emplace_back("China");

        // Cmp_Text.emplace_back("I love China! 我喜欢中国！");
        Cmp_Text.emplace_back("I");
        Cmp_Text.emplace_back("like");
        Cmp_Text.emplace_back("China");

        // cerr << "LCS: " << fixed << setprecision(2) << LCS(Ori_Text, Cmp_Text) << endl;
    }
};