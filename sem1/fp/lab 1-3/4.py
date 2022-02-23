'''
4.  Dându-se numărul natural n, determina numerele prime p1 si p2 astfel ca 
                     n  = p1 + p2 
    (verificarea ipotezei lui Goldbach). Pentru ce fel de n exista soluție?
'''

# exista solutie pentru orice n par > 2

n = int(input('n = '))

def isPrim(x):
    if x <= 3:
        return x > 1
    elif (x % 2 == 0 or x % 3 == 0):
        return False
    else:
        start = 5
        while (start ** 2 <= x):
            if (x % start == 0 or x % (start + 2) == 0):
                return False

            start += 6
        
        return True

x = 2
while (x <= n // 2):
    if (isPrim(x) == True and isPrim(n - x) == True):
        print(x, n - x, n)
        break

    x += 1