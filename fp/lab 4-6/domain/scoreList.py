from utils.dict_operations import copyDict

def getPredefinedScoreList():
    '''
    Returneaza o lista cu scoruri predefinite

    rtype: list of dictionaries
    '''

    return [
        {'name' : "Andrei", 'score' : [1, 2, 3, 1, 3, 4, 5, 6, 7, 28]},
        {'name' : "Briana", 'score' : [51, 52, 53, 54, 55, 56, 57, 58, 59, 60]},
        {'name' : "Oana", 'score' : [61, 62, 63, 64, 65, 66, 67, 68, 69, 70]},
        {'name' : "Timeea", 'score' : [1, 2, 3, 4, 106, 6, 7, 8, 9, 10]},
        {'name' : "Daria", 'score' : [1, 2, 3, 1, 3, 4, 5, 6, 7, 8]},
        {'name' : "Raluca", 'score' : [11, 12, 13, 14, 15, 16, 17, 18, 19, 20]},
        {'name' : "Ana", 'score' : [21, 22, 23, 24, 25, 26, 27, 28, 29, 32]},
        {'name' : "Bianca", 'score' : [31, 32, 33, 34, 35, 36, 37, 38, 39, 40]},
        {'name' : "Iraida", 'score' : [41, 42, 43, 44, 45, 46, 47, 48, 49, 50]},
        {'name' : "Andra", 'score' : [1, 2, 3, 1, 3, 4, 5, 6, 7, 18]}
    ]

def defineUndoList():
    '''
    undoList este o lista de dictionare, fiecare dictionar avand urmatoarele chei cu urmatoarele semnificatii:
        - operationToDo : operatia pe care trebuie sa o faca undoList (altfel spus: un reverse la un 'doList')
            -- 'reviveScoreList', 'reviveScoreListFor1', 'resetScoreList', 'pop'
        - arg : argumentul pe care il cautam in lista actuala pentru a fi modificat cum a fost inainte
        - dest : argument ce contine datele dinainte de a fi modificate
    '''

    return []

def getParticipantName(scoreList):
    return scoreList['name']

def getParticipantList(scoreList):
    return scoreList['score']

def setParticipantName(scoreList, newName):
    scoreList['name'] = newName

def setParticipantList(scoreList, newList):
    scoreList['score'] = newList

def getUndoAction(undoDict):
    return undoDict['operationToDo']

def getUndoArg(undoDict):
    return undoDict['arg']

def getUndoDest(undoDict):
    return undoDict['dest']

def validateScoreList(scoreList):
    '''
    Valideaza scorul unui participant

    paramtype: list
    raise if the score does not meet requirements
    '''

    err = []

    if len(scoreList) != 10:
        err.append('Participantul trebuie sa aiba 10 scoruri, cate unul pentru fiecare proba.')

    for score in scoreList:
        if score < 1 or score > 10:
            err.append('Scorul obtinut la o proba poate fi intre 1-10 inclusiv.')
            break

    if len(err) > 0:
        errSep = '\n'.join(err)
        raise ValueError(errSep)

def validateNewParticipant(name, scoreList):
    '''
    Valideaza datele unui nou participant

    paramtype: string, list
    raise if the score or the name does not meet requirements
    '''

    err = []
    if name == 'default' or len(name) < 2:
        err.append('Participantul trebuie sa aiba un nume alcatuit din minim 2 caractere.')
    
    validateScoreList(scoreList)

    if len(err) > 0:
        errSep = '\n'.join(err)
        raise ValueError(errSep)

def validateExistingParticipant(scoreList, position, fullScoreListLen):
    '''
    Valideaza datele unui participant existent

    paramtype: list, int, int
    raise if the score or the position does not meet requirements
    '''

    err = []
    if position >= fullScoreListLen or position < 0:
        err.append('Participantul specificat nu exista.')

    validateScoreList(scoreList)

    if len(err) > 0:
        errSep = '\n'.join(err)
        raise ValueError(errSep)

def createNewScoreList(fullScoreList, undoList, scoreList, newName):
    '''
    Creeaza o noua lista de scoruri pentru un nou participant

    paramtype: list of lists, list of dictionaries, list, string
    '''

    validateNewParticipant(newName, scoreList)

    newDictScoreList = {}
    setParticipantName(newDictScoreList, newName)
    setParticipantList(newDictScoreList, scoreList)
    fullScoreList.append(newDictScoreList)

    undoList.append({'operationToDo' : 'pop', 'arg' : newDictScoreList, 'dest' : {}})

def insertNewScoreList(fullScoreList, undoList, scoreList, position):
    '''
    Insereaza o noua lista de scoruri pentru un participant existent

    paramtype: list of lists, list of dictionaries, list, int
    '''

    validateExistingParticipant(scoreList, position, len(fullScoreList))
    
    retForUndo = copyDict(fullScoreList[position])
    undoList.append({'operationToDo' : 'resetScoreList', 'arg' : position, 'dest' : retForUndo})

    setParticipantList(fullScoreList[position], scoreList)

def getNameAndScoreListFromDict(dict):
    '''
    Extrage doar valorile cheilor dintr-un dictionar

    paramtype: dict
    rtype: tuple
    '''

    return (getParticipantName(dict), getParticipantList(dict))

def setup(predefined):
    '''
    Initializeaza cele necesare pentru gestiunea participantilor

    paramtype: boolean
    rtype: list / list of dictionaries
    '''

    if predefined:
        fullScoreListSetup = getPredefinedScoreList()
    else:
        fullScoreListSetup = []
    
    return fullScoreListSetup

def test_validateScoreList():
    try:
        scoreList = [1, 2, 3, 4, 5, 6, 7, 8, 11, 10]
        validateScoreList(scoreList)

    except Exception as ValueError:
        assert(str(ValueError) == 'Scorul obtinut la o proba poate fi intre 1-10 inclusiv.')

    try:
        scoreList = [1, 2, 3, 4, 5, 6, 7, 8, 10, 10, 10]
        validateScoreList(scoreList)

    except Exception as ValueError:
        assert(str(ValueError) == 'Participantul trebuie sa aiba 10 scoruri, cate unul pentru fiecare proba.')

def test_validateNewParticipant():
    try:
        name = ''
        scoreList = [1, 2, 3, 4, 5, 6, 7, 8, 10, 10]
        validateNewParticipant(name, scoreList)

    except Exception as ValueError:
        assert(str(ValueError) == 'Participantul trebuie sa aiba un nume alcatuit din minim 2 caractere.')

def test_validateExistingParticipant():
    try:
        position = 11
        fullScoreListLen = 10
        scoreList = [1, 2, 3, 4, 5, 6, 7, 8, 10, 10]
        validateExistingParticipant(scoreList, position, fullScoreListLen)

    except Exception as ValueError:
        assert(str(ValueError) == 'Participantul specificat nu exista.')

test_validateScoreList()
test_validateNewParticipant()
test_validateExistingParticipant()