import os 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt 
from queue import Queue
from copy import deepcopy

FILE_TO_LOAD = "football"

#https://medium.com/smucs/girvan-newman-algorithm-community-detection-in-network-part-1-9cebce5f4c65
#https://medium.com/smucs/girvan-newman-algorithm-community-detection-in-network-part-2-2473c06dd518

#Time complexity: O(n^2*m*c)
#Space complexity: O(n*m)

def BFS(StartNode: int, AdjencyList: list) -> dict:
    level = 0
    visitedNodes = [StartNode]
    currentLevelNodes = [StartNode]

    graphDict = {}
    
    while currentLevelNodes:
        graphDict[level] = currentLevelNodes
        level += 1
        nextLevelNodes = []
        for currentLevelNode in currentLevelNodes:
            currentLevelNodeNeighbours = AdjencyList[currentLevelNode]
            for currentLevelNodeNeighbour in currentLevelNodeNeighbours:
                if currentLevelNodeNeighbour not in visitedNodes:
                    visitedNodes.append(currentLevelNodeNeighbour)
                    nextLevelNodes.append(currentLevelNodeNeighbour)
        currentLevelNodes = nextLevelNodes

    return graphDict

def CalculateNodesWeights(GraphDict: dict, AdjencyList: list) -> dict:
    nodesWeights = {}
    levels = len(GraphDict)

    rootLevelNodes = GraphDict[0]
    for rootLevelNode in rootLevelNodes:
        nodesWeights[rootLevelNode] = 1.0

    for level in range(1, levels):
        previousLevelNodes = GraphDict[level - 1]
        currentLevelNodes = GraphDict[level]
        for currentLevelNode in currentLevelNodes:
            currentLevelNodeNeighbours = AdjencyList[currentLevelNode]
            currentLevelNodeParentNodes = list(set(previousLevelNodes) & set(currentLevelNodeNeighbours))
            nodesWeights[currentLevelNode] = sum(float(nodesWeights[currentLevelNodeParentNode]) for currentLevelNodeParentNode in currentLevelNodeParentNodes)
    
    return nodesWeights

def CalculateEdgeWeights(GraphDict: dict, NodesWeights: dict, AdjencyList: list) -> dict:
    edgesWeights = {}
    nodeCredits = {}
    levels = len(GraphDict)

    for node in NodesWeights.keys():
        nodeCredits[node] = 0

    for level in range(levels - 2, -1, -1):
        currentLevelNodes = GraphDict[level + 1]
        nextLevelNodes = GraphDict[level]
        for currentLevelNode in currentLevelNodes:
            currentLevelNodeNeighbours = AdjencyList[currentLevelNode]
            currentLevelNodeParentNodes = list(set(nextLevelNodes) & set(currentLevelNodeNeighbours))
            for currentLevelNodeParentNode in currentLevelNodeParentNodes:
                edge = tuple(sorted([currentLevelNode, currentLevelNodeParentNode]))
                edgeWeight = (NodesWeights[currentLevelNodeParentNode] + nodeCredits[currentLevelNode]) / NodesWeights[currentLevelNode]
                edgesWeights[edge] = edgeWeight
                if currentLevelNodeParentNode not in nodeCredits:
                    nodeCredits[currentLevelNodeParentNode] = edgeWeight
                else:
                    nodeCredits[currentLevelNodeParentNode] += edgeWeight
    
    return edgesWeights

def CalculateBetweenness(StartNode: int, AdjencyList: list) -> dict:
    graphDict = BFS(StartNode, AdjencyList)
    nodesWeights = CalculateNodesWeights(graphDict, AdjencyList)
    edgesWeights = CalculateEdgeWeights(graphDict, nodesWeights, AdjencyList)
    
    return edgesWeights

def GetCommunities(AdjencyList) -> list:
    visited = []
    communities = []
    for node in list(dict.fromkeys([item for subList in AdjencyList for item in subList])):
        community = []
        queue = Queue()
        queue.put(node)
        while not queue.empty():
            currentNode = queue.get()
            if currentNode not in visited:
                visited.append(currentNode)
                community.append(currentNode)
                nodeNeighbours = AdjencyList[currentNode]
                for nodeNeighbour in nodeNeighbours:
                    queue.put(nodeNeighbour)
        if len(community):
            communities.append(sorted(community))

    return communities

