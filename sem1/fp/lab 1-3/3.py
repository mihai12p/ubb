'''
3. Determina o data calendaristica (sub forma an, luna, zi) pornind de 
    la doua numere întregi care reprezintă anul si numărul 
    de ordine al zilei in anul respectiv.
'''

from datetime import date

year = int(input('year = '))
dayOfTheYear = int(input('dayOfTheYear = '))

monthTup = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)

month = 0
while (dayOfTheYear > monthTup[month]):
    dayOfTheYear -= monthTup[month]
    month += 1

print(date(year, month + 1, dayOfTheYear))
