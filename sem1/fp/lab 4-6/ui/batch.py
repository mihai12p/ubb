from termcolor import colored
from domain.participant import createScoreListForParticipant, computeAverageScoreForSublist, undoListFunc
from domain.scoreList import getParticipantName, getParticipantList

def printCurrentScoreList(fullScoreList):
    '''
    Afiseaza lista curenta

    paramtype: list of dictionaries
    '''

    for participant in fullScoreList:
        print(colored(getParticipantName(participant), 'yellow'), colored(getParticipantList(participant), 'cyan'))

    print(colored('Total participanti: %d\n' % len(fullScoreList), 'magenta'))

def printBatchMenu():
    '''
    Afiseaza tabelul cu cerintele principale
    '''

    print(colored("Separati instructiunile printr-un ;", 'green'))
    print(colored("Optiunea", 'green'), colored("add [index] [scor]", 'yellow'), colored("- Adauga un scor la un participant", 'blue'))
    print(colored("Optiunea", 'green'), colored("afiseaza", 'yellow'), colored("- Afiseaza lista curenta", 'blue'))
    print(colored("Optiunea", 'green'), colored("calc [start] [stop]", 'yellow'), colored("- Calculeaza media scorurilor pentru un interval dat", 'blue'))
    print(colored("Optiunea", 'green'), colored("undo", 'yellow'), colored("- Undo ultima operatie", 'blue'))
    print(colored("Optiunea", 'green'), colored("inchide", 'yellow'), colored("- Inchide programul", 'blue'))


def getActionFromBatchDict(dict):
    return dict['action']

def getArg1FromBatchDict(dict):
    return dict['arg1']

def getArg2FromBatchDict(dict):
    return dict['arg2']

def getBatchInputUi(fullScoreList, undoList):
    try:
        mainOption = input('Optiunile dumneavoastra sunt: ').split(';')
        fullList = []
        for i in mainOption:
            dict = {}
            listForAdd = []

            for j in i.split():
                if 'arg1' in dict:
                    if getActionFromBatchDict(dict) == 'add':
                        listForAdd.append(int(j))
                    else:
                        dict.update({'arg2' : j})
                elif 'action' in dict:
                    dict.update({'arg1' : j})
                else:
                    dict.update({'action' : j})

            if getActionFromBatchDict(dict) == 'add':
                dict.update({'arg2' : listForAdd})

            fullList.append(dict)

        for i in fullList:
            if getActionFromBatchDict(i) == 'add':
                try:
                    createScoreListForParticipant(fullScoreList, undoList, getArg2FromBatchDict(i), int(getArg1FromBatchDict(i)))
                except Exception as ValueError:
                    print(colored(ValueError, 'red'))
            elif getActionFromBatchDict(i) == 'afiseaza':
                printCurrentScoreList(fullScoreList)
            elif getActionFromBatchDict(i) == 'calc':
                try:
                    print("Media scorurilor pentru intervalul specificat este:", colored(computeAverageScoreForSublist(fullScoreList[int(getArg1FromBatchDict(i)) - 1 : int(getArg2FromBatchDict(i))]), 'cyan'))
                except Exception as ValueError:
                    print(colored(ValueError, 'red'))
            elif getActionFromBatchDict(i) == 'undo':
                try:
                    undoListFunc(fullScoreList, undoList)
                except Exception as ValueError:
                    print(colored(ValueError, 'red'))
            elif getActionFromBatchDict(i) == 'inchide':
                return 1
            else:
                return 0
            
    except Exception as ValueError:
        print(colored(ValueError, 'red'))
