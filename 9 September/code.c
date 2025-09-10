#define MOD 1000000007   // define MOD here

int peopleAwareOfSecret(int n, int delay, int forget) {
    long long dp[n + 1];   // dp[i] = number of people who learn secret on day i
    for (int i = 0; i <= n; i++) dp[i] = 0;

    dp[1] = 1; // Day 1: one person knows the secret

    long long share = 0; // number of people available to share on current day

    for (int day = 2; day <= n; day++) {
        // People who can start sharing today
        if (day - delay >= 1) {
            share = (share + dp[day - delay]) % MOD;
        }

        // People who forget today (they stop sharing)
        if (day - forget >= 1) {
            share = (share - dp[day - forget] + MOD) % MOD;
        }

        // New people who learn the secret today
        dp[day] = share;
    }

    // Count people who still remember secret at day n
    long long ans = 0;
    for (int day = n - forget + 1; day <= n; day++) {
        if (day >= 1) ans = (ans + dp[day]) % MOD;
    }

    return (int)ans;
}
