#!/usr/bin/env python


# Graph connections
graph_instance = {'A': {'B', 'C', 'G'},
                  'B': {'A', 'D', 'E'},
                  'C': {'A', 'F', 'G'},
                  'D': {'B'},
                  'E': {'B', 'F'},
                  'F': {'C', 'E'},
                  'G': {'C', 'F'}}

# Graph edge costs
graph_weight = {'AB': 1, 'BE': 1, 'AC': 1, 'BD': 5, 'EF': 1, 'CF': 3, 'FG': 1, 'CG': 1, 'AG': 10}


# Class to hold information of a Path
class PathData(object):
    def __init__(self):
        self._path = list()
        self._cost = 0

    def get_path(self):
        return self._path

    def get_cost(self):
        return self._cost


def BFS_Search(start, goal, mygraph, mygraph_weight):
    mypathdata = PathData()
    mypathdata._path.append(start)
    mypathdata._cost = 0
    queue = [(start, mypathdata)]
    while queue:
        (vertex, pathdat) = queue.pop(0)
        for next in mygraph[vertex] - set(pathdat.get_path()):
            if next == goal:
                if vertex+next in mygraph_weight:
                    PandC = pathdat.get_path() + [next] + [pathdat.get_cost() + mygraph_weight[vertex+next]]
                else:
                    PandC = pathdat.get_path() + [next] + [pathdat.get_cost() + mygraph_weight[next + vertex]]
                yield PandC
            else:
                mypathdata2 = PathData()
                mypathdata2._path = pathdat.get_path() + [next]
                if vertex+next in mygraph_weight:
                    mypathdata2._cost = pathdat.get_cost() + mygraph_weight[vertex+next]
                else:
                    mypathdata2._cost = pathdat.get_cost() + mygraph_weight[next + vertex]
                queue.append((next, mypathdata2))


all_path = list(BFS_Search('A', 'F', graph_instance, graph_weight))
print("All paths with associated costs: ")
print(all_path)
