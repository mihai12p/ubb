from domain.entities import Student, Task, Grade, DTO
from domain.validators import StudentValidator, TaskValidator, GradeValidator
from repository.repo import InMemoryStudentRepository, InMemoryTaskRepository, InMemoryGradeRepository
from utilis.random_helper import randomNumber, randomString

class StudentService:
    '''
    Coordoneaza operatiile legate de studenti primite de la consola astfel incat sa se ajunga la raspunsul dorit
    '''

    def __init__(self, repository, validator):
        '''
        __repository = multimea ce se ocupa de multimea de studenti
        __validator = multimea ce valideaza studentii inainte sa ii adauge in __repository
        '''

        self.__repository = repository
        self.__validator = validator

    def get_all_students(self) -> list[Student]:
        return self.__repository.get_all_students()

    def add_student(self, studentId, studentName, studentGroup) -> Student:
        '''
        Adauga un student in lista oficiala daca acesta este validat si il returneaza in final
        '''

        student = Student(studentId, studentName, studentGroup)
        self.__validator.validate(student, self.get_all_students())
        self.__repository.store(student)

        return student

    def delete_student(self, studentId) -> Student:
        '''
        Sterge un student din lista oficiala daca acesta exista si il returneaza in final
        '''

        self.__validator.validateExisting(studentId, self.get_all_students())

        student = self.__repository.findStudent(studentId)
        self.__repository.remove(student)

        return student

    def get_copy_of_a_student(self, studentId) -> Student:
        '''
        Returneaza o copie fictiva a unui student inainte de modificarea detaliilor acestuia daca acesta exista
        '''

        self.__validator.validateExisting(studentId, self.get_all_students())

        student = self.__repository.findStudent(studentId)

        return Student(student.getStudentId(), student.getStudentName(), student.getStudentGroup())

    def modify_student(self, studentId, newStudentId, newStudentName, newStudentGroup) -> Student:
        '''
        Returneaza studentul cu informatiile modificate
        '''

        modifiedStudent = Student(newStudentId, newStudentName, newStudentGroup)
        self.__validator.validate(modifiedStudent, self.get_all_students())

        self.__validator.validateExisting(studentId, self.get_all_students())
        student = self.__repository.findStudent(studentId)
        student.setStudentId(modifiedStudent.getStudentId())
        student.setStudentName(modifiedStudent.getStudentName())
        student.setStudentGroup(modifiedStudent.getStudentGroup())

        return student

    def findStudent(self, studentId) -> Student:
        '''
        Cauta un student dupa id-ul acestuia si il returneaza
        '''

        self.__validator.validateExisting(studentId, self.get_all_students())
        student = self.__repository.findStudent(studentId)

        return student

    def generate(self):
        '''
        Genereaza o noua entitate Student si o adauga in repository
        '''

        studentId = randomNumber()

        studentFirstName = randomString()
        studentSecondName = randomString()

        studentGroup = randomNumber()

        student = Student(studentId, studentFirstName + ' ' + studentSecondName, studentGroup)
        self.__validator.validate(student, self.get_all_students())
        self.__repository.store(student)

def test_AddStudent():
    validator = StudentValidator()
    repository = InMemoryStudentRepository()
    service = StudentService(repository, validator)

    added_student = service.add_student(1002, 'Alberto Mihai', 215)
    added_student2 = service.add_student(1001, 'Mihai Panduru', 217)

    assert(added_student.getStudentName() == 'Alberto Mihai')
    assert(added_student2.getStudentGroup() == 217)
    assert(len(repository.get_all_students()) == 2)

def test_DeleteStudent():
    validator = StudentValidator()
    repository = InMemoryStudentRepository()
    service = StudentService(repository, validator)

    service.add_student(1002, 'Alberto Mihai', 215)
    service.add_student(1001, 'Mihai Panduru', 217)

    try:
        service.delete_student(1003)
        assert False
    except:
        assert True

def test_VirtualCopyStudent():
    validator = StudentValidator()
    repository = InMemoryStudentRepository()
    service = StudentService(repository, validator)

    added_student = service.add_student(1002, 'Alberto Mihai', 215)

    assert(id(added_student) != id(service.get_copy_of_a_student(1002)))

def test_UpdateStudent():
    validator = StudentValidator()
    repository = InMemoryStudentRepository()
    service = StudentService(repository, validator)

    added_student = service.add_student(1002, 'Alberto Mihai', 215)

    service.modify_student(1002, 77777, 'Adelin Gradinaru', 666)
    assert(added_student.getStudentId() == 77777)
    assert(added_student.getStudentName() == 'Adelin Gradinaru')
    assert(added_student.getStudentGroup() == 666)

