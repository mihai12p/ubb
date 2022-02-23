from domain.entities import Melodie

class Validator:
    '''
    Clasa ce valideaza eventualele modificari ce urmeaza sa apara
    '''

    def valid(self, melodie, data, gen):
        '''
        paramtype: class, str, str
        data = data de verificat
        gen = genul de verificat
        melodie = melodie daca exista sau None daca nu exista

        se arunca o exceptie ce cumuleaza toate neregularitatile gasite in datele de intrare
        '''

        errors = []

        if melodie == None:
            errors.append('Nu a fost gasita o melodie cu acest titlu si artist.')

        (zi, luna, an) = [token.strip() for token in data.split('.')]
        if int(zi) < 1 or int(zi) > 31 or len(zi) != 2:
            errors.append('Ziua trebuie sa fie cuprinsa intre 1-31 sub forma dd.')
        if int(luna) < 1 or int(luna) > 12 or len(luna) != 2:
            errors.append('Luna trebuie sa fie cuprinsa intre 1-12 sub forma mm.')
        if len(an) != 4:
            errors.append('Anul trebuie sa fie sub forma yyyy.')

        if gen not in ['Rock', 'Pop', 'Jazz', 'Altele']:
            errors.append('Genul trebuie sa fie Rock, Pop, Jazz sau Altele.')

        if len(errors) > 0:
            raise Exception(errors)

def test_valid():
    valid = Validator()
    
    melodie = Melodie('Highway to hell', 'AC\DC', 'Rock', '12.11.2003')

    valid.valid(melodie, '12.12.2012', 'Altele')

    try:
        valid.valid(melodie, '00.00.199', 'Manele')
        assert False
    except:
        assert True

    try:
        valid.valid(None, '12.12.2022', 'Metal')
        assert False
    except:
        assert True

    try:
        valid.valid(melodie, '12.12.2022', 'Clasica')
        assert False
    except:
        assert True

test_valid()