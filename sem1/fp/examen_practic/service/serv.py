from functools import cmp_to_key
from domain.validator import Validator
from repo.repository import InMemoryGestiune
from utils.rand import randomFrom, randomDate
from domain.entities import Melodie

class Service:
    def __init__(self, repository, validator):
        self.__repo = repository
        self.__validator = validator

    def modifica(self, titlu, artist, gen, data):
        '''
        paramtype: str, str, str, str
        Modifica genul si data unei melodii

        Se arunca exceptie in caz ca nu exista melodie sau datele de intrare nu sunt valide
        '''

        cauta = self.__repo.findMelodie(titlu, artist)
        self.__validator.valid(cauta, data, gen)
        self.__repo.modifica(cauta, gen, data)

    def genereaza(self, numar, lista_titluri, lista_artisti):
        '''
        paramtype: int, list, list
        Genereaza melodii alegand random titluri din lista_titluri si artisti din lista_artisti

        Se arunca exceptie in caz ca datele de intrare nu sunt valide
        '''

        for i in range(numar):
            titlu = randomFrom(lista_titluri)
            artist = randomFrom(lista_artisti)
            gen = randomFrom(['Rock', 'Pop', 'Jazz', 'Altele'])
            data = randomDate()

            melodie = Melodie(titlu, artist, gen, data)
            self.__validator.valid(melodie, data, gen)
            self.__repo.adauga(melodie)

    def export(self, nume_fisier):
        '''
        paramtype: str
        Exporteaza intr-un fisier melodiile din memorie sortate crescator in functie de data

        Se arunca exceptie in caz ca datele de intrare nu sunt valide
        '''

        def compare(data1, data2):
            '''
            paramtype: class, class
            Compara 2 date

            Returneaza 1 daca data1 > data2, altfel -1
            '''

            (zi, luna, an) = [int(token) for token in data1.getData().split('.')]
            (zi2, luna2, an2) = [int(token) for token in data2.getData().split('.')]
            
            if (an2 > an):
                return -1
            elif (an2 < an):
                return 1
            else:
                if luna > luna2:
                    return 1
                elif luna < luna2:
                    return -1
                else:
                    if zi < zi2:
                        return -1
                    else:
                        return 1

        sorted_list = sorted(self.__repo.get_all(), key = cmp_to_key(compare))
        with open(nume_fisier, 'w') as f:
            for melodie in sorted_list:
                linie = 'Artist: ' + melodie.getArtist() + ' Titlu: ' + melodie.getTitlu() + ' Data: ' + melodie.getData() + ' Gen: ' + melodie.getGen() + '\n'
                f.write(linie)

def test_modifica():
    repo = InMemoryGestiune()
    validator = Validator()
    service = Service(repo, validator)

    melodie = Melodie('Highway to hell', 'AC\DC', 'Rock', '12.11.2003')
    melodie2 = Melodie('Thunderstruck', 'AC\DC', 'Rock', '01.02.2005')
    repo.adauga(melodie)
    repo.adauga(melodie2)

    service.modifica('Highway to hell', 'AC\DC', 'Altele', '01.02.2005')
    service.modifica('Thunderstruck', 'AC\DC', 'Jazz', '12.11.2003')

    assert repo.get_all()[0].getGen() == 'Altele'
    assert repo.get_all()[1].getData() == '12.11.2003'

    try:
        service.modifica('Hells Bells', 'AC\DC', 'Jazz', '12.11.2003')
        assert False
    except:
        assert True

def test_genereaza():
    repo = InMemoryGestiune()
    validator = Validator()
    service = Service(repo, validator)

    service.genereaza(5, ['ABC', 'CDE', 'FGH'], ['123', '456', '789'])
    assert len(repo.get_all()) == 5

test_modifica()
test_genereaza()