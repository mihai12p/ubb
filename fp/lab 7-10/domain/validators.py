from domain.entities import Student, Task, Grade
from exceptions.exceptions import ValidationException

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
            raise ValidationException(errors)

    def validateExisting(self, studentId, all_students = []):
        errors = []

        for stud in all_students:
            if studentId == stud.getStudentId():
                break
        else:
            errors.append('Studentul cautat nu exista.')

        if len(errors) > 0:
            raise ValidationException(errors)

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
            raise ValidationException(errors)

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
            raise ValidationException(errors)

class GradeValidator:
    '''
    Valideaza multimea de probleme ale studentilor (Student & Task)
    paramtype:                                       class    class
    '''

    def validate(self, grade, all_grades = []):
        errors = []

        for grade_ in all_grades:
            if grade == grade_: # (Grade: __eq__(self, other) -> bool)
                errors.append('Aceasta problema este deja atribuita acestui student.')
                break

        if len(errors) > 0:
            raise ValidationException(errors)

    def validateGrade(self, gradeNumber):
        errors = []

        if gradeNumber < 1 or gradeNumber > 10:
            errors.append('Nota acordata trebuie sa fie intre 1 si 10 inclusiv.')

        if len(errors) > 0:
            raise ValidationException(errors)
