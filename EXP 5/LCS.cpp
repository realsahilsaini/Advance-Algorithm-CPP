// Longest common substring

// #include <iostream>
// #include <vector>
// #include <algorithm>

// int LCS(std::string X, std::string Y) {
//     int m = X.size();
//     int n = Y.size();
//     std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

//     for (int i = 1; i <= m; i++) {
//         for (int j = 1; j <= n; j++) {
//             if (X[i - 1] == Y[j - 1]) {
//                 dp[i][j] = dp[i - 1][j - 1] + 1;
//             } else {
//                 dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
//             }
//         }
//     }
//     return dp[m][n];
// }

// int main() {
//     std::string X, Y;
//     std::cout << "Enter first string: ";
//     std::cin >> X;
//     std::cout << "Enter second string: ";
//     std::cin >> Y;
//     std::cout << "Length of LCS is " << LCS(X, Y) << std::endl;
//     return 0;
// }
























#include <iostream>
#include <vector>
#include <algorithm>

std::string LCS(std::string X, std::string Y) {
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Constructing the LCS string
    int i = m, j = n;
    std::string lcs = "";
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int main() {
    std::string X, Y;
    std::cout << "Enter first string: ";
    std::cin >> X;
    std::cout << "Enter second string: ";
    std::cin >> Y;
    std::string lcs = LCS(X, Y);
    std::cout << "Length of LCS: " << lcs.length() << std::endl;
    std::cout << "LCS: " << lcs << std::endl;
    return 0;
}