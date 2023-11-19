''' Problem Statement
        Batsmen has an array 'A' of length 'N' representing runs he can get. He has 'K' balls to play.
        On each ball, he can choose either the leftmost or the rightmost element of the array, remove it and add it to 'score'.
        After each ball, the remaining runs in the array are multiplied by 2.
        Your task is to determine the maximum possible value of 'score' he can get in 'K' balls. Considering the value can be large return modulo 1e9 + 7.
    
    Example:
        'N' = 2
        'K' = 1
        'A' = [5, 10]
        Since 'K'=1, we can only play 1 ball.
        The maximum value of the 'score' is only possible if we remove the rightmost element in this case.
        Therefore we return 10 as maximum possible value of 'score'.
'''


def maximumScore(num_players, max_singles, difficulty_scores): 
    if max_singles == 0: 
        print(0) 
        return 0 
 
    MOD = 10**9 + 7 
 
    pow2 = [0] * 41 
    pow2[0] = 1 
    for i in range(1, 41): 
        pow2[i] = pow2[i - 1] * 2 
 
    difficulty_dp = [[0] * num_players for _ in range(num_players)] 
 
    for i in range(num_players): 
        length = num_players - max_singles + 1 
        removed = num_players - length 
        j = i + num_players - max_singles 
        if j >= num_players: 
            break 
 
        difficulty_dp[i][j] = max(difficulty_scores[i], difficulty_scores[j]) * pow2[removed] 
 
    for length in range(num_players - max_singles + 2, num_players + 1): 
        for i in range(num_players): 
            j = i + length - 1 
            removed = num_players - length 
 
            if j >= num_players: 
                break 
 
            difficulty_dp[i][j] = max( 
                difficulty_scores[i] * pow2[removed] + difficulty_dp[i + 1][j], 
                difficulty_scores[j] * pow2[removed] + difficulty_dp[i][j - 1]) 
 
    return difficulty_dp[0][num_players - 1] % MOD