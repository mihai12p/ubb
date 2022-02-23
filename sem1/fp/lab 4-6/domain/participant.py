from termcolor import colored
from utils.list_operations import copyScoreList
from utils.dict_operations import copyDict
from domain.scoreList import createNewScoreList, getPredefinedScoreList, insertNewScoreList, getParticipantList, \
    getNameAndScoreListFromDict, setParticipantList, validateScoreList, getUndoAction, getUndoArg, getUndoDest

def createScoreListForParticipant(fullScoreList, undoList, scoreList, participantIndex, newName = 'default'):
    '''
    Creeaza o noua lista de scoruri pentru un participant.

    paramtype: list of dictionaries / list of dictionaries / list / int / (str)
    '''

    if participantIndex == -1:
        createNewScoreList(fullScoreList, undoList, scoreList, newName)
    else:
        insertNewScoreList(fullScoreList, undoList, scoreList, participantIndex - 1)

def deleteScoreForParticipant(fullScoreList, undoList, participantIndex = -1):
    '''
    Sterge scorul pentru unul sau mai multi participanti

    paramtype: list of dictionaries / list of dictionaries / int
    '''

    if type(participantIndex) == list:
        startPosition = participantIndex[0] - 1
        endPosition = participantIndex[1]

        if startPosition > endPosition:
            raise ValueError('Pozitia de start nu poate fi mai mare ca cea de sfarsit.')

        if startPosition >= len(fullScoreList) or startPosition < 0 or endPosition > len(fullScoreList) or endPosition < 0:
            raise ValueError('Pozitiile trebuie sa coincida cu pozitia unor participanti existenti.')

        retForUndo = copyScoreList(fullScoreList[startPosition : endPosition])
        undoList.append({'operationToDo' : 'reviveScoreList', 'arg' : [startPosition, endPosition], 'dest' : retForUndo})

        for position in range(startPosition, endPosition):
            setParticipantList(fullScoreList[position], [])
    else:
        position = participantIndex - 1
        if position >= len(fullScoreList) or position < 0:
            raise ValueError('Pozitia trebuie sa coincida cu pozitia unui participant existent.')

        retForUndo = copyDict(fullScoreList[position])
        undoList.append({'operationToDo' : 'reviveScoreListFor1', 'arg' : position, 'dest' : retForUndo})

        setParticipantList(fullScoreList[position], [])

def getParticipantAverageScoreByScoreList(scoreList):
    '''
    Returneaza media aritmetica a notelor unui participant. (scorul mediu a unui participant)

    paramtype: list
    rtype: float
    '''

    if len(scoreList) == 0:
        return 0.0

    average = sum(scoreList) / len(scoreList)
    return average

def filterParticipantsByReferenceScore(scoreList, referenceScore, descending = False):
    '''
    Filtreaza participantii in functie de scorul pe care l-au obtinut in raport cu scorul dat

    paramtype: list of dictionaries / list / boolean
    rtype: list of (lists / dictionaries) (depinde de valoarea parametrului descending)
    '''

    validateScoreList(referenceScore)

    newFilteredParticipantsScoreList = []
    averageReferenceScore = sum(referenceScore) / len(referenceScore)

    for participantScore in scoreList:
        if not descending:
            if getParticipantAverageScoreByScoreList(getParticipantList(participantScore)) < averageReferenceScore:
                newFilteredParticipantsScoreList.append(getNameAndScoreListFromDict(participantScore))
        else:
            if getParticipantAverageScoreByScoreList(getParticipantList(participantScore)) > averageReferenceScore:
                newFilteredParticipantsScoreList.append(participantScore)

    return newFilteredParticipantsScoreList

def filterParticipantsByReferenceNumber(scoreList, referenceNumber):
    '''
    Filtreaza participantii in functie de multiplul unui numar dat

    paramtype: list of dictionaries / float
    rtype: list of dictionaries
    '''

    newFilteredParticipantsScoreList = []

    for participantIndex, participantScore in enumerate(scoreList):
        if round(getParticipantAverageScoreByScoreList(getParticipantList(participantScore)) % referenceNumber, 1) == 0.0:
            newFilteredParticipantsScoreList.append([getParticipantAverageScoreByScoreList(getParticipantList(participantScore)), getParticipantList(participantScore)])

    return newFilteredParticipantsScoreList

