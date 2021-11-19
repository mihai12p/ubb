'''
12.Determinati al n-lea element al șirului 
                 1,2,3,2,5,2,3,7,2,3,2,5,... 
    obținut din șirul numerelor naturale prin înlocuirea numerelor compuse prin 
    divizorii lor primi, fără a retine termenii șirului.
'''

n = int(input('n = '))
current = 0
i = 1
exit = False
while (exit == False):
    x = i
    d = 2
    ok = True
    current += 1

    while (x > 1 and d < i):
        if (x % d == 0):
            if ok == False:
                current += 1

            ok = False

        if (n == current):
            if (i % d == 0):
                print(d)
            else:
                print(i)
            exit = True
            break

        while (x % d == 0):
            x //= d

        d += 1
        if (d % 2 == 0):
            d += 1
    
    i += 1