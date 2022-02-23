'''
6. Găsește cel mai mic număr m din șirul lui Fibonacci definit de 
           f[0]=f[1]=1, f[n]=f[n-1]+f[n-2], pentru n>2, 
   mai mare decât numărul natural n dat, deci exista k astfel ca f[k]=m si m>n.
'''

def f():
    a = b = 1
    n = int(input('n (numar natural) = '))

    while True:
        c = a + b
        a = b

        if (a > n):
            print('m =', a)
            break

        b = c

f()
