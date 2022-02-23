from random import choice, randint

def randomFrom(listOfChoices):
    return ''.join(choice(listOfChoices))

def randomDate():
    zi = randint(1, 31)
    luna = randint(1, 12)
    an = randint(1980, 2022)

    ziFormalizata = '0'
    if (zi < 10): ziFormalizata += str(zi)
    else: ziFormalizata = str(zi)

    lunaFormalizata = '0'
    if (luna < 10): lunaFormalizata += str(luna)
    else: lunaFormalizata = str(luna)
    
    return str(ziFormalizata) + '.' + str(lunaFormalizata) + '.' + str(an)