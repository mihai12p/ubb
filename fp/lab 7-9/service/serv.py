from domain.entities import Student, Task
from domain.validators import StudentValidator, TaskValidator
from repository.repo import InMemoryStudentRepository, InMemoryTaskRepository
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

    def get_repository(self):
        return self.__repository

    def get_validator(self):
        return self.__validator

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

        student = self.__repository.get_student_by_ID(studentId)
        self.__repository.remove(student)

        return student

    def get_copy_of_a_student(self, studentId) -> Student:
        '''
        Returneaza o copie fictiva a unui student inainte de modificarea detaliilor acestuia daca acesta exista
        '''

        self.__validator.validateExisting(studentId, self.get_all_students())

        student = self.__repository.get_student_by_ID(studentId)

        return Student(student.getStudentId(), student.getStudentName(), student.getStudentGroup())

    def modify_student(self, studentId, newStudentId, newStudentName, newStudentGroup) -> Student:
        '''
        Returneaza studentul cu informatiile modificate
        '''

        modifiedStudent = Student(newStudentId, newStudentName, newStudentGroup)
        self.__validator.validate(modifiedStudent, self.get_all_students())

        self.__validator.validateExisting(studentId, self.get_all_students())
        student = self.__repository.get_student_by_ID(studentId)
        student.setStudentId(modifiedStudent.getStudentId())
        student.setStudentName(modifiedStudent.getStudentName())
        student.setStudentGroup(modifiedStudent.getStudentGroup())

        return student

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

    def get_repository(self):
        return self.__repository

    def get_validator(self):
        return self.__validator

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

        task = self.__repository.get_task_by_arg(laboratory_task)
        self.__repository.remove(task)

        return task

    def get_copy_of_a_task(self, laboratory_task) -> Task:
        '''
        Returneaza o copie fictiva a unei probleme inainte de modificarea detaliilor acesteia daca aceasta exista
        '''

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())

        task = self.__repository.get_task_by_arg(laboratory_task)

        return Task(task.getLaboratory_Task(), task.getDescription(), task.getDeadline())

    def modify_task(self, laboratory_task, newLaboratory_task, newDescription, newDeadline) -> Task:
        '''
        Returneaza problema cu informatiile modificate
        '''

        modifiedTask = Task(newLaboratory_task, newDescription, newDeadline)
        self.__validator.validate(modifiedTask, self.get_all_tasks())

        self.__validator.validateExisting(laboratory_task, self.get_all_tasks())
        task = self.__repository.get_task_by_arg(laboratory_task)
        task.setLaboratory_Task(modifiedTask.getLaboratory_Task())
        task.setDescription(modifiedTask.getDescription())
        task.setDeadline(modifiedTask.getDeadline())

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

class CommonService:
    '''
    Coordoneaza operatiile legate de studenti si probleme primite de la consola astfel incat sa se ajunga la raspunsul dorit
    '''

    def __init__(self, c_repository, c_validator, s_service, t_service):
        '''
        __c_repository = multimea ce se ocupa de multimea de studenti si problemele lor
        __c_validator = multimea ce valideaza atribuirile de probleme si note
        __s_repository = student repository
        __s_validator = student validator
        __t_repository = task repository
        __t_validator = task validator
        '''

        self.__c_repository = c_repository
        self.__c_validator = c_validator
        self.__s_repository = s_service.get_repository()
        self.__s_validator = s_service.get_validator()
        self.__t_repository = t_service.get_repository()
        self.__t_validator = t_service.get_validator()

    def assign_task(self, studentId, laboratory_task) -> list[Student, Task]:
        '''
        Atribuie o problema unui student si returneaza o lista formata din studentul si problema atribuita
        '''

        self.__s_validator.validateExisting(studentId, self.__s_repository.get_all_students())
        self.__t_validator.validateExisting(laboratory_task, self.__t_repository.get_all_tasks())
        self.__c_validator.validateAssign(laboratory_task, self.__c_repository.get_student_with_tasks(studentId))

        self.__c_repository.store(studentId, laboratory_task)
        student = self.__s_repository.get_student_by_ID(studentId)
        task = self.__t_repository.get_task_by_arg(laboratory_task)

        return [student, task]

    def evaluate_task(self, studentId, laboratory_task, grade) -> list[Student, Task]:
        '''
        Evalueaza o problema a unui student si returneaza o lista formata din studentul si problema evaluata
        '''

        self.__s_validator.validateExisting(studentId, self.__s_repository.get_all_students())
        self.__t_validator.validateExisting(laboratory_task, self.__t_repository.get_all_tasks())
        self.__c_validator.validateGrade(laboratory_task, grade, self.__c_repository.get_student_with_tasks(studentId))

        self.__c_repository.evaluate(studentId, laboratory_task, grade)
        student = self.__s_repository.get_student_by_ID(studentId)
        task = self.__t_repository.get_task_by_arg(laboratory_task)

        return [student, task]

    def delete_student(self, studentId):
        self.__c_repository.removeStudent(studentId)

    def delete_task(self, laboratory_task):
        self.__c_repository.removeTask(laboratory_task)

    def update_student(self, studentId, newStudentId):
        self.__c_repository.update_student(studentId, newStudentId)

    def update_task(self, laboratory_task, newLaboratory_task):
        self.__c_repository.update_task(laboratory_task, newLaboratory_task)

    def search_student(self, studentId) -> list[Student, list]:
        '''
        Cauta un student si daca acesta exista, il returneaza impreuna cu problemele atribuite
        '''

        self.__s_validator.validateExisting(studentId, self.__s_repository.get_all_students())

        student = self.__s_repository.get_student_by_ID(studentId)
        studentTasks = self.__c_repository.get_student_with_tasks(studentId)

        return [student, studentTasks]

    def search_task(self, laboratory_task) -> list[Task, list]:
        '''
        Cauta o problema si daca aceasta exista, ii returneaza studentii atribuiti
        '''

        self.__t_validator.validateExisting(laboratory_task, self.__t_repository.get_all_tasks())

        task = self.__t_repository.get_task_by_arg(laboratory_task)
        taskStudents = self.__c_repository.get_task_with_students(laboratory_task)

        return [task, taskStudents]

    def generate(self):
        '''
        Genereaza o noua entitate Student si o adauga in repository
        '''

        studentId = randomNumber()

        studentFirstName = randomString()
        studentSecondName = randomString()

        studentGroup = randomNumber()

        student = Student(studentId, studentFirstName + ' ' + studentSecondName, studentGroup)
        self.__s_validator.validate(student, self.__s_repository.get_all_students())
        self.__s_repository.store(student)
