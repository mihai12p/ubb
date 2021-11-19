def bye():
    '''
    Functie ce opreste executia programului
    '''

    print("Pe curand :)")
    exit()

def chooseAnOption():
    '''
    Functie interfata utlizator

    return: optiunea utilizatorului daca aceasta este in intervalul [1, 4], altfel se apeleaza functia de iesire [bye()]
    return type: int, None
    '''

    print("         1 - Cititi o lista de numere intregi")
    print("         2 - Se cauta secventele de lungime maxima cu proprietatea x[i] < x[i+1] < ... < x[i+p] unde i, p ∈ ℕ")
    print("         3 - Se cauta secventele de lungime maxima cu proprietatea ca toate elementele apartin de intervalul dat [0, 10]")
    print("         4 - Se cauta secventa de lungime maxima cu proprietatea de a contine cel mult trei valori distincte")
    print("         5 - Iesire din aplicatie")

    i = int(input('Alegeti optiunea dorita '))
    if i < 5 and i > 0:
        return i
    else:
        bye()

def task2(list):
    '''
    Functie ce rezolva cerinta 2

    param: lista cu elemente
    param type: list
    '''

    print("Secventele ce indeplinesc proprietatea ceruta sunt")

    if len(list) == 1: # daca lista are un singur element
        print(list[0:1]) # il afisam deoarece sigur satisface cerinta

    count = 1
    maximum = 0
    for i in range(0, len(list) - 1):
        if list[i] < list[i + 1]:
            count += 1
        else:
            count = 1

        if count > maximum:
            maximum = count

    if maximum == 1: # daca toate elementele sunt in ordine descrescatoare
        for i in list: # parcurgem toata lista
            print([i]) # afisam fiecare element independent ca fiind o secventa ce satisface conditia
        
        return

    count = 1
    for i in range(0, len(list) - 1):
        if list[i] < list[i + 1]:
            count += 1
        else:
            count = 1

        if count == maximum:
            sequenceStart = (i + 1) - count + 1 # [i + 1](range(0, len(list) - 1)) == [i](range(1, len(list)))
            print(list[sequenceStart : sequenceStart + maximum])
            
def task3(list):
    '''
    Functie ce rezolva cerinta 3

    param: lista cu elemente
    param type: list
    '''

    print("Secventele ce indeplinesc proprietatea ceruta sunt")

    count = 0
    maximum = 0
    for i in list:
        if i >= 0 and i <= 10:
            count += 1
        else:
            count = 0

        if count > maximum:
            maximum = count

    count = 0
    for i, e in enumerate(list):
        if e >= 0 and e <= 10:
            count += 1
        else:
            count = 0

        if count == maximum and count != 0:
            sequenceStart = i - count + 1
            print(list[sequenceStart : sequenceStart + maximum])

def task4(list):
    '''
    Functie ce rezolva cerinta 4 (cerinta din timpul lab3)

    param: lista cu elemente
    param type: list
    '''

    print("Secventa ce indeplineste proprietatea ceruta este")
    
    maximum = 0
    for index in range(len(list) - 2):
        first = list[index]
        firstIndex = index
        lastIndex = index

        while index + 1 < len(list) and first == list[index + 1]:
            index += 1

        lastIndex = index

        if index + 1 < len(list):
            index += 1
            second = list[index]

            while index + 1 < len(list) and (first == list[index + 1] or second == list[index + 1]):
                index += 1

            lastIndex = index

            if index + 1 < len(list):
                index += 1
                third = list[index]
            
                while index + 1 < len(list) and (first == list[index + 1] or second == list[index + 1] or third == list[index + 1]):
                    index += 1

                lastIndex = index

        count = lastIndex - firstIndex + 1
        if count > maximum:
            sequenceIndexStart = firstIndex
            sequenceIndexEnd = lastIndex
            maximum = count

        #print(first, second, third, count)

    print(list[sequenceIndexStart : sequenceIndexEnd + 1])

def fillTheList():
    '''
    Functie ce populeaza o lista cu numere intregi si o returneaza

    return: lista cu elemente
    return type: list
    '''

    print("Introduceti elementele in ordinea dorita separate printr-un spatiu: ")

    lst = [int(x) for x in input().split()]
    print("Elementele listei sunt", lst)

    return lst

def start():
    '''
    Functia de start a programului
    '''

    print("Bun venit!")
    i = chooseAnOption()

    while i != 1:
        print("Alegeti prima optiune pentru a citi o lista de numere mai intai :)")
        i = chooseAnOption()

    lst = fillTheList()

    i = chooseAnOption()
    while i < 5 and i > 0:
        while i == 1 and lst:
            print("Lista contine deja elementele", lst)
            i = chooseAnOption()

        if i == 2:
            task2(lst)
        elif i == 3:
            task3(lst)
        else:
            task4(lst)

        i = chooseAnOption()

    bye()

start()
