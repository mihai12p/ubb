from domain.entities import Student, Task
from utilis.dict_operations import get_key_from_dict

class ValidatorException(Exception):
    pass

class StudentValidator:
    '''
    Valideaza multimea de studenti (Student)
    paramtype:                       class
    '''

    def validate(self, student, all_students = []):
        errors = []

        for stud in all_students:
            if student == stud: # (Student: __eq__(self, other) -> bool)
                errors.append('Nu pot exista 2 studenti cu acelasi ID.')
                break

        if len(student.getStudentName().split()) < 2:
            errors.append('Numele studentului trebuie sa fie format din cel putin 2 cuvinte.')

        if student.getStudentId() < 1:
            errors.append('ID-ul studentului nu poate fi mai mic ca 1.')

        if student.getStudentGroup() < 1:
            errors.append('Grupa studentului nu poate fi mai mica ca 1.')

        if len(errors) > 0:
            error_string = '\n    '.join(errors)
            raise ValueError(error_string)

    def validateExisting(self, studentId, all_students = []):
        errors = []

        for stud in all_students:
            if studentId == stud.getStudentId():
                break
        else:
            errors.append('Studentul cautat nu exista.')

        if len(errors) > 0:
            error_string = '\n    '.join(errors)
            raise ValueError(error_string)

def test_validateStudent():
    validator = StudentValidator()

    student1 = Student(1001, 'Mihai Panduru', 215)
    student2 = Student(1002, 'Andrei Paunescu', 215)

    validator.validate(student1)
    validator.validate(student2)

    try:
        student3 = Student(1003, 'Andrei', 215)
        validator.validate(student3)
        assert False
    except:
        assert True

    try:
        student3 = Student(0, 'Andrei Paunescu', 0)
        validator.validate(student3)
        assert False
    except:
        assert True

test_validateStudent()

class TaskValidator:
    '''
    Valideaza multimea de probleme (Task)
    paramtype:                      class
    '''

    def validate(self, task, all_tasks = []):
        errors = []

        for tsk in all_tasks:
            if task == tsk: # (Task: __eq__(self, other) -> bool)
                errors.append('Exista deja o astfel de problema in lista.')
                break

        if len(task.getLaboratory_Task().split('_')) != 2:
            errors.append('Problema nu este sub forma ceruta: numar laborator_numar problema.')

        if len(task.getDeadline().split('/')) != 3:
            errors.append('Termenul limita nu este sub forma ceruta: dd/mm/YYYY.')

        if len(errors) > 0:
            error_string = '\n    '.join(errors)
            raise ValueError(error_string)

    def validateExisting(self, task, all_tasks = []):
        errors = []

        if len(task.split('_')) != 2:
            errors.append('Problema nu este sub forma ceruta: numar laborator_numar problema.')
        else:
            for tsk in all_tasks:
                if task == tsk.getLaboratory_Task():
                    break
            else:
                errors.append('Problema cautata nu exista.')

        if len(errors) > 0:
            error_string = '\n    '.join(errors)
            raise ValueError(error_string)

def test_validateTask():
    validator = TaskValidator()

    task1 = Task('7_2', 'Gestionare', '8/11/2021')
    task2 = Task('7_3', 'Inchiriere', '8/11/2021')

    validator.validate(task1)
    validator.validate(task2)

    try:
        task3 = Task('7 2', 'Gestionare', '8.11.2021')
        validator.validate(task3)
        assert False
    except:
        assert True

    try:
        task3 = Task('', '', '')
        validator.validate(task3)
        assert False
    except:
        assert True

test_validateTask()

class CommonValidator:
    '''
    Valideaza multimea de probleme problemele ale studentilor (Student & Task)
    paramtype:                                                  class    class
    '''

    def validateAssign(self, task, all_students_tasks = []):
        errors = []

        for tsk in all_students_tasks:
            if task == get_key_from_dict(tsk):
                errors.append('Aceasta problema este deja atribuita acestui student.')
                break

        if len(errors) > 0:
            error_string = '\n    '.join(errors)
            raise ValueError(error_string)

    def validateGrade(self, task, grade, all_students_tasks = []):
        errors = []

        for tsk in all_students_tasks:
            if task == get_key_from_dict(tsk):
                break
        else:
            errors.append('Aceasta problema nu este atribuita acestui student.')

        if grade < 1 or grade > 10:
            errors.append('Nota acordata trebuie sa fie intre 1 si 10 inclusiv.')

        if len(errors) > 0:
            error_string = '\n    '.join(errors)
            raise ValueError(error_string)
