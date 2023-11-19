''' Problem Statement
        In the epic showdown between India and Australia in the Cricket World Cup final, 'W' powerful defenders represent the vigilant commandos guarding the boundary of the ground and providing security to the players on the ground, while 'M'exuberant fans symbolize the excited spectators in the stands of the stadium.
        These defenders are strategically positioned at specific locations along the boundary, indicated by the array 'B' of length 'N', such that 'B[i]' is the x- coordinate of the 'i-th' defender.
        Meanwhile, the fans are joyfully marching toward the ground in a straight line parallel to the x-axis. They are positioned at respective coordinates represented by the array 'A'such that 'A[i]' is the x-coordinate of the 'i-th' excited fan on the line.
        Each fan has a level of enthusiasm denoted by the array 'H' such that 'H[i] represents the level of enthusiasm of the 'i-th' excited fan. If a fan's enthusiasm reduces to '0', it means they've calmed down.
        Each defenders can fire an infinite-range railgun to either its left or right side. Defenders have accurate throws that can reduce a fan's excitement by 'K'. You only have a moment to act before more fans appear, so each defender can fire its railgun at most once.
        The goal is to prevent the exuberant fans from entering the ground after India win the world cup. Determine if it's possible to eliminate all the fans. Return '1' if achievable; otherwise, return '0'.

    Example:
        Let 'N' = 2, 'M' = 3, 'A' = [3, 5, 7], 'H' = [4, 3, 2 ], 'B' = [1, 6], 'K' = 2.
        The order of defenders and fans on the line is: [DO, FO, F1, D1, F2 ], where 'Di' is the 'i-th' defender and 'Fi' is the 'i-th' fan.
        DO fires a railgun to its right side, dealing 'K = 2' decrease in excitement level of every fan. 'H' reduces to [2, 1, 0].
        D1 fires a railgun to its left side, dealing 'K = 2' damage to FO and F1. All fans are eliminated.
        Therefore, it is possible to eliminate all the fans..
        Thus, the answer is '1'.
'''


from typing import *


def terminalDefence(n: int, m: int, a: List[int], h: List[int], b: List[int], k: int) -> int:
    # write your code here
    i,j,l = 0,0,0
    C= [0]*(n+m)

    while i<m or j<n:
        if i!=m and (j == n or a[i]<b[j]):
            C[l] =(h[i] +k -1)//k
            i+=1
        else:
            C[l] = -1
            j+=1
        l+=1
    cnt = req = 0
    left=right=0
    for i in range(n+m):
        if C[i] == -1:
            cnt+=1
            if cnt+req>n:
                right =n-cnt
            else:
                left+=1
        elif C[i]>left+right:
            if cnt+req>n or C[i]>n:
                return 0
            req=max(req,C[i]-left)
    return 1
        
    pass