/*  Problem Statement
        You have a scorecard 'A' of 'N' cricket matches, initially all marked with a score of '0'. Over time, you adjusted the scores for a series of consecutive matches on this scorecard. Each adjustment allowed you to do the following:
            • Select a sequence of consecutive matches such that all the scores in this sequence are the same.
            • Increase the score of all matches within this selected sequence by 1, excluding the first and last matches of the sequence.
        However, this was done some time ago. You can only recall certain scores on scorecard 'A' after all the adjustments were applied. Any score on scorecard 'A' that you don't remember is denoted by '-1'.
        Your task is to determine how many different scorecards are possible. Since this number may be very large, return it modulo 10^9+7.
    Example:
        'N' = 4
        'A' = [-1, -1, -1, 0]
        These four scorecards are all the possibilities for the original scorecard 'A': [0, 0, 0, 0], [0, 1, 0, 0], [0, 1, 1, 0], [0, 0, 1, 0].
        Therefore, the answer here is 4.
*/


int howManyArrays(int n, vector<int>& v) {  
    // Write Your Code Here  
    if (v[0] > 0 || v[n - 1] > 0) {  
        return 0;  
    }  
    vector<vector<long long int>> dp(n, vector<long long int>(n, 0));  
    dp[0][0] = 1;  
    for (int i = 1; i < n; i++) {  
        int curr = i;  
        int prev = i - 1;  
        for (int j = 0; j < n; j++) {  
        dp[curr][j] = dp[prev][j];  
        if (j > 0) {  
            dp[curr][j] = (dp[curr][j] + dp[prev][j - 1]) % 1000000007;  
        }  
        if (j + 1 < n) {  
            dp[curr][j] = (dp[curr][j] + dp[prev][j + 1]) % 1000000007;  
        }  
        }  
        if (v[i] != -1) {
        for (int j = 0; j < n; j++) {
            if (j != v[i])
              dp[curr][j] = 0;
        }
        }
    }
    return dp[n - 1][0];
}