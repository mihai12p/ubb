from domain.entities import Student, Task, Grade
from exceptions.exceptions import StudentNotFoundException, TaskNotFoundException, TaskNotAssignedException

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

    def findStudent(self, studentId) -> Student:
        '''
        Returneaza studentul identificat dupa ID-ul acestuia
        '''

        for student in self.__students:
            if student.getStudentId() == studentId:
                return student

        raise StudentNotFoundException()

def test_findStudent():
    repository = InMemoryStudentRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Alberto Mihai', 215)

    repository.store(student1)
    repository.store(student2)

    assert(repository.findStudent(1001) == student1)
    assert(repository.findStudent(1003) == student2)

    try:
        repository.findStudent(1002)
        assert False
    except StudentNotFoundException:
        assert True

test_findStudent()

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

    def findTask(self, laboratory_task) -> Task:
        '''
        Returneaza problema identificata dupa ID-ul acesteia
        '''

        for tsk in self.__tasks:
            if tsk.getLaboratory_Task() == laboratory_task:
                return tsk

        raise TaskNotFoundException()

def test_findTask():
    repository = InMemoryTaskRepository()

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')

    repository.store(task1)
    repository.store(task2)

    assert(repository.findTask('7_2') == task1)
    assert(repository.findTask('8_4') == task2)

    try:
        repository.findTask('8_5')
        assert False
    except TaskNotFoundException:
        assert True

test_findTask()

class InMemoryGradeRepository:
    '''
    Stocheaza catalogul studentilor
    '''

    def __init__(self):
        '''
        __grades = multimea de studenti, fiecare cu problemele si notele atribuite
        '''

        self.__grades = []

    def store(self, grade):
        self.__grades.append(grade)

    def remove(self, grade):
        self.__grades.remove(grade)

    def get_all_grades(self) -> list[Grade]:
        return self.__grades

    def findStudents(self, task) -> list[Student]:
        students = []

        for relation in self.__grades:
            if relation.getTask() == task:
                students.append([relation.getStudent(), relation.getGrade()])

        return students

    def findTasks(self, student) -> list[Task]:
        tasks = []

        for relation in self.__grades:
            if relation.getStudent() == student:
                tasks.append([relation.getTask(), relation.getGrade()])

        return tasks

    def findGrade(self, student, task) -> Grade:
        for grade in self.__grades:
            if grade.getStudent() == student and grade.getTask() == task:
                return grade

        raise TaskNotAssignedException()

def test_findStudents():
    repository = InMemoryGradeRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Adelin Gradinaru', 217)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')
    task3 = Task('7_3', 'Revelion', '12/1/2022')

    grade1 = Grade(student1, task1, 1)
    grade2 = Grade(student2, task2, 2)
    grade3 = Grade(student1, task3, 3)

    repository.store(grade1)
    repository.store(grade2)
    repository.store(grade3)

    assert(repository.findStudents(task2) == [[student2, 2]])

def test_findTasks():
    repository = InMemoryGradeRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Adelin Gradinaru', 217)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')
    task3 = Task('7_3', 'Revelion', '12/1/2022')

    grade1 = Grade(student1, task1, 1)
    grade2 = Grade(student2, task2, 2)
    grade3 = Grade(student1, task3, 3)

    repository.store(grade1)
    repository.store(grade2)
    repository.store(grade3)

    assert(repository.findTasks(student2) == [[task2, 2]])

def test_findGrades():
    repository = InMemoryGradeRepository()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1003, 'Adelin Gradinaru', 217)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')
    task3 = Task('7_3', 'Revelion', '12/1/2022')

    grade1 = Grade(student1, task1, 1)
    grade2 = Grade(student2, task2, 2)
    grade3 = Grade(student1, task3, 3)

    repository.store(grade1)
    repository.store(grade2)
    repository.store(grade3)

    assert(repository.findGrade(student1, task3) == grade3)

    try:
        repository.findGrade(student1, task2)
        assert False
    except TaskNotAssignedException:
        assert True

test_findStudents()
test_findTasks()
test_findGrades()
