class Melodie:
    '''
    Clasa entitate pentru fiecare obiect melodie
    '''

    def __init__(self, titlu, artist, gen, data_apartiei):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__data = data_apartiei

    def getTitlu(self):
        return self.__titlu

    def getArtist(self):
        return self.__artist

    def getGen(self):
        return self.__gen

    def getData(self):
        return self.__data

    def setTitlu(self, titluNou):
        self.__titlu = titluNou

    def setArtist(self, artistNou):
        self.__artist = artistNou

    def setGen(self, genNou):
        self.__gen = genNou

    def setData(self, dataNoua):
        self.__data = dataNoua

    def __str__(self):
        return self.__titlu + ' ' + self.__artist + ' ' + self.__gen + ' ' + self.__data