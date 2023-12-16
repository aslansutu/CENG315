#include "the4.h"

// do not add extra libraries here

int divide_land(int X, int Y, bool** possible_plots) {
    // Create a 2D vector to store the minimum unusable land for each subproblem
    std::vector<std::vector<int>> dp(X + 1, std::vector<int>(Y + 1, 0));

    std::vector<int> plot_x;
    std::vector<int> plot_y;
    int size = 0;

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            if (possible_plots[i][j]) {
                plot_x.push_back(i);
                plot_y.push_back(j);
                size++;
            }
        }
    }

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            // For land of ixj, max remaining is the land itself
            dp[i][j] = i * j;

            for (int k = 0; k < size; k++) {
                int a = plot_x[k];
                int b = plot_y[k];

                if (a > i || b > j) {continue;}

                int r_x = i - a;
                int r_y = j - b;
                // Compare the 2 instances of cutting it horizontally and vertically
                int min_1 = dp[r_x][j] + dp[a][r_y];
                int min_2 = dp[r_x][b] + dp[i][r_y];
                int min = std::min(min_1, min_2);
                dp[i][j] = std::min(min, dp[i][j]);
            }
        }
    }

    // The final result is stored in the bottom-right corner of the dp matrix
    return dp[X][Y];
}
