from collections import defaultdict
from domain.entities import Student, Task
from utilis.dict_operations import get_key_from_dict, get_dict_from_arguments

class RepositoryException(Exception):
    pass

class InMemoryStudentRepository:
    '''
    Stocheaza multimea de studenti
    '''

    def __init__(self):
        '''
        __students = multimea de studenti stocati
        '''

        self.__students = []

    def store(self, student):
        self.__students.append(student)

    def remove(self, student):
        self.__students.remove(student)

    def get_all_students(self) -> list[Student]:
        return self.__students

    def get_student_by_ID(self, studentId) -> Student:
        '''
        Returneaza studentul identificat dupa ID-ul acestuia
        '''

        for student in self.__students:
            if student.getStudentId() == studentId:
                return student

def test_get_student_by_ID():
    repository = InMemoryStudentRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Alberto Mihai', 215)

    repository.store(student1)
    repository.store(student2)

    assert(repository.get_student_by_ID(1001) == student1)
    assert(repository.get_student_by_ID(1003) == student2)

test_get_student_by_ID()

class InMemoryTaskRepository:
    '''
    Stocheaza multimea de probleme
    '''

    def __init__(self):
        '''
        __tasks = multimea de probleme stocate
        '''

        self.__tasks = []

    def store(self, task):
        self.__tasks.append(task)

    def remove(self, task):
        self.__tasks.remove(task)

    def get_all_tasks(self) -> list[Task]:
        return self.__tasks

    def get_task_by_arg(self, laboratory_task) -> Task:
        '''
        Returneaza problema identificata dupa ID-ul acesteia
        '''

        for tsk in self.__tasks:
            if tsk.getLaboratory_Task() == laboratory_task:
                return tsk

def test_get_task_by_arg():
    repository = InMemoryTaskRepository()

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')

    repository.store(task1)
    repository.store(task2)

    assert(repository.get_task_by_arg('7_2') == task1)
    assert(repository.get_task_by_arg('8_4') == task2)

test_get_task_by_arg()

class InMemoryCommonRepository:
    '''
    Stocheaza multimea de studenti si problemele atribuite
    '''

    def __init__(self):
        '''
        __combined = multimea de studenti, fiecare cu problemele atribuite
        __combined este un dictionar de forma { studentId : [ probleme + note ]}
                        ++ lista de probleme + note este de form contine cate un dictionar pentru fiecare problema
                                si nota pentru aceasta de exemplu {'8_4':None} cand nu a fost notat laboratorul
                                si {'8_4':10} cand nota acordata a fost 10 
                (exemplu) ==> __combined = { studentId : [ {'8_4' : None}, {'7_2' : 9}, {'9_1' : None} ] }
        '''

        self.__combined = defaultdict(list)
        self.__grade = None

    def store(self, studentId, laboratory_task):
        self.__combined[studentId].append(get_dict_from_arguments(laboratory_task, self.__grade))

    def evaluate(self, studentId, laboratory_task, grade):
        '''
        Adauga o nota pentru o problema atribuita unui student

        nota = grade
        '''

        for index, taskDict in enumerate(self.__combined[studentId]):
            if get_key_from_dict(taskDict) == laboratory_task:
                self.__combined[studentId][index] = get_dict_from_arguments(laboratory_task, grade)
                break

    def removeStudent(self, studentId):
        '''
        Elimina un student din lista de probleme cu studentii atribuiti atunci cand aceasta a fost sters
        '''

        self.__combined.pop(studentId)

    def removeTask(self, laboratory_task):
        '''
        Elimina o problema din lista de probleme atribuita studentilor atunci cand aceasta a fost stearsa
        '''

        for studentId, tsk in self.__combined.items():
            for tskNum in tsk:
                if get_key_from_dict(tskNum) == laboratory_task:
                    self.__combined[studentId].remove(tskNum)
                    break

    def update_student(self, studentId, newStudentId):
        '''
        Actualizeaza lista de probleme atribuite studentilor atunci cand datele unui student sunt actualizate
        '''

        self.__combined[newStudentId] = self.__combined.pop(studentId)

    def update_task(self, laboratory_task, newLaboratory_task):
        '''
        Actualizeaza lista de probleme atribuite studentilor atunci cand datele unei probleme sunt schimbate
        '''

        for studentId, tsk in self.__combined.items():
            for index, tskNum in enumerate(tsk):
                if get_key_from_dict(tskNum) == laboratory_task:
                    self.__combined[studentId][index] = get_dict_from_arguments(newLaboratory_task, self.__grade)
                    break

    def get_student_with_tasks(self, studentId) -> dict:
        '''
        Returneaza problemele atribuite studentului dupa ID-ul acestuia
        '''
        
        return self.__combined[studentId]

    def get_task_with_students(self, laboratory_task) -> list[Student]:
        '''
        Returneaza stundetii atribuiti problemei dupa ID-ul acesteia
        '''

        __students = []

        for studentId, tsk in self.__combined.items():
            for tskNum in tsk:
                if get_key_from_dict(tskNum) == laboratory_task:
                    __students.append(studentId)
                    break

        return __students

def test_get_student_with_tasks():
    repository = InMemoryCommonRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Adelin Gradinaru', 217)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')
    task3 = Task('7_3', 'Revelion', '12/1/2022')
    task4 = Task('9_1', 'Parlament', '1/5/2024')

    repository.store(student1.getStudentId(), task2.getLaboratory_Task())
    repository.store(student1.getStudentId(), task3.getLaboratory_Task())
    repository.store(student1.getStudentId(), task1.getLaboratory_Task())

    assert(repository.get_student_with_tasks(student1.getStudentId()) == [{'8_4': None}, {'7_3': None}, {'7_2': None}])

    repository.store(student2.getStudentId(), task1.getLaboratory_Task())
    repository.store(student2.getStudentId(), task4.getLaboratory_Task())

    assert(repository.get_student_with_tasks(student2.getStudentId()) == [{'7_2': None}, {'9_1': None}])

def test_get_task_with_students():
    repository = InMemoryCommonRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Adelin Gradinaru', 217)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')
    task3 = Task('7_3', 'Revelion', '12/1/2022')
    task4 = Task('9_1', 'Parlament', '1/5/2024')

    repository.store(student1.getStudentId(), task2.getLaboratory_Task())
    repository.store(student1.getStudentId(), task3.getLaboratory_Task())
    repository.store(student1.getStudentId(), task1.getLaboratory_Task())

    assert(repository.get_task_with_students(task2.getLaboratory_Task()) == [1001])

    repository.store(student2.getStudentId(), task1.getLaboratory_Task())
    repository.store(student2.getStudentId(), task4.getLaboratory_Task())

    assert(repository.get_task_with_students(task1.getLaboratory_Task()) == [1001, 1003])

test_get_student_with_tasks()
test_get_task_with_students()
