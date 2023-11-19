/*  Problem Statement
        You are given a graph with 'N' vertices and 'M' directed edges. Each vertex is assigned a random number in the range '[0, K-1]' to represent the score at a specific time in a cricket match, with equal probability for all numbers. Directed edges signify the progression of scores from past points to future points.
        A valid graph in this context ensures that for all directed edges (u, v)', the random number assigned to vertex 'u' is less than or equal to the random number assigned to vertex 'v', as the score from a past point is always less than or equal to the score of a future point in a cricket match.
        The given graph is guaranteed to satisfy the following property: There is a vertex 'v' such that if we start a DFS from 'v', we can visit all 'N' vertices, and there is only one shortest path from 'v' to all 'N' vertices.
        Find the probability that the randomly generated graph is valid.
        Note: The answer should be found modulo 10^9 + 7. Formally, let M = 10^9 +7. It can be shown that the answer can be expressed as an irreducible fraction p/q, where p and q are integers and q = 0 (mod M). Output the integer equal to p* (q^-1) mod M. In other words, output such an integer x that 0 <= x < M and x * q = p (mod M).

    Example:
        Let 'N' = 3, 'M' = 2, edges = [[0, 1], [0, 2]], 'K' = 3.
        Random number assignments that result in a valid graph are [0, 0, 0], [0, 0, 1], [0, 1, 0], [0, 1, 1], [0, 0, 2], [0, 2, 0], [0, 2, 1], [0, 1, 2], [0, 2, 2], [1, 1, 1], [1, 2, 1], [1, 1, 2], [1, 2, 2], and [2, 2, 2].
        The total number of possible assignments is '27', and the '14' assignments above are desired.
        Thus, the required probability is '(14/27) % (10^9+7)=185185187'.
*/


int modInverse(long long number, long long modulus) {
    vector<long long> multiplicativeInverse(number + 1);
    multiplicativeInverse[0] = multiplicativeInverse[1] = 1;

    for (int i = 2; i <= number; i++) {
        multiplicativeInverse[i] = multiplicativeInverse[modulus % i] * (modulus - modulus / i) % modulus;
    }

    return multiplicativeInverse[number];
}

void dfsFirstTraversal(int vertex, vector<vector<int>> &graph, vector<int> &visited, vector<int> &order) {
    visited[vertex] = 1;

    for (int i = 0; i < graph[vertex].size(); i++) {
        int neighbor = graph[vertex][i];

        if (!visited[neighbor]) {
            dfsFirstTraversal(neighbor, graph, visited, order);
        }
    }

    order.push_back(vertex);
}

void dfsSecondTraversal(int vertex, int representative, int &cycleSize, vector<vector<int>> &reverseGraph,
    vector<int> &visited, vector<int> &representatives) {
    visited[vertex] = 1;
    representatives[vertex] = representative;
    cycleSize++;

    for (int i = 0; i < reverseGraph[vertex].size(); i++) {
        int neighbor = reverseGraph[vertex][i];

        if (!visited[neighbor]) {
            dfsSecondTraversal(neighbor, representative, cycleSize, reverseGraph, visited, representatives);
        }
    }
}

void dfsSuffixArray(int vertex, int modulo, int inverseK, int k, vector<vector<int>> &tree,
    vector<vector<long long>> &dp, vector<vector<long long>> &suffixArray) {
    for (int j = 0; j < k; j++) {
        dp[vertex][j] = inverseK;
    }

    for (int i = 0; i < tree[vertex].size(); i++) {
        int neighbor = tree[vertex][i];
        dfsSuffixArray(neighbor, modulo, inverseK, k, tree, dp, suffixArray);

        for (int j = 0; j < k; j++) {
            dp[vertex][j] = dp[vertex][j] * suffixArray[neighbor][j] % modulo;
        }
    }

    suffixArray[vertex][k - 1] = dp[vertex][k - 1];
    for (int j = k - 2; j >= 0; j--) {
        suffixArray[vertex][j] = (suffixArray[vertex][j + 1] + dp[vertex][j]) % modulo;
    }
}

int randomlySorted3(int numVertices, int numEdges, vector<vector<int>> &edges, int upperLimitRandom) {
    int modulo = 1e9 + 7, inverseK = modInverse(upperLimitRandom, modulo);
    vector<long long> powers(numVertices);

    powers[0] = 1;
    for (int i = 1; i < numVertices; i++) {
        powers[i] = (powers[i - 1] * inverseK) % modulo;
    }

    vector<vector<int>> graph(numVertices), reverseGraph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int u = edges[i][0], v = edges[i][1];
        graph[u].push_back(v);
        reverseGraph[v].push_back(u);
    }

    vector<int> visited(numVertices);
    vector<int> order;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            dfsFirstTraversal(i, graph, visited, order);
        }
    }

    reverse(order.begin(), order.end());
    visited.assign(numVertices, 0);

    int cycleProduct = 1;
    vector<int> representatives(numVertices);

    for (int i = 0; i < numVertices; i++) {
        int vertex = order[i];

        if (!visited[vertex]) {
            int cycleSize = 0;
            dfsSecondTraversal(vertex, vertex, cycleSize, reverseGraph, visited, representatives);
            cycleProduct = (cycleProduct * powers[cycleSize - 1]) % modulo;
        }
    }

    vector<vector<int>> tree(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int u = edges[i][0], v = edges[i][1];

        if (representatives[u] != representatives[v]) {
            tree[representatives[u]].push_back(representatives[v]);
        }
    }

    vector<vector<long long>> dp(numVertices, vector<long long>(upperLimitRandom));
    vector<vector<long long>> suffixArray(numVertices, vector<long long>(upperLimitRandom));

    dfsSuffixArray(representatives[order[0]], modulo, inverseK, upperLimitRandom, tree, dp, suffixArray);
    return (cycleProduct * suffixArray[representatives[order[0]]][0]) % modulo;
}
