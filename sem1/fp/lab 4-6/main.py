'''
P2. Concurs 
Se cere să creăm o aplicație pentru gestiunea concurenților de la un concurs de programare. 
Programul înregistrează scorul obținut de fiecare concurent la 10 probe diferite, 
fiecare probă este notat cu un scor de la 1 la 10. Fiecare participant este 
identificat printr-un număr de concurs, scorul este ținut într-o listă unde 
concurentul 3 are scorul pe poziția 3 în listă. Programul trebuie sa ofere următoarele funcționalități:

1. Adaugă un scor la un participant. 
    • Adaugă scor pentru un nou participant (ultimul participant) 
    • Inserare scor pentru un participant. 
2. Modificare scor. 
    • Șterge scorul pentru un participant dat. 
    • Șterge scorul pentru un interval de participanți. 
    • Înlocuiește scorul de la un participant. 
3. Tipărește lista de participanți. 
    • Tipărește participanții care au scor mai mic decât un scor dat. 
    • Tipărește participanții ordonat după scor 
    • Tipărește participanții cu scor mai mare decât un scor dat, ordonat după scor.  
4. Operații pe un subset de participanți. 
    • Calculează media scorurilor pentru un interval dat (ex. Se da 1 și 5 se tipărește media scorurilor participanților 1,2,3,4 și 5)
    • Calculează scorul minim pentru un interval de participanți dat. 
    • Tipărește participanții dintr-un interval dat care au scorul multiplu de 10. 
5. Filtrare. 
    • Filtrare participanți care au scorul multiplu unui număr dat. Ex. Se da numărul 10, se elimină scorul de la toți participanții care nu au scorul multiplu de 10. 
    • Filtrare participanți care au scorul mai mic decât un scor dat. 
6. Undo 
    • Reface ultima operație (lista de scoruri revine la numerele ce existau înainte de ultima operație care a modificat lista) – Nu folosiți funcția deepCopy 
'''

from ui.console import start

start()
