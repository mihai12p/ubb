'''
1. Găsiți primul număr prim mai mare decât un număr dat.
'''

def isPrim(x):
    if (x <= 3):
        return x > 1
    elif (x % 2 == 0 or x % 3 == 0):
        return False

    i = 5
    while i ** 2 <= x:
        if (x % i == 0 or x % (i + 2) == 0):
            return False
        i += 6

    return True

def prim(x):
    if (x < 2):
        print('2')
        return
    elif (x == 2):
        print('3')
        return

    if (x % 2 == 0):
        if (isPrim(x + 1) == True):
            print(x + 1)
            return
        else:
            x += 1

    while (isPrim(x + 2) == False):
        x += 2
    
    print(x + 2)

x = int(input('x = '))
prim(x)