def sortParticipantsByScore(scoreList):
    '''
    Sorteaza participantii in functie de scorul pe care l-au obtinut

    paramtype: list of lists
    rtype: list of lists
    '''

    newSortedParticipantsList = copyScoreList(scoreList)

    for index in range(len(newSortedParticipantsList) - 1):
        for jndex in range(index + 1, len(newSortedParticipantsList)):
                firstParticipantList = getParticipantList(newSortedParticipantsList[index])
                secondParticipantList = getParticipantList(newSortedParticipantsList[jndex])
                if getParticipantAverageScoreByScoreList(firstParticipantList) > getParticipantAverageScoreByScoreList(secondParticipantList):
                    newSortedParticipantsList[index], newSortedParticipantsList[jndex] = newSortedParticipantsList[jndex], newSortedParticipantsList[index]

    for index, elem in enumerate(newSortedParticipantsList):
        newSortedParticipantsList[index] = getNameAndScoreListFromDict(elem)

    return newSortedParticipantsList

def computeAverageScoreForSublist(scoreList):
    '''
    Calculeaza media scorurilor unui interval dat de participanti
    
    paramtype: list
    rtype: float
    '''

    newAverageList = []

    for participantScore in scoreList:
        participantAverage = getParticipantAverageScoreByScoreList(getParticipantList(participantScore))
        newAverageList.append(participantAverage)

    subListAverage = round(getParticipantAverageScoreByScoreList(newAverageList), 1)
    return subListAverage

def computeMinScoreForSublist(scoreList):
    '''
    Calculeaza scorul minim pentru un interval de participanti
    
    paramtype: list
    rtype: float
    '''

    minimum = float('inf')
    for participantScore in scoreList:
        participantAverage = getParticipantAverageScoreByScoreList(getParticipantList(participantScore))
        if participantAverage < minimum:
            minimum = participantAverage

    return minimum

def undoListFunc(fullScoreList, undoList):
    '''
    Actioneaza refacerea ultimei operatii
    
    paramtype: list of dictionaries / list of dictionaries
    catches in case of lists.pop() raises (no elements to pop())
    '''

    try:
        getLastStackedUndoElement = undoList.pop()
        actionToDo = getUndoAction(getLastStackedUndoElement)
        prevVals = getUndoArg(getLastStackedUndoElement)
        destVals = getUndoDest(getLastStackedUndoElement)

        if actionToDo == 'resetScoreList' or actionToDo == 'reviveScoreListFor1':
            fullScoreList[prevVals] = destVals
        elif actionToDo == 'reviveScoreList':
            (start, end) = prevVals
            fullScoreList[start : end] = destVals
        elif actionToDo == 'pop':
            fullScoreList.pop()

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_getParticipantAverageScoreByScoreList():
    assert(getParticipantAverageScoreByScoreList([1, 2, 3, 4, 5]) == 3)
    assert(getParticipantAverageScoreByScoreList([15, 21, 33]) == 23)
    assert(getParticipantAverageScoreByScoreList([55, 55, 55, 55, 55, 55, 55, 55, 55, 55]) == 55)
    assert(getParticipantAverageScoreByScoreList([0]) == 0)
    assert(getParticipantAverageScoreByScoreList([-1, -5, 0, 1, 2, 3]) == 0)

