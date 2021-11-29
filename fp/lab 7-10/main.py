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

import tests
from domain.validators import StudentValidator, TaskValidator, GradeValidator
from repository.repo import InMemoryStudentRepository, InMemoryTaskRepository, InMemoryGradeRepository, \
                            InFileStudentRepository, InFileTaskRepository, InFileGradeRepository
from service.serv import StudentService, TaskService, GradeService
from ui.console import Console

ENABLE_FILE = True
if not ENABLE_FILE:
    s_validator = StudentValidator()
    s_repository = InMemoryStudentRepository()
    s_service = StudentService(s_repository, s_validator)

    t_validator = TaskValidator()
    t_repository = InMemoryTaskRepository()
    t_service = TaskService(t_repository, t_validator)

    g_validator = GradeValidator()
    g_repository = InMemoryGradeRepository()
    g_service = GradeService(g_repository, g_validator, s_repository, t_repository)

    def setup():
        from domain.entities import Student, Task, Grade
        student1 = Student(12, 'Mihai Panduru', 215)
        student2 = Student(22, 'Adelin Gradinaru', 217)
        student3 = Student(23, 'Alberto Mihai', 213)
        student4 = Student(25, 'Kevin Axmann', 219)

        s_repository.store(student1)
        s_repository.store(student2)
        s_repository.store(student3)
        s_repository.store(student4)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')
        task4 = Task('9_1', 'Parlament', '1/5/2024')

        t_repository.store(task1)
        t_repository.store(task2)
        t_repository.store(task3)
        t_repository.store(task4)

        grade1 = Grade(student2.getStudentId(), task1.getLaboratory_Task(), 6)
        grade2 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 4)
        grade3 = Grade(student3.getStudentId(), task1.getLaboratory_Task(), 3)
        grade4 = Grade(student3.getStudentId(), task2.getLaboratory_Task(), 6.9)
        grade5 = Grade(student2.getStudentId(), task3.getLaboratory_Task(), 9)
        grade6 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 3)
        grade7 = Grade(student4.getStudentId(), task2.getLaboratory_Task(), 9)
        grade8 = Grade(student4.getStudentId(), task4.getLaboratory_Task(), 10)
        grade9 = Grade(student2.getStudentId(), task4.getLaboratory_Task(), 10)

        g_repository.store(grade1)
        g_repository.store(grade2)
        g_repository.store(grade3)
        g_repository.store(grade4)
        g_repository.store(grade5)
        g_repository.store(grade6)
        g_repository.store(grade7)
        g_repository.store(grade8)
        g_repository.store(grade9)
    setup()
else:
    s_validator = StudentValidator()
    s_file_repository = InFileStudentRepository('data/students.txt')
    s_service = StudentService(s_file_repository, s_validator)

    t_validator = TaskValidator()
    t_file_repository = InFileTaskRepository('data/tasks.txt')
    t_service = TaskService(t_file_repository, t_validator)

    g_validator = GradeValidator()
    g_file_repository = InFileGradeRepository('data/grades.txt')
    g_service = GradeService(g_file_repository, g_validator, s_file_repository, t_file_repository)

ui = Console(s_service, t_service, g_service)
ui.showUI()
