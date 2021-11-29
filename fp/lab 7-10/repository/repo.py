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

    def remove_all(self):
        self.__students = []

    def update(self, student, modifiedStudent):
        for relation in self.__students:
            if relation.getStudentId() == student.getStudentId():
                relation.setStudentId(modifiedStudent.getStudentId())
                relation.setStudentName(modifiedStudent.getStudentName())
                relation.setStudentGroup(modifiedStudent.getStudentGroup())
                break

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

    def remove_all(self):
        self.__tasks = []

    def update(self, task, modifiedTask):
        for relation in self.__tasks:
            if relation.getLaboratory_Task() == task.getLaboratory_Task():
                relation.setLaboratory_Task(modifiedTask.getLaboratory_Task())
                relation.setDescription(modifiedTask.getDescription())
                relation.setDeadline(modifiedTask.getDeadline())
                break

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

    def remove_all(self):
        self.__grades = []

    def get_all_grades(self) -> list[Grade]:
        return self.__grades

    def update_student(self, student, modifiedStudent):
        for relation in self.__grades:
            if relation.getStudentId() == student.getStudentId():
                relation.setStudentId(modifiedStudent.getStudentId())

    def update_task(self, task, modifiedTask):
        for relation in self.__grades:
            if relation.getLaboratory_Task() == task.getLaboratory_Task():
                relation.setLaboratory_Task(modifiedTask.getLaboratory_Task())

    def evaluate(self, grade, gradeNumber):
        grade.setGrade(gradeNumber)

    def findStudents(self, task) -> list[Student]:
        students = []

        for relation in self.__grades:
            if relation.getLaboratory_Task() == task.getLaboratory_Task():
                students.append([relation.getStudentId(), relation.getGrade()])

        return students

    def findTasks(self, student) -> list[Task]:
        tasks = []

        for relation in self.__grades:
            if relation.getStudentId() == student.getStudentId():
                tasks.append([relation.getLaboratory_Task(), relation.getGrade()])

        return tasks

    def findGrade(self, studentId, laboratory_task) -> Grade:
        for grade in self.__grades:
            if grade.getStudentId() == studentId and grade.getLaboratory_Task() == laboratory_task:
                return grade

        raise TaskNotAssignedException()

class InFileStudentRepository(InMemoryStudentRepository):
    def __init__(self, filename):
        '''
        __filename = numele fisierului de deschis
        '''

        InMemoryStudentRepository.__init__(self)
        self.__filename = filename

        self.__load_from_file()

    def __load_from_file(self):
        '''
        Incarca datele din fisier
        '''

        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                studentId, studentName, studentGroup = [token.strip() for token in line.split('; ')]
                student = Student(int(studentId), studentName, int(studentGroup))
                InMemoryStudentRepository.store(self, student)

    def __save_to_file(self):
        '''
        Salveaza in fisier studentii dati
        '''

        students_list = self.get_all_students()
        with open(self.__filename, 'w') as f:
            for student in students_list:
                student_string = str(student.getStudentId()) + '; ' + student.getStudentName() + '; ' + str(student.getStudentGroup()) + '\n'
                f.write(student_string)

    def store(self, student):
        '''
        Adauga un student in lista si il salveaza in fisier
        paramtype: Student
        '''

        InMemoryStudentRepository.store(self, student)
        self.__save_to_file()

    def remove(self, student):
        '''
        Sterge un student din lista si il sterge si din fisier
        paramtype: Student
        '''

        InMemoryStudentRepository.remove(self, student)
        self.__save_to_file()

    def remove_all(self):
        '''
        Sterge toti studentii din fisier
        '''

        InMemoryStudentRepository.remove_all(self)
        self.__save_to_file()

    def update(self, student, modifiedStudent):
        '''
        Actualizeaza in fisier modificarile aduse studentului

        paramtype: Student, Student
        '''

        InMemoryStudentRepository.update(self, student, modifiedStudent)
        self.__save_to_file()

    def get_all_students(self) -> list[Student]:
        '''
        Returneaza o lista cu toti studentii
        '''

        return InMemoryStudentRepository.get_all_students(self)

    def findStudent(self, studentId) -> Student:
        '''
        Returneaza studentul identificat dupa ID-ul acestuia
        paramtype: int
        '''

        return InMemoryStudentRepository.findStudent(self, studentId)