def test_createScoreListForParticipant():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana")
        assert(len(test_list) == 1)
        assert(getParticipantList(test_list[0])[1] == 2)
        assert(getParticipantList(test_list[0])[9] == 10)

        createScoreListForParticipant(test_list, undo_list, [7, 5, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto")
        assert(len(test_list) == 2)
        assert(getParticipantList(test_list[1])[1] == 5)
        assert(getParticipantList(test_list[1])[9] == 9)

        createScoreListForParticipant(test_list, undo_list, [9, 9, 9, 9, 9, 9, 9, 9, 9, 9], 1)
        assert(len(test_list) == 2)
        assert(getParticipantList(test_list[0])[1] == 9)

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_deleteScoreForParticipant():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana")
        createScoreListForParticipant(test_list, undo_list, [7, 5, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto")

        deleteScoreForParticipant(test_list, undo_list, 1)
        assert(len(test_list) == 1)
        assert(getParticipantList(test_list[0])[1] == 2)

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_filterParticipantsByReferenceScore():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana")
        createScoreListForParticipant(test_list, undo_list, [7, 3, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto")
        createScoreListForParticipant(test_list, undo_list, [8, 9, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Nicu")
        createScoreListForParticipant(test_list, undo_list, [9, 9, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Ion")

        assert(filterParticipantsByReferenceScore(test_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == [('Alberto', [7, 3, 3, 4, 5, 6, 6, 1, 9, 9])])
        assert(filterParticipantsByReferenceScore(test_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], True) == [{'name': 'Nicu', 'score': [8, 9, 3, 4, 5, 6, 7, 8, 9, 10]}, {'name': 'Ion', 'score': [9, 9, 3, 4, 5, 6, 6, 1, 9, 9]}])
    
    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_sortParticipantsByScore():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana")
        createScoreListForParticipant(test_list, undo_list, [7, 3, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto")
        createScoreListForParticipant(test_list, undo_list, [8, 9, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Nicu")
        createScoreListForParticipant(test_list, undo_list, [9, 9, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Ion")
    
        assert(sortParticipantsByScore(test_list) == [('Alberto', [7, 3, 3, 4, 5, 6, 6, 1, 9, 9]), ('Ana', [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]), ('Ion', [9, 9, 3, 4, 5, 6, 6, 1, 9, 9]), ('Nicu', [8, 9, 3, 4, 5, 6, 7, 8, 9, 10])])

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_filterParticipantsByReferenceNumber():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana") # 5.5
        createScoreListForParticipant(test_list, undo_list, [7, 3, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto") # 5.3
        createScoreListForParticipant(test_list, undo_list, [8, 9, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Nicu") # 6.9
        createScoreListForParticipant(test_list, undo_list, [9, 9, 3, 4, 5, 6, 6, 1, 8, 9], -1, "Ion") # 6.0

        assert(filterParticipantsByReferenceNumber(test_list, 0.5) == [[5.5, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]], [6.0, [9, 9, 3, 4, 5, 6, 6, 1, 8, 9]]])
        assert(filterParticipantsByReferenceNumber(test_list, 2.3) == [[6.9, [8, 9, 3, 4, 5, 6, 7, 8, 9, 10]]])

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_computeAverageScoreForSublist():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana") # 5.5
        createScoreListForParticipant(test_list, undo_list, [7, 3, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto") # 5.3
        createScoreListForParticipant(test_list, undo_list, [8, 9, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Nicu") # 6.9
        createScoreListForParticipant(test_list, undo_list, [9, 9, 3, 4, 5, 6, 6, 1, 8, 9], -1, "Ion") # 6.0
        assert(computeAverageScoreForSublist(test_list) == 5.9)

        createScoreListForParticipant(test_list, undo_list, [7, 3, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Ion") # 5.3
        assert(computeAverageScoreForSublist(test_list) == 5.8)

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_computeMinScoreForSublist():
    try:
        test_list = []
        undo_list = []

        createScoreListForParticipant(test_list, undo_list, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Ana") # 5.5
        createScoreListForParticipant(test_list, undo_list, [7, 3, 3, 4, 5, 6, 6, 1, 9, 9], -1, "Alberto") # 5.3
        createScoreListForParticipant(test_list, undo_list, [8, 9, 3, 4, 5, 6, 7, 8, 9, 10], -1, "Nicu") # 6.9
        createScoreListForParticipant(test_list, undo_list, [9, 9, 3, 4, 5, 6, 6, 1, 8, 9], -1, "Ion") # 6.0
        assert(computeMinScoreForSublist(test_list) == 5.3)

        createScoreListForParticipant(test_list, undo_list, [1, 2, 1, 2, 1, 2, 1, 2, 1, 2], -1, "Ion") # 1.5
        assert(computeMinScoreForSublist(test_list) == 1.5)

    except Exception as ValueError:
        print(colored(ValueError, 'red'))

def test_undoListFunc():
    fullScoreList = getPredefinedScoreList()
                                                      # 1 in realitate deoarece in mintea noastra indexam de la 1
                                                        #    |
                                                        #    ^
    undoList = [{'operationToDo' : 'resetScoreList', 'arg' : 0, 'dest' : {'name': 'Andrei', 'score': [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]}},
                {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}}, {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}}, 
                {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}}, {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}},
                {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}}, {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}},
                {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}}, {'operationToDo' : 'pop', 'arg' : {}, 'dest' : {}}]

    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #pop
    undoListFunc(fullScoreList, undoList) #resetScoreList
    assert(fullScoreList == [{'name': 'Andrei', 'score': [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]}, {'name': 'Briana', 'score': [51, 52, 53, 54, 55, 56, 57, 58, 59, 60]}])

test_getParticipantAverageScoreByScoreList()
test_createScoreListForParticipant()
test_deleteScoreForParticipant()
test_filterParticipantsByReferenceScore()
test_sortParticipantsByScore()
test_filterParticipantsByReferenceNumber()
test_computeAverageScoreForSublist()
test_computeMinScoreForSublist()
test_undoListFunc()
