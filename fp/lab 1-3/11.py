'''
11. Numerele n1 si n2 au proprietatea P daca scrierile lor in baza 10 conțin 
    aceleași cifre (ex. 2113 si 323121). Determinați daca doua numere naturale 
    au proprietatea P. 
'''

n1 = int(input('n1 = '))
n2 = int(input('n2 = '))

dig1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
dig2 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

while (n1 != 0 and n2 != 0):
    dig1[n1 % 10] = 1
    dig2[n2 % 10] = 1
    n1 //= 10
    n2 //= 10

while (n1 != 0):
    dig1[n1 % 10] = 1
    n1 //= 10

while (n2 != 0):
    dig2[n2 % 10] = 1
    n2 //= 10

P = True

for i, j in zip(dig1, dig2):
    if dig1[i] != dig2[j]:
        P = False
        break

print(P)