Fiecare studnet primeste aplicatia unui coleg.<br>
Faceti code review pe aplicatia primita (CodeReviewTemplate.odt)<br>

Adaugati in aplicatia primita urmatoarele:<br>
1 Undo multiplu <br>
   - utilizatorul poate face undo la operatiile: adauga/modifica/sterge<br>
   - utilizatorul poate face undo de mai multe ori.<br>
2 O noua varianta de filtrare<br>

Obs: Functionalitata undo se implementeaza folosind o lista de liste.<br>

In proiect trebuie sa existe un modul (si doar unu singur) care implementeaza conceptul de lista folosind structura de vector dinamic.<br>

  Implementarea voastra de lista trebuie sa functioneze si in cazul in care vreau lista de liste. Practic lista o sa contina elemente de tip void*.<br>

Acordati atentie gestiunii memoriei (alocare/delocare, cum facem copierea listei, etc). Este important ca lista depusa in lista de undo sa fie o lista total independenta de lista curenta de obiecte.<br>

Cerinte obligatorii (nu se preia laboratorul daca nu sunt satisfacute toate):<br>
   1 un singur modul care implementeaza lista folosind structura vector dinamic folosit si la undo si la lista de obiecte (void*)<br>
   2 Test Code coverage 100% pe toate modulele in afara de UI<br>
   3 Fara memory leak.<br>
   4 Fara warninguri (in Visual Studio warning level /W4, treat warning as errors).<br>
      E vorba de warninguri de la compilator, unele medii de dezvoltare ofera si alte warninguri <br>
      (Ex. In Visual Studio in Error List apar atat warninguri de la compilator cat si warninguri de la IntelliSense)<br>

Timp de lucru 1 saptamana.
