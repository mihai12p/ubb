import os 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt 
from fcOptimisation.NaturalChromosome import Chromosome
from random import randint

FILE_TO_LOAD = "football"

#Time complexity: O(n^2*m*c)
#Space complexity: O(n*m)

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

    degrees = []
    for i in range(network['nodesCount']):
        d = 0
        for j in range(network['nodesCount']):
            if matrix[i][j] == 1:
                d += 1
        degrees.append(d)
    network['degrees'] = degrees

    return network

def PlotNetwork(Network: list, CommunitiesColor: list):
    np.random.seed(123)
    matrix = np.matrix(Network)
    graph = nx.from_numpy_matrix(matrix)
    pos = nx.spring_layout(graph)
    plt.figure(figsize = (4, 4))
    nx.draw_networkx_nodes(graph, pos, node_size = 60, cmap = plt.cm.Spectral, node_color = CommunitiesColor)
    nx.draw_networkx_edges(graph, pos, alpha = 0.3)
    plt.show()

def Modularity1(Chromosome: list, resolution = 0.7) -> float:
    M = network['edgesCount']

    def communityContribution(CommunityID: int):
        Lc = 0
        communityNodesList = []
        for nodeIndex, community in enumerate(Chromosome):
            if community == CommunityID:
                communityNodesList.append(nodeIndex)

        for i in communityNodesList:
            for j in communityNodesList:
                if network['matrix'][i][j]:
                    Lc += 1 / 2

        sumDegree = sum(len(originalAdjencyList[nodeIndex]) for nodeIndex, community in enumerate(Chromosome) if community == CommunityID)
        return Lc / M - resolution * ((sumDegree / (2 * M)) ** 2)

    return sum(map(communityContribution, set(Chromosome)))

def Modularity2(Chromosome: list) -> float:
    Q = 0.0
    M = 2 * network['edgesCount']
    for i in range(0, network['nodesCount']):
        for j in range(0, network['nodesCount']):
            if Chromosome[i] == Chromosome[j]:
               Q += network['matrix'][i][j] - network['degrees'][i] * network['degrees'][j] / M
    return Q / M

class GA:
    def __init__(self, param = None, problParam = None):
        self.__param = param
        self.__problParam = problParam
        self.__population = []
        
    @property
    def population(self) -> list:
        return self.__population
    
    def initialisation(self):
        for _ in range(0, self.__param['popSize']):
            chromosome = Chromosome(self.__problParam)
            self.__population.append(chromosome)
    
    def evaluation(self):
        for chromosome in self.__population:
            chromosome.fitness = self.__problParam['function'](chromosome.repres)
            
    def bestChromosome(self) -> Chromosome:
        best = self.__population[0]
        for chromosome in self.__population:
            if chromosome.fitness > best.fitness:
                best = chromosome
        return best

    def selection(self):
        pos1 = randint(0, self.__param['popSize'] - 1)
        pos2 = randint(0, self.__param['popSize'] - 1)
        if self.__population[pos1].fitness > self.__population[pos2].fitness:
            return pos1
        else:
            return pos2 
    
    def oneGeneration(self):
        newPop = []
        for _ in range(self.__param['popSize']):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            offspring = p1.crossover(p2)
            offspring.mutation()
            newPop.append(offspring)
        self.__population = newPop
        self.evaluation()

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

    gaParam = {'popSize' : nodesCount, 'generations' : 100}
    problParam = {'function' : Modularity1, 'noDim' : nodesCount, 'network' : network, 'adj' : originalAdjencyList}
    ga = GA(gaParam, problParam)
    ga.initialisation()
    ga.evaluation()

    allBestFitnesses = []
    allAvgFitnesses = []
    generations = []

    maximumFitness = -1.0
    bestChromosomeOfTheBests = []

    for _ in range(gaParam['generations']):
        ga.oneGeneration()

        chromosome = ga.bestChromosome()
        if chromosome.fitness > maximumFitness:
            maximumFitness = chromosome.fitness
            bestChromosomeOfTheBests = chromosome

    communities = {}
    for nodeIndex, nodeCommunity in enumerate(bestChromosomeOfTheBests.repres):
        if nodeCommunity in communities:
            communities[nodeCommunity].append(nodeIndex)
        else:
            communities[nodeCommunity] = [nodeIndex]

    print("Modularitate: ", bestChromosomeOfTheBests.fitness)
    print("Numarul de comunitati identificate:", len(communities))
    print("Comunitatile identificate: ")
    for communityID, community in communities.items():
        print(community)

    PlotNetwork(network['matrix'], bestChromosomeOfTheBests.repres)