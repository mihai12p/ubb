class Consola:
    def __init__(self, service):
        self.__serv = service

    def modificareUi(self):
        '''
        Interfata pentru modificarea genului si a datei date de utilizator pentru o melodie
        '''

        try:
            titlu = input('Introduceti titlul pentru care se doreste modificare: ')
            artist = input('Introduceti artistul pentru care se doreste modificare: ')
            gen = input('Introduceti genul: ')
            data = input('Introduceti data in formatul (dd.mm.yyyy): ')

            self.__serv.modifica(titlu, artist, gen, data)
        except Exception as f:
            print("EXCEPTII MODIFICARE: \n" + str(f))

    def genereazaUi(self):
        '''
        Interfata pentru generarea de melodii cu titluri si artisti dintr-o lista data de utilizator
        '''

        try:
            numar = int(input('Introduceti numarul de melodii de generat: '))
            lista = input('Introduceti lista de titluri si artisti si separati cele 2 subliste printr-o virgula: ')
            separare = [token for token in lista.split(', ')]
            lista_titluri = [token for token in separare[0].split(' ')]
            lista_artisti = [token for token in separare[1].split(' ')]
            
            self.__serv.genereaza(numar, lista_titluri, lista_artisti)
        except Exception as f:
            print("EXCEPTII GENERARE: \n" + str(f))

    def exportaUi(self):
        '''
        Interfata pentru exportarea de melodii intr-un fisier dat de utilizator
        '''

        try:
            nume_fisier = input('Introduceti numele fisierului pentru exportare: ')
            
            self.__serv.export(nume_fisier)
        except Exception as f:
            print("EXCEPTII EXPORTARE: \n" + str(f))

    def showUi(self):
        finishedMain = False
        while not finishedMain:
            print('Optiuni disponibile: mod, gen, exp, exit')
            optiune = input('Introduceti optiunea dorita: ')
            if optiune == 'mod':
                self.modificareUi()
            elif optiune == 'gen':
                self.genereazaUi()
            elif optiune == 'exp':
                self.exportaUi()
            elif optiune == 'exit':
                finishedMain = True