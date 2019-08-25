#!/usr/bin/env python


graph = {'A': {'B', 'C'},
         'B': {'A', 'D', 'E'},
         'C': {'A', 'F', 'G'},
         'D': {'B'},
         'E': {'B', 'F'},
         'F': {'C', 'E'},
         'G': {'C', 'F'}}


graph_weight = {'AB': 1,
                'BE': 1,
                'AC': 1,
                'BD': 5,
                'EF': 1,
                'CF': 3,
                'FG': 1,
                'CG': 1,
                'GF': 1}


class PathData(object):
    def __init__(self):
        self._path = list()
        self._cost = 0


def bfs_paths(graph, start, goal):
    mypathdata = PathData()
    mypathdata._path.append(start)
    mypathdata._cost = 0
    # queue = [(start, [start])]
    queue = [(start, mypathdata)]
    while queue:
        (vertex, pathdat) = queue.pop(0)
        # path = pathdat._path
        # print(graph[vertex] - set(path))
        for next in graph[vertex] - set(pathdat._path):
            if next == goal:
                pathdat._path.append(next)
                pathdat._cost += graph_weight[vertex+next]
                # yield path + [next]
                PandC = pathdat._path + [pathdat._cost]
                yield PandC
            else:
                mypathdata2 = PathData()
                mypathdata2._path = pathdat._path + [next]
                # mypathdata2._cost = pathdat._cost + 1
                print(vertex+next, graph_weight[vertex+next])
                mypathdata2._cost = pathdat._cost + graph_weight[vertex+next]
                queue.append((next, mypathdata2))
    if not queue:
        print("Queue empty")


print(list(bfs_paths(graph, 'A', 'F')))

vertex: A
next: C
next: B
vertex: C
next: G
next: F
vertex: B
next: E
next: D
vertex: G
next: F
vertex: E
next: F
vertex: D
Queue empty
[['A', 'C', 'F', 2], ['A', 'C', 'G', 'F', 3], ['A', 'B', 'E', 'F', 3]]

vertex: A
next: C
next: B
vertex: C
next: F
next: G
vertex: B
next: D
next: E
vertex: G
vertex: D
vertex: E
next: F
Queue empty
[['A', 'C', 'F', 2], ['A', 'B', 'E', 'F', 3]]