test_AddStudent()
test_DeleteStudent()
test_VirtualCopyStudent()
test_UpdateStudent()

class TaskService:
    '''
    Coordoneaza operatiile legate de probleme primite de la consola astfel incat sa se ajunga la raspunsul dorit
    '''

    def __init__(self, repository, validator):
        '''
        __repository = multimea ce se ocupa de multimea de probleme
        __validator = multimea ce valideaza problemele inainte sa le adauge in __repository
        '''

        self.__repository = repository
        self.__validator = validator

    def get_all_tasks(self) -> list[Task]:
        return self.__repository.get_all_tasks()

    def add_task(self, laboratory_task, description, deadline) -> Task:
        '''
        Adauga o problema in lista oficiala daca aceasta este validata si o returneaza in final
        '''

        task = Task(laboratory_task, description, deadline)
        self.__validator.validate(task, self.get_all_tasks())
        self.__repository.store(task)

        return task

    def delete_task(self, laboratory_task) -> Task:
        '''
        Sterge o problema din lista oficiala daca aceasta exista si o returneaza in final
        '''

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())

        task = self.__repository.findTask(laboratory_task)
        self.__repository.remove(task)

        return task

    def get_copy_of_a_task(self, laboratory_task) -> Task:
        '''
        Returneaza o copie fictiva a unei probleme inainte de modificarea detaliilor acesteia daca aceasta exista
        '''

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())

        task = self.__repository.findTask(laboratory_task)

        return Task(task.getLaboratory_Task(), task.getDescription(), task.getDeadline())

    def modify_task(self, laboratory_task, newLaboratory_task, newDescription, newDeadline) -> Task:
        '''
        Returneaza problema cu informatiile modificate
        '''

        modifiedTask = Task(newLaboratory_task, newDescription, newDeadline)
        self.__validator.validate(modifiedTask, self.get_all_tasks())

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())
        task = self.__repository.findTask(laboratory_task)
        task.setLaboratory_Task(modifiedTask.getLaboratory_Task())
        task.setDescription(modifiedTask.getDescription())
        task.setDeadline(modifiedTask.getDeadline())

        return task

    def findTask(self, laboratory_task) -> Task:
        '''
        Cauta o problema dupa id-ul acesteia si o returneaza
        '''

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())
        task = self.__repository.findTask(laboratory_task)

        return task

def test_AddTask():
    validator = TaskValidator()
    repository = InMemoryTaskRepository()
    service = TaskService(repository, validator)

    added_task = service.add_task('7_2', 'Catalog', '8/11/2021')
    added_task2 = service.add_task('8_4', 'Complex', '2/3/2022')

    assert(added_task.getDeadline() == '8/11/2021')
    assert(added_task2.getLaboratory_Task() == '8_4')
    assert(len(repository.get_all_tasks()) == 2)

def test_DeleteTask():
    validator = TaskValidator()
    repository = InMemoryTaskRepository()
    service = TaskService(repository, validator)

    service.add_task('7_2', 'Catalog', '8/11/2021')
    service.add_task('8_4', 'Complex', '2/3/2022')

    try:
        service.delete_task('7_3')
        assert False
    except:
        assert True

def test_VirtualCopyTask():
    validator = TaskValidator()
    repository = InMemoryTaskRepository()
    service = TaskService(repository, validator)

    added_task = service.add_task('7_2', 'Catalog', '8/11/2021')

    assert(id(added_task) != id(service.get_copy_of_a_task('7_2')))

def test_UpdateTask():
    validator = TaskValidator()
    repository = InMemoryTaskRepository()
    service = TaskService(repository, validator)

    added_task = service.add_task('7_2', 'Catalog', '8/11/2021')

    service.modify_task('7_2', '6_2', 'Revelion', '1/1/2022')
    assert(added_task.getLaboratory_Task() == '6_2')
    assert(added_task.getDescription() == 'Revelion')
    assert(added_task.getDeadline() == '1/1/2022')

test_AddTask()
test_DeleteTask()
test_VirtualCopyTask()
test_UpdateTask()

