from domain.entities import Student, Task, Grade, DTO
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

    def delete_all_students(self):
        '''
        Sterge toti studentii
        '''

        self.__repository.remove_all()

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
        self.__repository.update(student, modifiedStudent)

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

    def delete_all_tasks(self):
        '''
        Sterge toate problemele
        '''

        self.__repository.remove_all()

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
        self.__repository.update(task, modifiedTask)

        return task

    def findTask(self, laboratory_task) -> Task:
        '''
        Cauta o problema dupa id-ul acesteia si o returneaza
        '''

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())
        task = self.__repository.findTask(laboratory_task)

        return task

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

        grade = Grade(student.getStudentId(), task.getLaboratory_Task(), 0.0)
        self.__g_validator.validate(grade, self.__g_repository.get_all_grades())
        self.__g_repository.store(grade)

        return grade

    def delete_all_grades(self):
        '''
        Sterge toate notele
        '''

        self.__g_repository.remove_all()

    def update_student(self, student, modifiedStudent):
        '''
        Actualizeaza in fisier modificarile aduse studentului

        paramtype: Student, Student
        '''

        self.__g_repository.update_student(student, modifiedStudent)

    def update_task(self, task, modifiedTask):
        '''
        Actualizeaza in fisier modificarile aduse problemei

        paramtype: Task, Task
        '''

        self.__g_repository.update_task(task, modifiedTask)

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
                grade = self.__g_repository.findGrade(student.getStudentId(), taskGrade[0])
                self.__g_repository.remove(grade)

        return student

    def delete_student_for_tasks(self, task) -> Task:
        '''
        Sterge studentii atribuiti unei probleme
        '''

        search_students_for_task = self.findStudents(task)
        if len(search_students_for_task):
            for studentGrade in search_students_for_task:
                grade = self.__g_repository.findGrade(studentGrade[0], task.getLaboratory_Task())
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

        grade = self.__g_repository.findGrade(student.getStudentId(), task.getLaboratory_Task())

        self.__g_validator.validateGrade(gradeNumber)
        self.__g_repository.evaluate(grade, gradeNumber)

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
                self.__g_repository.findGrade(studentGrade[0], task.getLaboratory_Task())
                if studentGrade[1]:
                    individual = DTO(self.__s_repository.findStudent(studentGrade[0]), studentGrade[1])
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
                tasks = self.findTasks(x)
                for y in tasks:
                    if y[1]:
                        counter += 1
                        sum += y[1]

                if counter:
                    average = sum / counter
                    if average < 5.0:
                        individual = DTO(self.__s_repository.findStudent(x.getStudentId()), average)
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
                tasks = self.findStudents(self.__t_repository.findTask(x.getLaboratory_Task()))
                for y in tasks:
                    if y[1]:
                        counter += 1

                if counter:
                    individual = DTO(self.__t_repository.findTask(x.getLaboratory_Task()), counter)
                    for already in statistics:
                        if already == individual: # (DTO: __eq__(self, other) -> bool)
                            break
                    else:
                        statistics.append(individual)

        statistics = sorted(statistics, key=lambda average : average.getGrade(), reverse=True)
        return statistics[:3]
