import os 
import networkx as nx
import matplotlib.pyplot as plt 
from fcOptimisation.NaturalChromosome import Chromosome
from random import randint

FILE_TO_LOAD = "football"
SOURCE = 0

#Time complexity: O(generations*popsize*n)
#Space complexity: O(n*m)

def ReadNet(FileName: str) -> dict:
    """
    Reads the graph from txt file and returns dictionary containing
    noNodes, noEdges, degrees vector and adjacency matrix of graph
    :param path: path of file
    :return: net, dictionary containing info about the graph
    """
    f = open(FileName, "r")
    net = {}
    n = int(f.readline())
    net['nodesCount'] = n
    mat = []
    for i in range(n):
        mat.append([])
        line = f.readline()
        elems = line.split(",")
        for j in range(n):
            mat[-1].append(int(elems[j]))
    net['matrix'] = mat

    net['source'] = int(f.readline())
    net['destination'] = int(f.readline())

    degrees = []
    noEdges = 0
    for i in range(n):
        d = 0
        for j in range(n):
            if mat[i][j] != 10000:
                d += 1
            if j > i:
                noEdges += mat[i][j]
        degrees.append(d)
    net['edgesCount'] = noEdges
    net['degrees'] = degrees
    f.close()
    return net

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

def GetFitness(Chromosome: list) -> float:
    networkMatrix = network['matrix']

    total = 0
    for i in range(nodesCount):
        if networkMatrix[Chromosome[i]][Chromosome[i + 1]]:
            total += networkMatrix[Chromosome[i]][Chromosome[i + 1]]

            if Chromosome[i] in Chromosome[:i]:
                total -= networkMatrix[Chromosome[i]][Chromosome[i + 1]] * 5 / 4

    return total / nodesCount

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
            chromosome = Chromosome(None, self.__problParam)
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

    def selection(self) -> int:
        pos1 = randint(0, self.__param['popSize'] - 1)
        pos2 = randint(0, self.__param['popSize'] - 1)
        if self.__population[pos1].fitness > self.__population[pos2].fitness:
            return pos1
        else:
            return pos2 
    
    def oneGenerationElitism(self):
        newPop = [self.bestChromosome()]
        for _ in range(self.__param['popSize'] - 1):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            offspring = p1.crossover(p2)
            offspring.mutation()
            newPop.append(offspring)
        self.__population = newPop
        self.evaluation()

if __name__ == "__main__":
    #filePath = os.path.join(os.path.curdir,  'data/' + FILE_TO_LOAD, FILE_TO_LOAD + '.gml')
    #network = ReadGML(filePath)

    network = ReadNet(os.path.join(os.path.curdir,  'data/', 'easy.txt'))

    nodesCount = network['nodesCount']
    originalAdjencyList = [[]] * nodesCount

    for i in range(nodesCount):
        originalAdjencyList[i] = []

    for lineIndex, line in enumerate(network['matrix']):
        for rowIndex, row in enumerate(line):
            if network['matrix'][lineIndex][rowIndex]:
                originalAdjencyList[lineIndex].append(rowIndex)

    gaParam = {'popSize' : 40, 'generations' : 200}
    problParam = {'function' : GetFitness, 'noDim' : nodesCount, 'network' : network, 'adj' : originalAdjencyList, 'source' : SOURCE}
    ga = GA(gaParam, problParam)
    ga.initialisation()
    ga.evaluation()

    allBestFitnesses = []
    bestGenerations = []
    generations = []
    maximumFitness = 0.0

    for _ in range(gaParam['generations']):
        generations.append(_)
        ga.oneGenerationElitism()

        chromosome = ga.bestChromosome()
        allBestFitnesses.append(chromosome.fitness)

        if chromosome.fitness >= maximumFitness:
            if chromosome.fitness > maximumFitness:
                bestGenerations = [chromosome]
            elif chromosome.fitness == maximumFitness:
                if not chromosome in bestGenerations:
                    bestGenerations.append(chromosome)
            maximumFitness = chromosome.fitness

    for generation in bestGenerations:
        print(generation.repres)

    plt.plot(generations, allBestFitnesses, label="Best path")
    plt.xlabel("Generatie")
    plt.ylabel("Randament")
    plt.legend()
    plt.show()