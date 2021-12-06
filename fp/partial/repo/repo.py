from domain.entities import Firma

class FirmeFileRepo:
    def __init__(self, fisier):

        self.__firme = []
        self.__fisier = fisier

        self.loadFromFile()

    def loadFromFile(self):
        '''
        Incarca datele din fisier
        '''

        with open(self.__fisier, 'r') as f:
            lines = f.readlines()
            for line in lines:
                cui, nume, sold = [x for x in line.split(', ')]
                firma = Firma(int(cui), nume, int(sold))
                self.add(firma)

    def saveToFile(self):
        '''
        Salveaza datele in fisier
        '''

        with open(self.__fisier, 'w') as f:
            for firma in self.__firme:
                line = str(firma.getCui()) + ', ' + firma.getNume() + ', ' + str(firma.getSold()) + '\n'
                f.write(str(line))

    def get_all(self):
        return self.__firme

    def findFirma(self, cui):
        '''
        Cauta o firma dup CUI-ul acesteia
        '''

        for firma in self.__firme:
            if firma.getCui() == cui:
                return firma

    def add(self, firma):
        self.__firme.append(firma)

def test_load_from_file():
    repo = FirmeFileRepo('data/firme.txt')

    try:
        repo.loadFromFile()
        assert True
    except:
        assert False

test_load_from_file()
