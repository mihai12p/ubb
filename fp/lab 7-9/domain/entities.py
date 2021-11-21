class Student:
    '''
    Creeaza un nou student cu un ID (studentId), un nume (studentName) si o grupa (studentGroup)
    paramtype:                          int                  string                    int
    '''

    def __init__(self, studentId, studentName, studentGroup):
        self.__studentId = studentId
        self.__studentName = studentName
        self.__studentGroup = studentGroup

    def getStudentId(self) -> int:
        return self.__studentId

    def getStudentName(self) -> str:
        return self.__studentName

    def getStudentGroup(self) -> int:
        return self.__studentGroup

    def setStudentId(self, id):
        self.__studentId = id

    def setStudentName(self, name):
        self.__studentName = name

    def setStudentGroup(self, group):
        self.__studentGroup = group

    def __eq__(self, other) -> bool:
        return self.__studentId == other.getStudentId()

    def __str__(self) -> str:
        return 'ID: ' + str(self.__studentId) + ' | Nume: ' + self.__studentName + ' | Grupa: ' + str(self.__studentGroup)

def test_Student():
    student1 = Student(1001, 'Mihai Panduru', 215)
    assert(student1.getStudentId() == 1001)
    assert(student1.getStudentName() == 'Mihai Panduru')
    assert(student1.getStudentGroup() == 215)

    student1.setStudentId(1002)
    student1.setStudentName('Andrei Paunescu')
    student1.setStudentGroup(212)

    assert(student1.getStudentId() == 1002)
    assert(student1.getStudentName() == 'Andrei Paunescu')
    assert(student1.getStudentGroup() == 212)

    student2 = Student(1002, 'Alberto Mihai', 215)
    assert(student1 == student2)

    student3 = Student(1001, 'Alberto Mihai', 215)
    assert(student2 != student3)

test_Student()

class Task:
    '''
    Creeaza o noua problema cu un ID (laboratory_task), o descriere (description) si un termen limita (deadline)
    paramtype:                            string                       string                           string
    '''

    def __init__(self, laboratory_task, description, deadline):
        self.__laboratory_task = laboratory_task
        self.__description = description
        self.__deadline = deadline

    def getLaboratory_Task(self) -> str:
        return self.__laboratory_task

    def getDescription(self) -> str:
        return self.__description

    def getDeadline(self) -> str:
        return self.__deadline

    def setLaboratory_Task(self, laboratory_task):
        self.__laboratory_task = laboratory_task

    def setDescription(self, description):
        self.__description = description

    def setDeadline(self, deadline):
        self.__deadline = deadline

    def __eq__(self, other) -> bool:
        return self.__laboratory_task == other.getLaboratory_Task()

    def __str__(self) -> str:
        self.__laboratoryNumber, self.__taskNumber = self.__laboratory_task.split('_')
        return 'Laborator: ' + self.__laboratoryNumber + ' | Problema: ' + self.__taskNumber + ' | Descriere: ' + self.__description + ' | Termen limita: ' + self.__deadline

def test_Task():
    task1 = Task('7_2', 'Catalog', '8/11/2021')
    assert(task1.getLaboratory_Task() == '7_2')
    assert(task1.getDescription() == 'Catalog')
    assert(task1.getDeadline() == '8/11/2021')

    task1.setLaboratory_Task('8_4')
    task1.setDescription('Gestionare')
    task1.setDeadline('3/12/2021')

    assert(task1.getLaboratory_Task() == '8_4')
    assert(task1.getDescription() == 'Gestionare')
    assert(task1.getDeadline() == '3/12/2021')

    task2 = Task('8_4', 'Complex', '2/3/2022')
    assert(task1 == task2)

    task3 = Task('7_2', 'Complex', '2/3/2022')
    assert(task2 != task3)

test_Task()

class Grade:
    '''
    Creeaza o noua nota (grade) pentru un student (student) la o anumita problema (task)
    paramtype:            int                      Student                         Task
    '''

    def __init__(self, student, task, grade):
        self.__student = student
        self.__task = task
        self.__grade = grade

    def getStudent(self) -> Student:
        return self.__student

    def getTask(self) -> Task:
        return self.__task

    def getGrade(self) -> int:
        return self.__grade

    def setStudent(self, student):
        self.__student = student

    def setTask(self, task):
        self.__task = task

    def setGrade(self, grade):
        self.__grade = grade

    def __eq__(self, other) -> bool:
        return self.__student == other.getStudent() and self.__task == other.getTask()

def test_Grade():
    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1002, 'Alberto Mihai', 215)
    student3 = Student(1001, 'Alberto Mihai', 215)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('7_2', 'Complex', '2/3/2022')

    grade1 = Grade(student1, task1, 9)
    assert(grade1.getStudent() == student1)
    assert(grade1.getTask() == task1)
    assert(grade1.getGrade() == 9)

    grade1.setStudent(student3)
    grade1.setTask(task2)
    grade1.setGrade(10)

    assert(grade1.getStudent() == student3)
    assert(grade1.getTask() == task2)
    assert(grade1.getGrade() == 10)

    grade2 = Grade(student2, task2, 9)
    assert(grade1 != grade2)

    grade2.setStudent(student3)
    assert(grade1 == grade2)

test_Grade()

class DTO:
    '''
    Data Transfer Object
    '''

    def __init__(self, student, grade):
        self.__student = student
        self.__grade = grade

    def getStudent(self):
        return self.__student

    def getGrade(self):
        return self.__grade

    def setStudent(self, student):
        self.__student = student

    def setGrade(self, grade):
        self.__grade = grade

    def __eq__(self, other) -> bool:
        return self.__student == other.getStudent() and self.__grade == other.getGrade()
