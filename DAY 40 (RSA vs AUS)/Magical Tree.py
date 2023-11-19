''' Problem Statement
        In a cricket league with 'N' teams and 'M' scheduled matches, there is a rival team trying to disrupt the predictions of a seasoned coach. In the coach's system, every team is linked directly or indirectly to every other team, with the sequence of matches from the tournament forming a graph.
        The coach utilizes these matches to make predictions. He can use match 'i' in his predictions if and only if there exist any two teams 'A' and 'B' such that there is no sequence of matches linking 'A' and 'B' without including match 'i'.
        However, the rival team has the ability to schedule an additional match between any two teams once. Your task is to determine the minimum number of matches that the coach can use in his prediction system after rival team uses their ability exactly once.
    
    Example:
        'N' = 3
        'M' = 2
        'Matches' = '[ [1, 2], [2, 3] ]'
        Before scheduling an additional match:
            For match [1,2], there's no alternate route between 1 and 2 that doesn't contain this match, so this match can be used.
            Similarly, for match [2,3], as there is no alternate route between 2 and 3 that doesn't contain this match, so this match can be used.
            Thus, there are two matches which the coach can use.
        After scheduling an additional match:
            If the rival team schedules a match between team '1' and '3', it creates alternate paths. For instance, the match between '1' and '2' is no longer the sole connection, as an indirect sequence (1→3→2) is now possible, that does not contain match [1,2]. This applies to other matches as well.
            Consequently, the coach cannot use any match reliably. Hence, the minimum number of matches used in prediction is 0.
'''


from collections import defaultdict

def dfs(vertex, parent_vertex, timer, bridge_set, visited_nodes, entry_time, lowest_entry, parent_array, adjacency_list):
    visited_nodes[vertex] = True
    entry_time[vertex] = lowest_entry[vertex] = timer
    timer += 1
    parent_array[vertex] = parent_vertex
    for adjacent in adjacency_list[vertex]:
        if adjacent == parent_vertex:
            continue
        if visited_nodes[adjacent]:
            lowest_entry[vertex] = min(lowest_entry[vertex], entry_time[adjacent])
        else:
            dfs(adjacent, vertex, timer, bridge_set, visited_nodes, entry_time, lowest_entry, parent_array, adjacency_list)
            lowest_entry[vertex] = min(lowest_entry[vertex], lowest_entry[adjacent])
            if lowest_entry[adjacent] > entry_time[vertex]:
                bridge_set.add((min(adjacent, vertex), max(adjacent, vertex)))

def find_bridges(num_vertices, bridge_set, visited_nodes, entry_time, lowest_entry, parent_array, adjacency_list):
    timer = 0
    for i in range(num_vertices):
        if not visited_nodes[i]:
            dfs(i, -1, timer, bridge_set, visited_nodes, entry_time, lowest_entry, parent_array, adjacency_list)

def dfs_recursive(vertex, distance, depth, visited_nodes, adjacency_list):
    visited_nodes[vertex] = True
    depth[vertex] = distance
    for neighbor in adjacency_list[vertex]:
        adjacent, weight = neighbor
        if not visited_nodes[adjacent]:
            dfs_recursive(adjacent, distance + weight, depth, visited_nodes, adjacency_list)

def magicalTree(num_vertices, num_edges, edges_list):
    adj_list = defaultdict(list)
    visited = [False] * (num_vertices + 1)
    entry_time = [-1] * (num_vertices + 1)
    lowest_entry = [-1] * (num_vertices + 1)
    parent = [-1] * (num_vertices + 1)

    for i in range(num_edges):
        adj_list[edges_list[i][0]].append(edges_list[i][1])
        adj_list[edges_list[i][1]].append(edges_list[i][0])

    bridge_set = set()
    find_bridges(num_vertices, bridge_set, visited, entry_time, lowest_entry, parent, adj_list)
    total_bridges = len(bridge_set)

    adj_new = defaultdict(list)
    for i in range(2, num_vertices + 1):
        v = parent[i]
        w = 0
        if (min(i, v), max(i, v)) in bridge_set:
            w = 1
        adj_new[i].append((v, w))
        adj_new[v].append((i, w))

    visited = [False] * (num_vertices + 1)
    node_depth = [0] * (num_vertices + 1)
    dfs_recursive(1, 0, node_depth, visited, adj_new)

    max_depth_node = 0
    max_depth = 0
    for i in range(1, num_vertices + 1):
        if max_depth < node_depth[i]:
            max_depth = node_depth[i]
            max_depth_node = i

    visited = [False] * (num_vertices + 1)
    node_depth = [0] * (num_vertices + 1)
    dfs_recursive(max_depth_node, 0, node_depth, visited, adj_new)
    diameter = max(node_depth)
    
    return total_bridges - diameter
