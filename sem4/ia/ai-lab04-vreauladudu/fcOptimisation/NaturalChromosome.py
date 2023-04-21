from random import random, randint, choice

class Chromosome:
    def __init__(self, repres = None, problParam = None):
        self.__problParam = problParam

        self.__repres = []

        if repres is None:
            self.__repres.append(problParam['source'])
            S = []
            S.append(problParam['source'])
            while len(S) > 0:
                currentNode = S.pop()

                tries, maxTries = 0, len(self.__problParam['adj'][currentNode]) - 1
                while tries < maxTries:
                    nodeNeighbour = choice(self.__problParam['adj'][currentNode])
                    if nodeNeighbour not in self.__repres:
                        self.__repres.append(nodeNeighbour)
                        S.append(nodeNeighbour)
                    tries += 1

                for nodeNeighbour in self.__problParam['adj'][currentNode]:
                    if nodeNeighbour not in self.__repres:
                        self.__repres.append(nodeNeighbour)
                        S.append(nodeNeighbour)
            self.__repres.append(problParam['source'])
        else:
            self.__repres = repres
                
        self.__fitness = 0.0
    
    @property
    def repres(self):
        return self.__repres
    
    @property
    def fitness(self):
        return self.__fitness 
    
    @repres.setter
    def repres(self, l = []):
        self.__repres = l 
    
    @fitness.setter 
    def fitness(self, fit = 0.0):
        self.__fitness = fit 
    
    def crossover(self, c):
        newrepres = []

        intersection = []
        for index in range(len(c.repres) - 1):
            if self.__repres[index] == c.repres[index]:
                intersection.append(index)

        randomIntersection = choice(intersection)
        
        newrepres[:randomIntersection] = self.__repres[:randomIntersection]
        newrepres[randomIntersection:] = c.repres[randomIntersection:]

        # for index in range(randomIntersection, len(c.repres)):
        #     if c.repres[index] not in newrepres:
        #         newrepres.append(c.repres[index])
        #     else:
        #         newrepres.append(self.__repres[index])

        return Chromosome(newrepres, c.__problParam)

    def mutation(self):
        if random() <= 0.85:
            pos1 = randint(1, len(self.__repres) - 2)
            pos2 = randint(1, len(self.__repres) - 2)
            self.__repres[pos1], self.__repres[pos2] = self.__repres[pos2], self.__repres[pos1]
        
    def __str__(self):
        return '\nChromo: ' + str(self.__repres) + ' has fit: ' + str(self.__fitness)
    
    def __repr__(self):
        return self.__str__()
    
    def __eq__(self, c):
        return self.__repres == c.__repres and self.__fitness == c.__fitness