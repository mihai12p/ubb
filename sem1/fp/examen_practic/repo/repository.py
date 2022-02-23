from domain.entities import Melodie

class InMemoryGestiune:
    '''
    Clasa ce retine in memorie lista curenta de melodii
    '''

    def __init__(self):
        self.__memory = []

    def adauga(self, melodie):
        self.__memory.append(melodie)

    def sterge(self, melodie):
        self.__memory.remove(melodie)

    def get_all(self):
        return self.__memory

    def findMelodie(self, titlu, artist):
        '''
        paramtype: str, str
        Cauta o melodie in lista si o returneaza daca exista
        '''

        for melodie in self.__memory:
            if melodie.getTitlu() == titlu and melodie.getArtist() == artist:
                return melodie

    def modifica(self, melodie, gen, data):
        '''
        paramtype: class, str, str
        Modifica genul si data unei melodii
        '''

        melodie.setGen(gen)
        melodie.setData(data)

def test_adauga():
    repo = InMemoryGestiune()

    melodie = Melodie('Highway to hell', 'AC\DC', 'Rock', '12.11.2003')
    repo.adauga(melodie)

    assert len(repo.get_all()) == 1
    assert repo.get_all()[0].getTitlu() == 'Highway to hell'

def test_sterge():
    repo = InMemoryGestiune()

    melodie = Melodie('Highway to hell', 'AC\DC', 'Rock', '12.11.2003')
    melodie2 = Melodie('Thunderstruck', 'AC\DC', 'Rock', '01.02.2005')
    repo.adauga(melodie)
    repo.adauga(melodie2)

    assert len(repo.get_all()) == 2
    
    repo.sterge(melodie)

    assert len(repo.get_all()) == 1
    assert repo.get_all()[0].getTitlu() == 'Thunderstruck'

def test_findMelodie():
    repo = InMemoryGestiune()

    melodie = Melodie('Highway to hell', 'AC\DC', 'Rock', '12.11.2003')
    melodie2 = Melodie('Thunderstruck', 'AC\DC', 'Rock', '01.02.2005')
    repo.adauga(melodie)
    repo.adauga(melodie2)
    
    assert repo.findMelodie('Thunderstruck', 'AC\DC') == melodie2
    assert repo.findMelodie('Hells Bells', 'AC\DC') == None

def test_modifica():
    repo = InMemoryGestiune()

    melodie = Melodie('Highway to hell', 'AC\DC', 'Rock', '12.11.2003')
    melodie2 = Melodie('Thunderstruck', 'AC\DC', 'Rock', '01.02.2005')
    repo.adauga(melodie)
    repo.adauga(melodie2)

    repo.modifica(melodie, 'Altele', '01.02.2005')
    repo.modifica(melodie2, 'Jazz', '12.11.2003')
    
    assert repo.get_all()[0].getGen() == 'Altele'
    assert repo.get_all()[1].getData() == '12.11.2003'

test_adauga()
test_sterge()
test_findMelodie()
test_modifica()

class InFileGestiune(InMemoryGestiune):
    '''
    Clasa ce se foloseste de lista din memorie pentru operatii externe (cu fisiere)
    '''

    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.loadFromFile()

    def loadFromFile(self):
        '''
        Citeste informatiile din fisier
        '''

        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                (titlu, artist, gen, data) = [token.strip() for token in line.split('; ')]
                melodie = Melodie(titlu, artist, gen, data)
                self.adauga(melodie)

    def saveToFile(self):
        '''
        Salveaza informatiile in fisier
        '''
        memory = self.get_all()
        with open(self.__filename, 'w') as f:
            for melodie in memory:
                linie = melodie.getTitlu() + '; ' + melodie.getArtist() + '; ' + melodie.getGen() + '; ' + melodie.getData() + '\n'
                f.write(linie)

    def adauga(self, melodie):
        super().adauga(melodie)
        self.saveToFile()

    def sterge(self, melodie):
        super().sterge(melodie)
        self.saveToFile()

    def get_all(self):
        return super().get_all()

    def findMelodie(self, titlu, artist):
        return super().findMelodie(titlu, artist)

    def modifica(self, melodie, gen, data):
        super().modifica(melodie, gen, data)
        self.saveToFile()