class GradeService:
    '''
    Coordoneaza operatiile legate de notare primite de la consola astfel incat sa se ajunga la raspunsul dorit
    '''

    def __init__(self, g_repository, g_validator, s_repository, t_repository):
        '''
        __g_repository = multimea ce se ocupa de multimea de studenti si problemele lor
        __g_validator = multimea ce valideaza atribuirile de probleme si note
        __s_repository = student repository
        __t_repository = task repository
        '''

        self.__g_repository = g_repository
        self.__g_validator = g_validator
        self.__s_repository = s_repository
        self.__t_repository = t_repository

    def assign_task(self, student, task) -> Grade:
        '''
        Atribuie o problema unui student

        paramtype: Student, Task
        rtype: Grade
        '''

        self.__s_repository.findStudent(student.getStudentId())
        self.__t_repository.findTask(task.getLaboratory_Task())

        grade = Grade(student, task, None)
        self.__g_validator.validate(grade, self.__g_repository.get_all_grades())
        self.__g_repository.store(grade)

        return grade

    def findTasks(self, student) -> list[Task]:
        '''
        Cauta problemele unui student
        '''

        return self.__g_repository.findTasks(student)


    def findStudents(self, task) -> list[Student]:
        '''
        Cauta studentii atribuiti unei probleme
        '''

        return self.__g_repository.findStudents(task)

    def delete_tasks_for_student(self, student) -> Student:
        '''
        Sterge problemele unui student
        '''

        search_tasks_for_student = self.findTasks(student)
        if len(search_tasks_for_student):
            for taskGrade in search_tasks_for_student:
                grade = self.__g_repository.findGrade(student, taskGrade[0])
                self.__g_repository.remove(grade)

        return student

    def delete_student_for_tasks(self, task) -> Task:
        '''
        Sterge studentii atribuiti unei probleme
        '''

        search_students_for_task = self.findStudents(task)
        if len(search_students_for_task):
            for studentGrade in search_students_for_task:
                grade = self.__g_repository.findGrade(studentGrade[0], task)
                self.__g_repository.remove(grade)

        return task

    def evaluate_task(self, student, task, gradeNumber) -> Grade:
        '''
        Evalueaza problema unui student

        paramtype: Student, Task, int
        rtype: Grade
        '''

        self.__s_repository.findStudent(student.getStudentId())
        self.__t_repository.findTask(task.getLaboratory_Task())

        grade = self.__g_repository.findGrade(student, task)

        self.__g_validator.validateGrade(gradeNumber)
        grade.setGrade(gradeNumber)

        return grade

    def statistics_students_for_task(self, task):
        '''
        Creeaza statistica studentilor pentru o problema data

        paramtype: Task
        rtype: list
        '''

        self.__t_repository.findTask(task.getLaboratory_Task())

        search_students_for_task = self.findStudents(task)
        statistics = []
        if len(search_students_for_task):
            for studentGrade in search_students_for_task:
                self.__g_repository.findGrade(studentGrade[0], task)
                if studentGrade[1]:
                    individual = DTO(studentGrade[0], studentGrade[1])
                    statistics.append(individual)

        statistics = sorted(statistics, key=lambda grade: grade.getGrade())
        return sorted(statistics, key=lambda name: name.getStudent().getStudentName())

    def statistics_students(self):
        '''
        Creeaza statistica studentilor cu media notelor de laborator mai mica ca 5

        rtype: list
        '''

        grades = self.__g_repository.get_all_grades()
        statistics = []
        if len(grades):
            for x in grades:
                counter = 0
                sum = 0
                tasks = self.findTasks(x.getStudent())
                for y in tasks:
                    if y[1]:
                        counter += 1
                        sum += y[1]

                if counter:
                    average = sum / counter
                    if average < 5.0:
                        individual = DTO(x.getStudent().getStudentName(), average)
                        for already in statistics:
                            if already == individual: # (DTO: __eq__(self, other) -> bool)
                                break
                        else:
                            statistics.append(individual)

        return statistics

    def statistics_top3(self):
        '''
        Creeaza statistica laboratoarelor top3

        rtype: list
        '''

        grades = self.__g_repository.get_all_grades()
        statistics = []
        if len(grades):
            for x in grades:
                counter = 0
                tasks = self.findStudents(x.getTask())
                for y in tasks:
                    if y[1]:
                        counter += 1

                if counter:
                    individual = DTO(x.getTask(), counter)
                    for already in statistics:
                        if already == individual: # (DTO: __eq__(self, other) -> bool)
                            break
                    else:
                        statistics.append(individual)

        statistics = sorted(statistics, key=lambda average : average.getGrade(), reverse=True)
        return statistics[:3]

