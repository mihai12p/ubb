class Console:
    def __init__(self, firmeService):
        self.__fservice = firmeService

    def __cauta(self):
        '''
        Cauta firme dupa numele acestora
        '''

        nume = input('Introduceti numele firmei pe care doriti sa il cautati: ')

        firme_gasite = self.__fservice.cauta(nume)
        for firma in firme_gasite:
            print(firma)

    def __calcul(self):
        '''
        Afiseaza numele firmei si soldul acesteia dupa o impozitare
        '''

        try:
            cuiFirma = int(input('Introduceti CUI-ul firmei: '))
            procent = int(input('Introduceti procentul: '))
        except:
            print('CUI (int), procent (int)')
            return

        firma = self.__fservice.findFirma(cuiFirma)
        firma_after_taxes = self.__fservice.get_sold_after_taxes(firma, procent)
        print('Numele firmei dupa impozitare: %s | Suma dupa impozitare %d' % (firma_after_taxes.getNume(), firma_after_taxes.getSold()))

    def showUi(self):
        finishedMain = False
        while not finishedMain:
            print('Optiuni disponibile: cauta, calcul, exit')
            option = input('Introduceti optiunea dorita: ')
            if option == 'cauta':
                self.__cauta()
            elif option == 'calcul':
                self.__calcul()
            elif option == 'exit':
                finishedMain = True
            else:
                print('Optiune invalida')
            