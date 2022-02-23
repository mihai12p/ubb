from termcolor import colored
from domain.scoreList import setup, defineUndoList
from domain.participant import deleteScoreForParticipant, filterParticipantsByReferenceScore, \
    sortParticipantsByScore, filterParticipantsByReferenceNumber, computeMinScoreForSublist, \
    createScoreListForParticipant, computeAverageScoreForSublist, undoListFunc
from ui.batch import printBatchMenu, getBatchInputUi, printCurrentScoreList

def printMenuFor(mainOption):
    '''
    Afiseaza tabelul cu cerintele secundare in functie de cerinta principala

    paramtype: int
    '''

    if mainOption == 1:
        print(colored("     Optiunea", 'green'), colored("1", 'yellow'), colored("- Adauga scor pentru un nou participant", 'blue'))
        print(colored("     Optiunea", 'green'), colored("2", 'yellow'), colored("- Adauga scor pentru un participant existent", 'blue'))
        print(colored("     Optiunea", 'green'), colored("3", 'yellow'), colored("- Intoarcere la meniul principal", 'blue'))
    elif mainOption == 2:
        print(colored("     Optiunea", 'green'), colored("1", 'yellow'), colored("- Sterge scorul pentru un participant dat", 'blue'))
        print(colored("     Optiunea", 'green'), colored("2", 'yellow'), colored("- Sterege scorul pentru un interval de participanti", 'blue'))
        print(colored("     Optiunea", 'green'), colored("3", 'yellow'), colored("- Inlocuieste scorul unui participant", 'blue'))
        print(colored("     Optiunea", 'green'), colored("4", 'yellow'), colored("- Intoarcere la meniul principal", 'blue'))
    elif mainOption == 3:
        print(colored("     Optiunea", 'green'), colored("1", 'yellow'), colored("- Tipareste participantii care au un scor mai mic decat un scor dat", 'blue'))
        print(colored("     Optiunea", 'green'), colored("2", 'yellow'), colored("- Tipareste participantii ordonati dupa scor", 'blue'))
        print(colored("     Optiunea", 'green'), colored("3", 'yellow'), colored("- Tipareste participantii cu scor mai mare decat un scor dat, ordonati dupa scor", 'blue'))
        print(colored("     Optiunea", 'green'), colored("4", 'yellow'), colored("- Intoarcere la meniul principal", 'blue'))
    elif mainOption == 4:
        print(colored("     Optiunea", 'green'), colored("1", 'yellow'), colored("- Calculeaza media scorurilor pentru un interval dat", 'blue'))
        print(colored("     Optiunea", 'green'), colored("2", 'yellow'), colored("- Calculeaza scorul minim pentru un interval de participanti dat", 'blue'))
        print(colored("     Optiunea", 'green'), colored("3", 'yellow'), colored("- Tipareste participantii dintr-un interval dat care au scorul multiplu de 10", 'blue'))
        print(colored("     Optiunea", 'green'), colored("4", 'yellow'), colored("- Intoarcere la meniul principal", 'blue'))
    elif mainOption == 5:
        print(colored("     Optiunea", 'green'), colored("1", 'yellow'), colored("- Filtreaza participantii care au scorul multiplu unui numar dat", 'blue'))
        print(colored("     Optiunea", 'green'), colored("2", 'yellow'), colored("- Filtreaza participantii care au scorul mai mic decat un scor dat", 'blue'))
        print(colored("     Optiunea", 'green'), colored("3", 'yellow'), colored("- Intoarcere la meniul principal", 'blue'))
    elif mainOption == 6:
        print(colored("     Optiunea", 'green'), colored("1", 'yellow'), colored("- Undo (revenire la lista dinaintea ultimei operatii)", 'blue'))
        print(colored("     Optiunea", 'green'), colored("2", 'yellow'), colored("- Intoarcere la meniul principal", 'blue'))

def printMenu():
    '''
    Afiseaza tabelul cu cerintele principale
    '''

    print(colored("Optiunea", 'green'), colored("1", 'yellow'), colored("- Adauga un scor la un participant", 'blue'))
    print(colored("Optiunea", 'green'), colored("2", 'yellow'), colored("- Modifica scorul unui participant", 'blue'))
    print(colored("Optiunea", 'green'), colored("3", 'yellow'), colored("- Tipareste lista de participanti", 'blue'))
    print(colored("Optiunea", 'green'), colored("4", 'yellow'), colored("- Operatii pe un subset de participanti", 'blue'))
    print(colored("Optiunea", 'green'), colored("5", 'yellow'), colored("- Filtreaza lista de participanti", 'blue'))
    print(colored("Optiunea", 'green'), colored("6", 'yellow'), colored("- Undo ultima operatie", 'blue'))
    print(colored("Optiunea", 'green'), colored("7", 'yellow'), colored("- Afiseaza lista curenta", 'blue'))
    print(colored("Optiunea", 'green'), colored("8", 'yellow'), colored("- Inchide programul", 'blue'))