def test_AssignTask():
    validator = GradeValidator()
    repository = InMemoryGradeRepository()
    s_repository = InMemoryStudentRepository()
    t_repository = InMemoryTaskRepository()
    service = GradeService(repository, validator, s_repository, t_repository)

    student1 = Student(12, 'Mihai Panduru', 215)

    task1 = Task('7_2', 'Catalog', '8/11/2021')
    task2 = Task('8_4', 'Complex', '2/3/2022')

    s_repository.store(student1)

    t_repository.store(task1)
    t_repository.store(task2)

    assigned_task1 = service.assign_task(student1, task1)
    assigned_task2 = service.assign_task(student1, task2)

    assert(assigned_task1.getStudent() == student1)
    assert(assigned_task2.getTask() == task2)
    assert(len(repository.get_all_grades()) == 2)

def test_EvaluateTask():
    validator = GradeValidator()
    repository = InMemoryGradeRepository()
    s_repository = InMemoryStudentRepository()
    t_repository = InMemoryTaskRepository()
    service = GradeService(repository, validator, s_repository, t_repository)

    student1 = Student(12, 'Mihai Panduru', 215)

    task1 = Task('7_2', 'Catalog', '8/11/2021')

    s_repository.store(student1)

    t_repository.store(task1)

    service.assign_task(student1, task1)
    evaluated_task1 = service.evaluate_task(student1, task1, 5)

    assert(evaluated_task1.getGrade() == 5)

def test_statistics_students_for_task():
    validator = GradeValidator()
    repository = InMemoryGradeRepository()
    s_repository = InMemoryStudentRepository()
    t_repository = InMemoryTaskRepository()
    service = GradeService(repository, validator, s_repository, t_repository)

    student1 = Student(12, 'Mihai Panduru', 215)
    student2 = Student(22, 'Adelin Gradinaru', 217)
    student3 = Student(23, 'Alberto Mihai', 213)
    student4 = Student(25, 'Kevin Axmann', 219)

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

    grade1 = Grade(student2, task1, 6)
    grade2 = Grade(student1, task1, 4)
    grade3 = Grade(student3, task1, 3)
    grade4 = Grade(student3, task2, 6.9)
    grade5 = Grade(student2, task3, 9)
    grade6 = Grade(student2, task2, 3)
    grade7 = Grade(student4, task2, 9)
    grade8 = Grade(student4, task4, 10)
    grade9 = Grade(student2, task4, 10)

    repository.store(grade1)
    repository.store(grade2)
    repository.store(grade3)
    repository.store(grade4)
    repository.store(grade5)
    repository.store(grade6)
    repository.store(grade7)
    repository.store(grade8)
    repository.store(grade9)

    statistics = service.statistics_students_for_task(task1)

    assert(len(statistics) == 3)
    assert(statistics[0].getStudent() == student2)
    assert(statistics[0].getGrade() == 6)
    assert(statistics[1].getStudent() == student3)
    assert(statistics[1].getGrade() == 3)
    assert(statistics[2].getStudent() == student1)
    assert(statistics[2].getGrade() == 4)

def test_statistics_students():
    validator = GradeValidator()
    repository = InMemoryGradeRepository()
    s_repository = InMemoryStudentRepository()
    t_repository = InMemoryTaskRepository()
    service = GradeService(repository, validator, s_repository, t_repository)

    student1 = Student(12, 'Mihai Panduru', 215)
    student2 = Student(22, 'Adelin Gradinaru', 217)
    student3 = Student(23, 'Alberto Mihai', 213)
    student4 = Student(25, 'Kevin Axmann', 219)

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

    grade1 = Grade(student2, task1, 6)
    grade2 = Grade(student1, task1, 4)
    grade3 = Grade(student3, task1, 3)
    grade4 = Grade(student3, task2, 6.9)
    grade5 = Grade(student2, task3, 9)
    grade6 = Grade(student2, task2, 3)
    grade7 = Grade(student4, task2, 9)
    grade8 = Grade(student4, task4, 10)
    grade9 = Grade(student2, task4, 10)

    repository.store(grade1)
    repository.store(grade2)
    repository.store(grade3)
    repository.store(grade4)
    repository.store(grade5)
    repository.store(grade6)
    repository.store(grade7)
    repository.store(grade8)
    repository.store(grade9)

    statistics = service.statistics_students()

    assert(len(statistics) == 2)
    assert(statistics[0].getStudent() == student1.getStudentName())
    assert(statistics[0].getGrade() == 4.0)
    assert(statistics[1].getStudent() == student3.getStudentName())
    assert(statistics[1].getGrade() == 4.95)

test_AssignTask()
test_EvaluateTask()
test_statistics_students_for_task()
test_statistics_students()
