'''
7. Fie n un număr natural dat. Calculați produsul p al tuturor factorilor 
    proprii ai lui n.
'''

n = int(input('n = '))

prod = 1
i = 2
while (i ** 2 < n):
    if (n % i == 0):
        prod *= i
        prod *= n // i

    i += 1
  
if (i ** 2 == n):
    prod *= i

print(prod)