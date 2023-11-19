/*  Problem Statement
        Virat is facing the deadly New Zealand bowlers and he has a plan for it. Each ball has a certain difficulty level represented by a value in an array 'A' of length 'N'. Virat aims to complete the innings while taking the minimum possible total difficulty.
        However, when facing a ball:
            Virat can pass on the strike by taking a single for at most 'K' balls which adds 0 to the difficulty faced by him. But due to fatigue caused by running thesubsequent balls have difficulty increased by 1. Virat chooses to hit a boundary which adds the difficulty of the ball to difficultyfaced by him.
        Your goal is to help Virat by finding which balls to hit the boundaries so it minimizes the total difficulty, considering the ability to pass on the strike by taking a single. Print the minimum possible total difficulty achieved.
    
    Example:
        Input: 'N' = 7, 'K' = 5, 'A' = [8, 2, 5, 15, 11, 2, 8]
        Output: 9
        For this test case, the balls that Virat should pass the strike to minimize the total difficulty are 1, 3, 4, 5, and 7. This results in a total difficulty of 9, the minimum possible value.
        To be precise, the total difficulty can be calculated as follows:
            Ball 1: Pass the Strike. (+1 to all subsequent balls)
            Ball 2: Hit a Boundary. (Difficulty Faced 2 + 1)
            Ball 3: Pass the Strike. (+1 to all subsequent balls)
            Ball 4: Pass the Strike. (+1 to all subsequent balls)
            Ball 5: Pass the Strike. (+1 to all subsequent balls)
            Ball 6: Hit a Boundary. (Difficulty Faced 2 + 4)
            Ball 7: Pass the Strike. (+1 to all subsequent balls) The total difficulty is thus 0+3+0+0+0+6+0=9.
        It can be proven that this is the optimal sequence, and there is no other way for Virat to complete the innings with a lower total difficulty.
*/


long long findMinimumDifficulty(int n, int k, vector<int> a) {  
    // Write your code here.  
    long long answer=0;  
  
    vector<pair<int,int>> v;  
    for(int i=0; i<n; i++) v.push_back({a[i]+i, i});  
    sort(v.begin(), v.end());  
  
    set<pair<int,int>> s;  
    for(int i=0; i<n-k; i++)  
    s.insert(v[i]);  
  
    int offset=0;  
    for(int i=0; i<n; i++)  
    {  
        if(s.count({a[i]+i, i}))  
        {  
            answer+= offset+ a[i];  
        } else {  
            offset++;  
        }  
    }  
  
    return answer;  
}