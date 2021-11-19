'''
9.  Palindromul unui număr este numărul obținut prin scrierea cifrelor in ordine 
    inversa (Ex. palindrom(237) = 732). Pentru un n dat calculați palindromul sau.
'''

n = int(input('n = '))

x = 0
while n != 0:
    x = x * 10 + n % 10
    n //= 10

print(x) 