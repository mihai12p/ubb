'''
2. Se da data nașterii (zi/luna/an), determinați vârsta persoanei in zile.
'''

import datetime

day = int(input('day = '))
month = int(input('month = '))
year = int(input('year = '))

days = 365
if (year % 4 == 0):
    days += 1

print((datetime.datetime.now().year - year) * days + (datetime.datetime.now().month - month) * 30 + datetime.datetime.now().day - day)
