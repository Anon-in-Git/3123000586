#include<cmath>
#include<string>
#include<vector>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<iostream>
using namespace std;
typedef vector<string> vs;
typedef unsigned char uc;

//Distinguish UTF8-1 from UTF8-2, UTF8-3 and UTF8-4
int ByteBundleLength(vs v, int i, int j) {
    if ((uc)v[i][j] >= 0xc2 && (uc)v[i][j] <= 0xdf && j + 1 < (uc)v[i].size() && (uc)v[i + 1][j + 1] >= 0x80 && (uc)v[i + 1][j + 1] <= 0xbf) {
        return 2;
    }
    if (j + 2 < v[i].size()) {
        if ((uc)v[i][j] == 0xe0 && (uc)v[i][j + 1] >= 0xa0 && (uc)v[i][j + 1] <= 0xbf && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf)
            return 3;
        if ((uc)v[i][j] >= 0xe1 && (uc)v[i][j] <= 0xec && (uc)v[i][j + 1] >= 0x80 && (uc)v[i][j + 1] <= 0xbf && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf)
            return 3;
        if ((uc)v[i][j] == 0xed && (uc)v[i][j + 1] >= 0x80 && (uc)v[i][j + 1] <= 0x9f && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf)
            return 3;
        if ((uc)v[i][j] >= 0xee && (uc)v[i][j] <= 0xef && (uc)v[i][j + 1] >= 0x80 && (uc)v[i][j + 1] <= 0xbf && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf)
            return 3;
    }
    if (j + 3 < v[i].size()) {
        if ((uc)v[i][j] == 0xf0 && (uc)v[i][j + 1] >= 0x90 && (uc)v[i][j + 1] <= 0xbf && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf && (uc)v[i][j + 3] >= 0x80 && (uc)v[i][j + 3] <= 0xbf)
            return 4;
        if ((uc)v[i][j] >= 0xf1 && (uc)v[i][j] <= 0xf3 && (uc)v[i][j + 1] >= 0x80 && (uc)v[i][j + 1] <= 0xbf && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf)
            return 4;
        if ((uc)v[i][j] == 0xf4 && (uc)v[i][j + 1] >= 0x80 && (uc)v[i][j + 1] <= 0x8f && (uc)v[i][j + 2] >= 0x80 && (uc)v[i][j + 2] <= 0xbf && (uc)v[i][j + 3] >= 0x80 && (uc)v[i][j + 3] <= 0xbf)
            return 4;
    }
    return 1;
}

void File_in(int argc, char* argv[], string& Ori_Addr, string& Cmp_Addr, string& Out_Addr, vs& Ori_Text, vs& Cmp_Text) {
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


    ifstream fin(Ori_Addr);
    string t;
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

void Chinese_Process(vs& Ori_Text, vs& Cmp_Text) {
    vs replace;
    for (int i = 0; i < Ori_Text.size(); i++) {
        string t;
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
            if (ispunct(Ori_Text[i][j]))
                continue;
            if (isupper(Ori_Text[i][j]))
                Ori_Text[i][j] = tolower(Ori_Text[i][j]);
            t.push_back(Ori_Text[i][j]);
        }
        if (!t.empty())
            replace.push_back(t);
    }
    Ori_Text = replace;
    replace.clear();

    for (int i = 0; i < Cmp_Text.size(); i++) {
        string t;
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
            if (ispunct(Cmp_Text[i][j]))
                continue;
            if (isupper(Cmp_Text[i][j]))
                Cmp_Text[i][j] = tolower(Cmp_Text[i][j]);
            t.push_back(Cmp_Text[i][j]);
        }
        if (!t.empty())
            replace.push_back(t);
    }
    Cmp_Text = replace;
}

void File_out(double rate, string Out_Addr) {
    ofstream Ori_Out(Out_Addr);
    Ori_Out << fixed << setprecision(2) << rate;
    Ori_Out.close();
}

double LCS(vs Ori_Text, vs Cmp_Text) {
    if (Ori_Text.empty() || Cmp_Text.empty())
        return 0;
    vector<vector<int>> dp(2, vector<int>(max(Ori_Text.size(), Cmp_Text.size()) + 10, 0));
    int t = 0;
    for (int i = 1; i <= Ori_Text.size(); i++, t ^= 1) {
        for (int j = 1; j <= Cmp_Text.size(); j++) {
            if (Ori_Text[i - 1] == Cmp_Text[j - 1])
                dp[t ^ 1][j] = dp[t][j - 1] + 1;
            else
                dp[t ^ 1][j] = max(dp[t][j], dp[t ^ 1][j - 1]);
            // cerr << dp[t ^ 1][j] << ' ';
        }
        // cerr << endl;
    }
    double ans = (double)dp[t][Cmp_Text.size()] / (double)Ori_Text.size();
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

int main(int argc, char* argv[]) {
    string Ori_Addr, Cmp_Addr, Out_Addr;
    vs Ori_Text, Cmp_Text;
    double rate = 0;

    File_in(argc, argv, Ori_Addr, Cmp_Addr, Out_Addr, Ori_Text, Cmp_Text);
    // Test_LCS(Ori_Text, Cmp_Text);
    Chinese_Process(Ori_Text, Cmp_Text);

    rate = LCS(Ori_Text, Cmp_Text);
    rate *= 100;
    // cerr << fixed << setprecision(2) << rate << endl;
    File_out(rate, Out_Addr);
    // cout << fixed << setprecision(2) << rate << endl;
    // system("pause");
    return 0;
}