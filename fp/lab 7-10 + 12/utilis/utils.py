from random import choices, randint
from string import ascii_lowercase, ascii_uppercase

def randomNumber() -> int:
    return randint(0, 1000)

def randomString() -> str:
   letters = ascii_lowercase + ascii_uppercase

   return ''.join(choices(letters, k = randint(1, 15)))

def recursive_sum(list) -> int:
    if list == []:
        return 0
    
    return list[0] + recursive_sum(list[1:])

def recursive_counter(list) -> int:
    if list == []:
        return 0
    
    if list[0]:
        return 1 + recursive_counter(list[1:])

def insertion_sort(sir, *, key = None, reverse = False):
    for index in range(1, len(sir)):
        valCurenta = sir[index]
        pozCurenta = index
        if key:
            while pozCurenta > 0 and key(sir[pozCurenta - 1]) > key(valCurenta):
                sir[pozCurenta] = sir[pozCurenta - 1]
                pozCurenta -= 1
        else:
            while pozCurenta > 0 and sir[pozCurenta - 1] > valCurenta:
                sir[pozCurenta] = sir[pozCurenta - 1]
                pozCurenta -= 1

        sir[pozCurenta] = valCurenta

    if reverse:
        return sir[::-1]

    return sir
  
def comb_sort(sir, *, key = None, reverse = False):
    distanta = len(sir)
    interschimbat = True
    while distanta > 1 or interschimbat == True:
        distanta = max(1, int(distanta / 1.3))
        interschimbat = False
        for i in range(0, len(sir) - distanta):
            if key:
                if key(sir[i]) > key(sir[i + distanta]):
                    sir[i], sir[i + distanta] = sir[i + distanta], sir[i]
                    interschimbat = True
            else:
                if sir[i] > sir[i + distanta]:
                    sir[i], sir[i + distanta] = sir[i + distanta], sir[i]
                    interschimbat = True

    if reverse:
        return sir[::-1]

    return sir

def compare(s1, s2):
    if s1.getStudent().getStudentName() > s2.getStudent().getStudentName():
        return 1
    elif s1.getStudent().getStudentName() > s2.getStudent().getStudentName():
        return -1
    else:
        if s1.getGrade() > s2.getGrade():
            return 1
        elif s1.getGrade() > s2.getGrade():
            return -1
        else:
            return 0
