from unittest import TestCase
from domain.entities import Student, Task, Grade
from domain.validators import GradeValidator
from exceptions.exceptions import ValidationException

class TestCaseGradeDomain(TestCase):
    def setUp(self):
        self.__validator = GradeValidator()

    def test_create_grade(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1001, 'Alberto Mihai', 215)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('7_2', 'Complex', '2/3/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 9)
        self.assertTrue(grade1.getStudentId() == student1.getStudentId())
        self.assertTrue(grade1.getLaboratory_Task() == task1.getLaboratory_Task())
        self.assertTrue(grade1.getGrade() == 9)

        grade1.setStudentId(student2.getStudentId())
        grade1.setLaboratory_Task(task2.getLaboratory_Task())
        grade1.setGrade(10)

        self.assertTrue(grade1.getStudentId() == student2.getStudentId())
        self.assertTrue(grade1.getLaboratory_Task() == task2.getLaboratory_Task())
        self.assertTrue(grade1.getGrade() == 10)

    def test_equal_grade(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1001, 'Alberto Mihai', 215)
        student3 = Student(1002, 'Alberto Mihai', 215)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('7_2', 'Complex', '2/3/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 9)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 9)

        self.assertEqual(grade1, grade2)

        grade2.setStudentId(student3.getStudentId())
        self.assertNotEqual(grade1, grade2)

    def test_validate_grade(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        task1 = Task('7_2', 'Gestionare', '8/11/2021')
        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 5)

        self.__validator.validate(grade1)

        grade2 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 12)
        self.assertRaises(ValidationException, self.__validator.validateGrade, grade2.getGrade())
        grade3 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 0)
        self.assertRaises(ValidationException, self.__validator.validateGrade, grade3.getGrade())
