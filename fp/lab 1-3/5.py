'''
5. Determina numerele prime p1 si p2 gemene imediat superioare numărului 
    natural nenul n dat. Doua numere prime p si q sunt gemene 
    daca q-p = 2.

input: 1       expected output: 3 5
input: 2       expected output: 3 5
input: 3       expected output: 5 7
input: 9       expected output: 11 13
input: 12      expected output: 17 19
input: 100     expected output: 101 103
input: 25      expected output: 29 31
input: 31      expected output: 41 43
input: 43      expected output: 59 61
input: 1451253 expected output: 1451717 1451719
'''

n = int(input('n (numar natural nenul) = '))

def isPrim(x):
    if x <= 3:
        return x > 1
    elif (x % 2 == 0 or x % 3 == 0):
        return False
    
    i = 5
    while i ** 2 <= x:
        if (x % i == 0 or x % (i + 2) == 0):
            return False

        i += 6
    
    return True

n += 1
if (n % 2 == 0):
    n += 1

while (isPrim(n) == False or isPrim(n + 2) == False):
    n += 2

print(n, n + 2)