#include <iostream>

using namespace std;

int main()
{
    int n = 3;
    int coins[n] = {2, 3, 5};
    int amount = 100;

    int dp[amount + 1] = {0};
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        int coin = coins[i];
        for (int j = coin; j <= amount; j++)
        {
            dp[j] = dp[j] + dp[j - coin];
        }
    }

    cout << dp[amount];
}
