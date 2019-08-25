#!/usr/bin/env python

# number of vertices in the graph
num_vertex = 5

# create a 2D list for Adjacency List representation of a graph
adj_list = [[] for i in range(num_vertex)]
print(adj_list)

# Fill in the adjacency list
adj_list[0].append(1)
adj_list[0].append(2)
adj_list[0].append(4)
adj_list[1].append(2)
adj_list[2].append(3)
adj_list[2].append(4)
adj_list[3].append(4)
adj_list[4].append(-1) # -1 to indicate deadend of the tree

print(adj_list)

# Traverse the tree
visited_list = [0]*num_vertex
visited_list[0] = 1
for i in range(num_vertex):
    for j in range(len(adj_list[i])):
        if visited_list[adj_list[i][j]] == 0:
            print(adj_list[i][j])
            visited_list[adj_list[i][j]] = 1


