/*  Problem Statement
        In the thrilling India vs. Australia Cricket World Cup final match, Ninja closely observes the team's performance over the 'W'overs. He maintains a record array 'A' of each over's performance.
        For each over, he's determined to discover the highest team performance lower than their current performance that occurred between the present over and the last time they achieved the same performance score.
        If there is no previous occurrence of the same performance score, he considers it as occurring from the very first over.
        The task is to assist Ninja in creating an array of length 'N' representing each over. Each index should contain the highest performance score lower than the current over's score that occurred between that over and the last occurrence of the same score. If no such score exists, it's indicated as '-1' for that index. Return the calculated array.
    
    Example:
        'N' = 3
        'A' = [2, 1, 2]
        Here, for the 'Oth' index, no such element is present between index '0' and '0'. For the '1st' index, no such element is present between index '0' and '1'. And for the '2nd' index, the maximum element between the 'Oth' and '2nd' index which is less than '2' is '1'.
        Hence, the answer for this case is '[-1, -1, 1]'.
*/


void updateTree(int node, int startldx, int endldx, int targetldx, int value, vector<int> &tree) {
	if (startldx == endldx) {
		tree[node] = value;
		return;
	}
	int mid = (startldx + endldx) / 2;
	if (targetldx <= mid) {
		updateTree(2 * node, startldx, mid, targetldx, value, tree);
	} 
	else {
		updateTree(2 * node + 1, mid + 1, endldx, targetldx, value, tree); 
	}
	tree[node] = max(tree[2 * node], tree[2 * node + 1]); 
}


int queryTree(int node, int startldx, int endldx, int rangeStart, int rangeEnd, vector<int> &tree) {
	if (startldx > rangeEnd || endldx < rangeStart) { 
		return -1;
	}
	if (rangeStart <= startldx && endldx <= rangeEnd) { 
		return tree[node]; 
	}
	int mid = (startldx + endldx) / 2;
	return max(queryTree(2 * node, startldx, mid, rangeStart, rangeEnd, tree),
	queryTree(2 * node + 1, mid + 1, endldx, rangeStart, rangeEnd, tree));
}

vector<int> ninjaAndLessMaxElement(int length, vector<int> &input) { 
	vector<int> segmentTree(4* length + 8, -1); 
	vector<vector<int>> positions(length + 1, vector<int>(1, 0));
	for (int i = 0; i < length; i++) { 
		positions[input[i]].push_back(i + 1); 
	}
	vector<int> result(length);
	for (int i = 1; i <= length; i++) { 
		if (positions[i].size() <= 1) { 
			continue; 
		}
	for (int j = 1; j < positions[i].size(); j++) { 
		result[positions[i][j] - 1] = queryTree(1, 1, length, positions[i][j - 1] + 1, positions[i][j] - 1, segmentTree); 
	}
    for (int j = 1; j < positions[i].size(); j++) {
            updateTree(1, 1, length, positions[i][j], i, segmentTree);
    }
        }
        return result;

}