class InFileTaskRepository(InMemoryTaskRepository):
    def __init__(self, filename):
        '''
        __filename = numele fisierului de deschis
        '''

        InMemoryTaskRepository.__init__(self)
        self.__filename = filename

        self.__load_from_file()

    def __load_from_file(self):
        '''
        Incarca datele din fisier
        '''

        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                laboratory_task, description, deadline = [token.strip() for token in line.split('; ')]
                task = Task(laboratory_task, description, deadline)
                InMemoryTaskRepository.store(self, task)

    def __save_to_file(self):
        '''
        Salveaza in fisier problemele date
        '''

        tasks_list = self.get_all_tasks()
        with open(self.__filename, 'w') as f:
            for task in tasks_list:
                task_string = task.getLaboratory_Task() + '; ' + task.getDescription() + '; ' + task.getDeadline() + '\n'
                f.write(task_string)

    def store(self, task):
        '''
        Adauga o problema in lista si o salveaza in fisier
        paramtype: Task
        '''

        InMemoryTaskRepository.store(self, task)
        self.__save_to_file()

    def remove(self, task):
        '''
        Sterge o problema din lista si o sterge si din fisier
        paramtype: Task
        '''

        InMemoryTaskRepository.remove(self, task)
        self.__save_to_file()

    def remove_all(self):
        '''
        Sterge toate problemele din fisier
        '''

        InMemoryTaskRepository.remove_all(self)
        self.__save_to_file()

    def update(self, task, modifiedTask):
        '''
        Actualizeaza in fisier modificarile aduse problemei

        paramtype: Task, Task
        '''

        InMemoryTaskRepository.update(self, task, modifiedTask)
        self.__save_to_file()

    def get_all_tasks(self) -> list[Task]:
        '''
        Returneaza o lista cu toate problemele
        '''

        return InMemoryTaskRepository.get_all_tasks(self)

    def findTask(self, laboratory_task) -> Task:
        '''
        Returneaza problema identificata dupa ID-ul acesteia
        paramtype: str
        '''

        return InMemoryTaskRepository.findTask(self, laboratory_task)

class InFileGradeRepository(InMemoryGradeRepository):
    def __init__(self, filename):
        '''
        __filename = numele fisierului de deschis
        '''

        InMemoryGradeRepository.__init__(self)
        self.__filename = filename

        self.__load_from_file()

    def __load_from_file(self):
        '''
        Incarca datele din fisier
        '''

        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                studentId, laboratory_task, grade = [token.strip() for token in line.split('; ')]
                grade = Grade(int(studentId), laboratory_task, float(grade))
                InMemoryGradeRepository.store(self, grade)

    def __save_to_file(self):
        '''
        Salveaza in fisier problemele date
        '''

        grades_list = self.get_all_grades()
        with open(self.__filename, 'w') as f:
            for grade in grades_list:
                grade_string = str(grade.getStudentId()) + '; ' + grade.getLaboratory_Task() + '; ' + str(grade.getGrade()) + '\n'
                f.write(grade_string)

    def store(self, grade):
        '''
        Adauga o nota unui student la o problema si o salveaza in fisier
        paramtype: Grade
        '''

        InMemoryGradeRepository.store(self, grade)
        self.__save_to_file()

    def remove(self, grade):
        '''
        Sterge o nota a unui student la o problema si o sterge si din fisier
        paramtype: Grade
        '''

        InMemoryGradeRepository.remove(self, grade)
        self.__save_to_file()

    def remove_all(self):
        '''
        Sterge toate notele din fisier
        '''

        InMemoryGradeRepository.remove_all(self)
        self.__save_to_file()

    def update_student(self, student, modifiedStudent):
        '''
        Actualizeaza in fisier modificarile aduse studentului

        paramtype: Student, Student
        '''

        InMemoryGradeRepository.update_student(self, student, modifiedStudent)
        self.__save_to_file()

    def update_task(self, task, modifiedTask):
        '''
        Actualizeaza in fisier modificarile aduse problemeii

        paramtype: Task, Task
        '''

        InMemoryGradeRepository.update_task(self, task, modifiedTask)
        self.__save_to_file()

    def evaluate(self, grade, gradeNumber):
        '''
        Actualizeaza in fisier nota studentului

        paramtype: Grade, float
        '''

        InMemoryGradeRepository.evaluate(self, grade, gradeNumber)
        self.__save_to_file()

    def get_all_grades(self) -> list[Grade]:
        '''
        Returneaza o lista cu toate notarile studentilor
        '''

        return InMemoryGradeRepository.get_all_grades(self)

    def findStudents(self, task) -> list[Student]:
        '''
        Returneaza studentii atribuiti la o problema
        paramtype: Task
        '''

        return InMemoryGradeRepository.findStudents(self, task)

    def findTasks(self, student) -> list[Task]:
        '''
        Returneaza problemele atribuite unui student
        paramtype: Student
        '''

        return InMemoryGradeRepository.findTasks(self, student)

    def findGrade(self, studentId, laboratory_task) -> Grade:
        '''
        Returneaza nota unui student la o problema
        paramtype: int, str
        '''

        return InMemoryGradeRepository.findGrade(self, studentId, laboratory_task)
