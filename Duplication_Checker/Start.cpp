#include<cmath>
#include<fstream>
#include <iomanip>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
typedef vector<string> vs;

void File_in(int argc, char* argv[], string& Ori_Addr, string& Cmp_Addr, string& Out_Addr, vs& Ori_Text, vs& Cmp_Text) {

}

void File_out(double rate, string Out_Addr) {

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
    Ori_Text.emplace_back("我");
    Ori_Text.emplace_back("爱");
    Ori_Text.emplace_back("你");
    Ori_Text.emplace_back("中");
    Ori_Text.emplace_back("国");

    Cmp_Text.emplace_back("我");
    Cmp_Text.emplace_back("喜");
    Cmp_Text.emplace_back("欢");
    Cmp_Text.emplace_back("中");
    Cmp_Text.emplace_back("国");

    // cerr << "LCS: " << fixed << setprecision(2) << LCS(Ori_Text, Cmp_Text) << endl;
}

signed main(int argc, char* argv[]) {
    string Ori_Addr, Cmp_Addr, Out_Addr;
    vs Ori_Text, Cmp_Text;
    double rate = 0;

    File_in(argc, argv, Ori_Addr, Cmp_Addr, Out_Addr, Ori_Text, Cmp_Text);

    Test_LCS(Ori_Text, Cmp_Text);
    rate = LCS(Ori_Text, Cmp_Text);
    cerr << fixed << setprecision(2) << rate << endl;

    File_out(rate, Out_Addr);
}