def createScoreListForParticipantUi(fullScoreList, undoList, option, participantIndex = 0):
    try:
        newName = 'default'
        if participantIndex == -1:
            newName = input('Introduceti numele participantului: ')

        scoreList = list(int(x) for x in input('Introduceti scorul obtinut de participant la cele 10 probe: ').split())
        if option == 2:
            participantIndex = int(input('Introduceti numarul participantului pentru care solicitati adaugarea scorului: '))
        elif option == 3:
            participantIndex = int(input('Introduceti numarul participantului pentru care solicitati inlocuirea scorului: '))

        createScoreListForParticipant(fullScoreList, undoList, scoreList, participantIndex, newName)

        if option == 1:
            print(colored("Scorul noului participant a fost adaugat cu succes.", 'magenta'))
        elif option == 2:
            print(colored("Scorul participantului %d a fost adaugat cu succes." % participantIndex, 'magenta'))
        elif option == 3:
            print(colored("Scorul participantului %d a fost inlocuit cu succes." % participantIndex, 'magenta'))

    except Exception as ValueError:
        print(colored(ValueError, 'red'))
        
def deleteScoreForParticipantUi(fullScoreList, undoList, option):
    try:
        if option == 1:
            participantIndex = int(input('Introduceti numarul participantului pentru care solicitati stergerea scorului: '))
            deleteScoreForParticipant(fullScoreList, undoList, participantIndex)
            print(colored("Scorul participantului %d a fost sters cu succes." % participantIndex, 'magenta'))
        elif option == 2:
            participantsRange = list(int(x) for x in input('Introduceti intervalul de participanti pentru care solicitati stergerea scorului sub forma startInterval stopInterval": ').split())
            deleteScoreForParticipant(fullScoreList, undoList, participantsRange)
            print(colored("Scorul intervalului de participanti %s a fost sters cu succes." % participantsRange, 'magenta'))
    
    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def filterParticipantsByReferenceScoreUi(fullScoreList, option):
    try:
        if option == 1:
            referenceScore = list(int(x) for x in input('Introduceti scorul de referinta la cele 10 probe: ').split())
            print("Participantii care au scorul mai mic decat scorul dat:", colored(filterParticipantsByReferenceScore(fullScoreList, referenceScore), 'cyan'))
        elif option == 2:
            print("Participantii ordonati in functie de scor:", colored(sortParticipantsByScore(fullScoreList), 'cyan'))
        elif option == 3:
            referenceScore = list(int(x) for x in input('Introduceti scorul de referinta la cele 10 probe: ').split())
            print("Participantii care au scorul mai mare decat scorul dat, ordonat dupa scor:", colored(sortParticipantsByScore(filterParticipantsByReferenceScore(fullScoreList, referenceScore, True)), 'cyan'))      
   
    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def filterParticipantsByReferenceNumberUi(fullScoreList, option):
    try:
        if option == 1:
            referenceNumber = float(input('Introduceti numarul de referinta: '))
            print("Participantii care au scorul multiplu unui numar dat:", colored(filterParticipantsByReferenceNumber(fullScoreList, referenceNumber), 'cyan'))
        elif option == 3:
            participantsRange = list(int(x) for x in input('Introduceti intervalul de participanti pentru care solicitati afisarea scorului sub forma startInterval stopInterval: ').split())
            print("Participantii din intevalul %s care au scorul multiplu de 10 sunt:" % participantsRange, colored(filterParticipantsByReferenceNumber(fullScoreList[participantsRange[0] - 1 : participantsRange[1]], 1.0), 'cyan'))
    
    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def computeScoreForSublistUi(fullScoreList, option):
    try:
        if option == 1:
            participantsRange = list(int(x) for x in input('Introduceti intervalul de participanti pentru care solicitati calcularea mediei scorului sub forma startInterval stopInterval: ').split())
            print("Media scorurilor pentru intervalul %s este:" % participantsRange, colored(computeAverageScoreForSublist(fullScoreList[participantsRange[0] - 1 : participantsRange[1]]), 'cyan'))
        elif option == 2:
            participantsRange = list(int(x) for x in input('Introduceti intervalul de participanti pentru care solicitati calcularea scorului minim sub forma startInterval stopInterval: ').split())
            print("Scorul minim pentru intervalul %s este:" % participantsRange, colored(computeMinScoreForSublist(fullScoreList[participantsRange[0] - 1 : participantsRange[1]]), 'cyan'))
    
    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def start():
    fullScoreList = setup(True)
    undoList = defineUndoList()
    finishedMain = False

    initialMenu = int(input('Batch = 1 / Select = 2: '))
    if initialMenu == 2:
        while not finishedMain:
            printMenu()
            mainOption = int(input('Optiunea dumneavoastra primara este: '))
            if mainOption == 1:
                finishedSecondary = False
                while not finishedSecondary:
                    printMenuFor(mainOption)
                    secondaryOption = int(input('Optiunea dumneavoastra secundara este: '))
                    if secondaryOption == 1:
                        createScoreListForParticipantUi(fullScoreList, undoList, secondaryOption, -1)
                    elif secondaryOption == 2:
                        createScoreListForParticipantUi(fullScoreList, undoList, secondaryOption)
                    elif secondaryOption == 3:
                        finishedSecondary = True
                    else:
                        print(colored("Optiune invalida.", 'red'))
            elif mainOption == 2:
                finishedSecondary = False
                while not finishedSecondary:
                    printMenuFor(mainOption)
                    secondaryOption = int(input('Optiunea dumneavoastra secundara este: '))
                    if secondaryOption == 1:
                        deleteScoreForParticipantUi(fullScoreList, undoList, secondaryOption)
                    elif secondaryOption == 2:
                        deleteScoreForParticipantUi(fullScoreList, undoList, secondaryOption)
                    elif secondaryOption == 3:
                        createScoreListForParticipantUi(fullScoreList, undoList, secondaryOption)
                    elif secondaryOption == 4:
                        finishedSecondary = True
                    else:
                        print(colored("Optiune invalida.", 'red'))
            elif mainOption == 3:
                finishedSecondary = False
                while not finishedSecondary:
                    printMenuFor(mainOption)
                    secondaryOption = int(input('Optiunea dumneavoastra secundara este: '))
                    if secondaryOption == 1:
                        filterParticipantsByReferenceScoreUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 2:
                        filterParticipantsByReferenceScoreUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 3:
                        filterParticipantsByReferenceScoreUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 4:
                        finishedSecondary = True
                    else:
                        print(colored("Optiune invalida.", 'red'))
            elif mainOption == 4:
                finishedSecondary = False
                while not finishedSecondary:
                    printMenuFor(mainOption)
                    secondaryOption = int(input('Optiunea dumneavoastra secundara este: '))
                    if secondaryOption == 1:
                        computeScoreForSublistUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 2:
                        computeScoreForSublistUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 3:
                        filterParticipantsByReferenceNumberUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 4:
                        finishedSecondary = True
                    else:
                        print(colored("Optiune invalida.", 'red'))
            elif mainOption == 5:
                finishedSecondary = False
                while not finishedSecondary:
                    printMenuFor(mainOption)
                    secondaryOption = int(input('Optiunea dumneavoastra secundara este: '))
                    if secondaryOption == 1:
                        filterParticipantsByReferenceNumberUi(fullScoreList, secondaryOption)
                    elif secondaryOption == 2:
                        filterParticipantsByReferenceScoreUi(fullScoreList, secondaryOption - 1)
                    elif secondaryOption == 3:
                        finishedSecondary = True
                    else:
                        print(colored("Optiune invalida.", 'red'))
            elif mainOption == 6:
                finishedSecondary = False
                while not finishedSecondary:
                    printMenuFor(mainOption)
                    secondaryOption = int(input('Optiunea dumneavoastra secundara este: '))
                    if secondaryOption == 1:
                        undoListFunc(fullScoreList, undoList)
                    elif secondaryOption == 2:
                        finishedSecondary = True
                    else:
                        print(colored("Optiune invalida.", 'red'))
            elif mainOption == 7:
                printCurrentScoreList(fullScoreList)
            elif mainOption == 8:
                finishedMain = True
            else:
                print(colored("Optiune invalida.", 'red'))
    else:
        while not finishedMain:
            printBatchMenu()
            option = getBatchInputUi(fullScoreList, undoList)
            if option == 1:
                finishedMain = True
            elif option == 0:
                print(colored("Optiune invalida.", 'red'))
