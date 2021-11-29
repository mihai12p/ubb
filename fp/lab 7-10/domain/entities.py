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

class Grade:
    '''
    Creeaza o noua nota (grade) pentru un student (studentId) la o anumita problema (laboratory_task)
    paramtype:           float                         int                                  str
    '''

    def __init__(self, studentId, laboratory_task, grade):
        self.__student = studentId
        self.__task = laboratory_task
        self.__grade = grade

    def getStudentId(self) -> int:
        return self.__student

    def getLaboratory_Task(self) -> str:
        return self.__task

    def getGrade(self) -> float:
        return self.__grade

    def setStudentId(self, student):
        self.__student = student

    def setLaboratory_Task(self, task):
        self.__task = task

    def setGrade(self, grade):
        self.__grade = grade

    def __eq__(self, other) -> bool:
        return self.__student == other.getStudentId() and self.__task == other.getLaboratory_Task()

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