def CalculateModularity(Communities: list) -> float:
    modularitySum = 0
    for community in Communities:
        for v1 in community:
            for v2 in community:
                ki, kj = len(modifiedAdjencyList[v1]), len(modifiedAdjencyList[v2])
                Aij = 1.0 if v2 in originalAdjencyList[v1] and v1 in originalAdjencyList[v2] else 0.0
                modularitySum += Aij - ki * kj / (2 * network['edgesCount'])

    return modularitySum / (2 * network['edgesCount'])

def ReadGML(FileName: str) -> dict:
    if FileName.endswith("karate.gml") or FileName.endswith("roedunet.gml") or FileName.endswith("redbestel.gml") or FileName.endswith("kdl.gml"):
        graph = nx.read_gml(FileName, label='id')
    else:
        graph = nx.read_gml(FileName)

    network = {}
    network['nodesCount'] = graph.number_of_nodes()
    network['edgesCount'] = graph.number_of_edges()

    matrix = []
    matrix = nx.to_numpy_matrix(graph)
    matrix = [[int(val) for val in row] for row in matrix.tolist()]
    network['matrix'] = matrix

    return network

def PlotNetwork(Network: list, CommunitiesColor: list):
    np.random.seed(123)
    matrix = np.matrix(Network)
    graph = nx.from_numpy_matrix(matrix)
    pos = nx.spring_layout(graph)
    plt.figure(figsize = (4, 4))
    nx.draw_networkx_nodes(graph, pos, node_size = 60, cmap = plt.cm.RdYlBu, node_color = CommunitiesColor)
    nx.draw_networkx_edges(graph, pos, alpha = 0.3)
    plt.show()

if __name__ == "__main__":
    filePath = os.path.join(os.path.curdir,  'data/' + FILE_TO_LOAD, FILE_TO_LOAD + '.gml')
    network = ReadGML(filePath)

    nodesCount = network['nodesCount']
    originalAdjencyList = [[]] * nodesCount

    for i in range(nodesCount):
        originalAdjencyList[i] = []

    for lineIndex, line in enumerate(network['matrix']):
        for rowIndex, row in enumerate(line):
            if network['matrix'][lineIndex][rowIndex]:
                originalAdjencyList[lineIndex].append(rowIndex)

    edgesBetweennessForNodes = {}
    for node in range(nodesCount):
        edgesBetweennessForNode = CalculateBetweenness(node, originalAdjencyList)
        if not edgesBetweennessForNodes:
            edgesBetweennessForNodes = edgesBetweennessForNode
        else:
            for key, val in edgesBetweennessForNode.items():
                if not key in edgesBetweennessForNodes:
                    edgesBetweennessForNodes[key] = val
                else:
                    edgesBetweennessForNodes[key] += val

    for key, val in edgesBetweennessForNodes.items():
        edgesBetweennessForNodes[key] = round(val / 2, 2)

    edgesBetweennessForNodes = { key: val for key, val in sorted(edgesBetweennessForNodes.items(), key = lambda x : x[1], reverse = True) }
    edgesBetweennessForNodesIter = iter(edgesBetweennessForNodes)

    modifiedAdjencyList = deepcopy(originalAdjencyList)

    currentModularity = 0.0
    maximumModularity = -1.0
    finalCommunities = []

    while edgesBetweennessForNodes:
        removedEdges = [key for key, val in edgesBetweennessForNodes.items() if val == max(edgesBetweennessForNodes.values())]
        for removedEdge in removedEdges:
            modifiedAdjencyList[removedEdge[0]].remove(removedEdge[1])
            modifiedAdjencyList[removedEdge[1]].remove(removedEdge[0])
            del edgesBetweennessForNodes[removedEdge]

        communities = GetCommunities(modifiedAdjencyList)
        currentModularity = CalculateModularity(communities)

        if currentModularity > maximumModularity:
            maximumModularity = currentModularity
            finalCommunities = communities

        if maximumModularity - currentModularity > 0.05:
            break

    communitiesColor = [0] * nodesCount
    colorIndex = 0
    for community in finalCommunities:
        colorIndex += 1
        for v in community:
            communitiesColor[v] = colorIndex

    listOfVisitedNodes = []

    print("Numarul de comunitati identificate:", len(finalCommunities) + 1)
    print("Comunitatile identificate: ")
    for index, comunity in enumerate(finalCommunities):
        print(finalCommunities[index])
        listOfVisitedNodes.extend(finalCommunities[index])

    lastCommunity = []
    for notVisitedNodes in range(network['nodesCount']):
        if notVisitedNodes not in listOfVisitedNodes:
            lastCommunity.append(notVisitedNodes)
    print(lastCommunity)

    PlotNetwork(network['matrix'], communitiesColor)