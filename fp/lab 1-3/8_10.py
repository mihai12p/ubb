'''
8. Pentru un număr natural n dat găsiți numărul natural maxim m format cu 
    aceleași cifre. Ex. n=3658,   m=8653.
'''

EIGHT = False

'''
10. Pentru un număr natural n dat găsiți numărul natural minim m format cu 
    aceleași cifre. Ex. n=3658,   m=3568.
'''

n = int(input('n = '))

digL = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

while n != 0:
    digL[n % 10] = 1
    n //= 10

if EIGHT:
    p = 1
    for i, e in enumerate(digL):
        if (e == 1):
            n += i * p
            p *= 10
else:
    p = 1
    for i, e in reversed(list(enumerate(digL))):
        if (e == 1):
            n += i * p
            p *= 10

print(n)