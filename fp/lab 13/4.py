'''
4. Se dă o listă de numere întregi a1,...,an, determinați toate sub-secvențele
(ordinea elementelor este menținută) strict crescătoare.
'''

import time
from termcolor import colored

def valid(list) -> bool:
    listLen = len(list)
    lastElemIndex = listLen - 1
    return not (listLen > 1 and list[lastElemIndex - 1] >= list[lastElemIndex])

def backtrackingRecursiv(solution, startIndex):
    solution.append(0)
    for i in range(startIndex, len(lst)):
        solution[-1] = lst[i]
        if (valid(solution)):
            print(solution)
            backtrackingRecursiv(solution, i + 1)
    solution.pop()

def validIterativ(list) -> bool:
    for i in range(0, len(list) - 1):
        if lst[list[i]] >= lst[list[i + 1]]:
            return False

    return True

def backtrackingIterativ():
    solution = [-1]
    while (len(solution) > 0):
        choosed = False
        while not choosed and solution[-1] < len(lst) - 1:
            solution[-1] += 1
            choosed = valid(solution)

        if choosed:
            if validIterativ(solution):
                print([lst[i] for i in solution])
            solution.append(-1)
        else:
            solution = solution[:-1]

lst = [int(num) for num in input("Introduceti elementele listei: ").split()]
solution = []

print(colored("Recursiv", "yellow"))
start = time.time()
backtrackingRecursiv(solution, 0)
print("Timp scurs: {}".format(time.time() - start))

print(colored("\nIterativ", "yellow"))
start = time.time()
backtrackingIterativ()
print("Timp scurs: {}".format(time.time() - start))
