'''
P2. Gestiune laboratoare studenți
Scrieți o aplicație pentru gestiunea notelor și a problemelor de laborator pentru o disciplină. 
Aplicația gestionează:
    • studenți: <studentID>, <nume>, <grup>  
    • problemă laborator: <număr laborator_număr problemă>, <descriere>, <deadline>
Creați o aplicație care permite:
    • gestiunea listei de studenți și probleme de laborator.
    • adaugă, șterge, modifică, listă de studenți, listă de probleme
    • căutare student, căutare problemă
    • Asignare laborator/Notare laborator
    • Creare statistici:
        • lista de studenți și notele lor la o problema de laborator dat, ordonat: alfabetic după nume, după notă.
        • Toți studenții cu media notelor de laborator mai mic decât 5. (nume student și notă)
'''

from domain.validators import StudentValidator, TaskValidator, CommonValidator
from repository.repo import InMemoryStudentRepository, InMemoryTaskRepository, InMemoryCommonRepository
from service.serv import StudentService, TaskService, CommonService
from ui.console import Console

s_validator = StudentValidator()
s_repository = InMemoryStudentRepository()
s_service = StudentService(s_repository, s_validator)

t_validator = TaskValidator()
t_repository = InMemoryTaskRepository()
t_service = TaskService(t_repository, t_validator)

c_validator = CommonValidator()
c_repository = InMemoryCommonRepository()
c_service = CommonService(c_repository, c_validator, s_service, t_service)

ENABLE_SETUP = False
if ENABLE_SETUP:
    def setup():
        from domain.entities import Student, Task
        student1 = Student(12, 'Mihai Panduru', 215)
        student2 = Student(22, 'Adelin Gradinaru', 217)
        student3 = Student(23, 'Alberto Mihai', 213)

        s_repository.store(student1)
        s_repository.store(student2)
        s_repository.store(student3)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')
        task4 = Task('9_1', 'Parlament', '1/5/2024')

        t_repository.store(task1)
        t_repository.store(task2)
        t_repository.store(task3)
        t_repository.store(task4)

        c_repository.store(student1.getStudentId(), task1.getLaboratory_Task())
        c_repository.store(student1.getStudentId(), task4.getLaboratory_Task())
        c_repository.store(student3.getStudentId(), task1.getLaboratory_Task())
    setup()

ui = Console(s_service, t_service, c_service)
ui.showUI()
