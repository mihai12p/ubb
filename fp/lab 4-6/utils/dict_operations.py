def copyDict(dictToCopy):
    '''
    Face o copie a unui dictionar

    paramtype: dict
    rtype: dict
    '''

    newCopiedDict = {}
    for key in dictToCopy:
        newCopiedDict[key] = dictToCopy[key]

    return newCopiedDict

def test_copyDict():
    test_dict = {'operationToDo' : 'pop', 'arg' : [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 'dest' : 123}

    second_test_dict = copyDict(test_dict)
    assert(id(test_dict) != id(second_test_dict))

test_copyDict()