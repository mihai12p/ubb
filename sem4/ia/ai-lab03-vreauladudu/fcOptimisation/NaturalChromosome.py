from random import randint, choice

class Chromosome:
    def __init__(self, problParam = None):
        self.__problParam = problParam

        self.__repres = [-1 for _ in range(problParam['noDim'])]

        gongNodesCount = self.__problParam['noDim'] // 5
        for _ in range(gongNodesCount):
            randomNode = randint(0, self.__problParam['noDim'] - 1)
            randomCommunity = randint(0, self.__problParam['noDim'] - 1)
            self.__repres[randomNode] = randomCommunity
            for randomNodeNeighbour in self.__problParam['adj'][randomNode]:
                self.__repres[randomNodeNeighbour] = randomCommunity

        for i in range(self.__problParam['noDim']):
            if self.__repres[i] == -1:
                self.__repres[i] = randint(0, self.__problParam['noDim'] - 1) 
                
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
        r = choice(self.__repres)
        newrepres = []
        for index, val in enumerate(c.repres):
            if self.__repres[index] == r:
                newrepres.append(r)
            else:
                newrepres.append(val)

        offspring = Chromosome(c.__problParam)
        offspring.repres = newrepres
        return offspring
    
    def mutation(self):
        pos = randint(0, len(self.__repres) - 1)
        otherCommunity = choice(self.__repres)
        while self.__repres[pos] == otherCommunity:
            otherCommunity = choice(self.__repres)
        
    def __str__(self):
        return '\nChromo: ' + str(self.__repres) + ' has fit: ' + str(self.__fitness)
    
    def __repr__(self):
        return self.__str__()
    
    def __eq__(self, c):
        return self.__repres == c.__repres and self.__fitness == c.__fitness