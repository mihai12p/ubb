from domain.entities import Impozitare

class FirmeSrv:
    def __init__(self, repo, valid):
        self.__repo = repo
        self.__valid = valid

    def get_all(self):
        return self.__repo.get_all()

    def cauta(self, nume):
        '''
        Cauta firme dupa numele acestora

        paramtype: nume (str)
        rtype: Firma (class)
        '''

        firme_gasite = []

        get_all_list = self.get_all()
        for firma in get_all_list:
            if nume.lower() in firma.getNume().lower():
                firme_gasite.append(firma)
        
        return firme_gasite

    def findFirma(self, cui):
        return self.__repo.findFirma(cui)

    def get_sold_after_taxes(self, firma, procent):
        '''
        Impoziteaza o firma cu un procent

        paramtype: Firma (class), procent (int)
        rtype: Firma (class)
        '''

        firma_impozitata = Impozitare(firma, procent)

        sold = firma_impozitata.getFirma().getSold()
        taxa_impozit = firma_impozitata.getProcent() * sold // 100
        sold -= taxa_impozit

        firma_impozitata.getFirma().setSold(sold)

        self.__repo.saveToFile()

        return firma_impozitata.getFirma()
