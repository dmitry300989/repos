# First networkx library is imported 
# along with matplotlib
import networkx as nx
import matplotlib.pyplot as plt
  
# Defining a Class
class GraphVisualization:
   
    def __init__(self):
          
        # visual is a list which stores all 
        # the set of edges that constitutes a
        # graph
        self.visual = []
        self.dictWeight = {}
        self.Q = set()
          
    # addEdge function inputs the vertices of an
    # edge and appends it to the visual list
    def addEdge(self, a, b, weight=1):
        temp = [a, b]
        self.Q.add(a)
        self.Q.add(b)
        self.dictWeight[tuple(temp)] = weight
        self.visual.append(temp)

    # In visualize function G is an object of
    # class Graph given by networkx G.add_edges_from(visual)
    # creates a graph with a given list
    # nx.draw_networkx(G) - plots the graph+
    # plt.show() - displays the graph
    def visualize(self):
        G = nx.DiGraph()
        G.add_edges_from(self.visual)
        pos = nx.spring_layout(G)
        nx.draw_networkx_nodes(G, pos, node_size = 500)
        nx.draw_networkx_edges(G, pos, edgelist = G.edges(), edge_color = 'black')
        nx.draw_networkx_labels(G, pos)
        nx.draw_networkx_labels(G, pos)
        #nx.draw_networkx(G)
        plt.show()

    def GetWeight(self, u,v):
        return self.dictWeight[tuple([u,v])]

    def GetSetVertices(self):
        return self.Q

def CommonTopologicalSort(G):
    in_degree = {}
    linearOrder = []
    for edge in G.visual:
        in_degree[edge[1]], in_degree[edge[0]] = 0, 0
    for edge in G.visual:
        in_degree[edge[1]] = in_degree[edge[1]] + 1

    next = []
    for edge in G.visual:
        if in_degree[edge[0]] == 0 and (edge[0] not in next):
            next.append(edge[0])

    while next:
        u = next[0]
        next.pop(0)
        linearOrder.append(u)
        for edge in G.visual:
            if edge[0] == u:
                v = edge[1]
                in_degree[v] = in_degree[v] - 1
                if in_degree[v] == 0:
                    next.append(v)

    return linearOrder

def TopologicalSort(G):
    #Set all values in in-degree to 0.
    n = len(G.visual)
    in_degree = [0] * n
    linearOrder = []
    for edge in G.visual:
        in_degree[edge[1]] = in_degree[edge[1]] + 1
    next = []
    for edge in G.visual:
        if in_degree[edge[0]] == 0 and (edge[0] not in next):
            next.append(edge[0])
    while next:
        u = next[0]
        next.pop(0)
        linearOrder.append(u)
        for edge in G.visual:
            if edge[0] == u:
                v = edge[1]
                in_degree[v] = in_degree[v] - 1
                if in_degree[v] == 0:
                    next.append(v)
    return linearOrder

class Relax:
    def __init__(self, Graph):
        self.shortest = []
        self.pred = []
        self.G = Graph
        n = len(self.G.visual)
        for v in range(0,n-1):
            self.shortest.append(100);
            self.pred.append(0)

    def impl(self, u, v):
        if self.shortest[u] + self.G.GetWeight(u,v) < self.shortest[v]:
            self.shortest[v] = self.shortest[u] + self.G.GetWeight(u,v)
            self.pred[v] = u

class DAG:

    def __init__(self, graph):
        self.G = graph
        self.relax = Relax(G)

    def Shortest_Paths(self, s):
        l = TopologicalSort(self.G)
        self.relax.shortest[s] = 0
        for u in l:
            for edge in self.G.visual:
                if edge[0] == u:
                    v = edge[1]
                    self.relax.impl(u,v)

    def GetShortestPath(self):
        return self.relax.shortest

class Dijkstra:

    def __init__(self, graph):
        self.G = graph
        self.relax = Relax(G)

    def Shortest_Paths(self, s):
        self.relax.shortest[s] = 0
        Q = self.G.GetSetVertices()
        while Q:
            #u = self.relax.shortest.index(min(self.relax.shortest))
            m = 1000
            for r in Q:
                if self.relax.shortest[r] <= m:
                    m = self.relax.shortest[r]
                    u = r
            if u in Q:
                Q.remove(u)
                for edge in self.G.visual:
                    if edge[0] == u:
                        v = edge[1]
                        self.relax.impl(u,v)

    def GetShortestPath(self):
        return self.relax.shortest


if __name__ == '__main__':
    # Driver code
    G = GraphVisualization()

    G.addEdge(0, 2)
    G.addEdge(0, 1)
    G.addEdge(1, 3)
    G.addEdge(3, 4)
    G.addEdge(2, 4)
    G.addEdge(0, 4)
    G.addEdge(5, 2)

    """
    G.addEdge('A', 'B')
    G.addEdge('A', 'C')
    G.addEdge('C', 'D')
    G.addEdge('B', 'D')
    """
    #print(CommonTopologicalSort(G))
    G.visualize()
    dijkstra = DAG(G)
    dijkstra.Shortest_Paths(0)
    print(dijkstra.GetShortestPath())