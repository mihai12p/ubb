class Firma:
    def __init__(self, cui, nume, sold):
        self.__cui = cui
        self.__nume = nume
        self.__sold = sold

    def getCui(self):
        return self.__cui

    def getNume(self):
        return self.__nume

    def getSold(self):
        return self.__sold

    def setCui(self, cuiNou):
        self.__cui = cuiNou

    def setNume(self, numeNou):
        self.__nume = numeNou

    def setSold(self, soldNou):
        self.__sold = soldNou
    
    def __str__(self):
        return 'CUI: ' + str(self.__cui) + ' NUME: ' + self.__nume + ' SOLD: ' + str(self.__sold)

class Impozitare:
    def __init__(self, firma, procent):
        self.__firma = firma
        self.__procent = procent

    def getFirma(self):
        return self.__firma

    def getProcent(self):
        return self.__procent
