from domain.scoreList import setParticipantName, setParticipantList, getParticipantName, getParticipantList

def copyScoreList(fullScoreList):
    '''
    Face o copie a listei de participanti

    paramtype: list of dictionaries
    rtype: list of dictionaries
    '''

    newCopiedScoreList = []
    for i in fullScoreList:
        newSubscoreList = {}
        setParticipantName(newSubscoreList, getParticipantName(i))
        setParticipantList(newSubscoreList, getParticipantList(i))

        newCopiedScoreList.append(newSubscoreList)

    return newCopiedScoreList

def test_copyScoreList():
    test_list = [{'name' : "Andrei", 'score' : [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]}, 
                    {'name' : "Ioana", 'score' : [7, 3, 3, 4, 5, 6, 6, 1, 9, 9]}, 
                    {'name' : "Camelia", 'score' : [8, 9, 3, 4, 5, 6, 7, 8, 9, 10]}, 
                    {'name' : "Dan", 'score' : [9, 9, 3, 4, 5, 6, 6, 1, 9, 9]}]

    second_test_list = copyScoreList(test_list)
    assert(id(test_list) != id(second_test_list))

test_copyScoreList()
