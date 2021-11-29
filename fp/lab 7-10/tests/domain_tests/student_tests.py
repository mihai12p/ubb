from unittest import TestCase
from domain.entities import Student
from domain.validators import StudentValidator
from exceptions.exceptions import ValidationException

class TestCaseStudentDomain(TestCase):
    def setUp(self):
        self.__validator = StudentValidator()

    def test_create_student(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        self.assertTrue(student1.getStudentId() == 1001)
        self.assertTrue(student1.getStudentName() == 'Mihai Panduru')
        self.assertTrue(student1.getStudentGroup() == 215)

        student1.setStudentId(1002)
        student1.setStudentName('Andrei Paunescu')
        student1.setStudentGroup(212)

        self.assertTrue(student1.getStudentId() == 1002)
        self.assertTrue(student1.getStudentName() == 'Andrei Paunescu')
        self.assertTrue(student1.getStudentGroup() == 212)

    def test_equal_student(self):
        student1 = Student(1002, 'Mihai Panduru', 215)
        student2 = Student(1002, 'Alberto Mihai', 215)

        self.assertEqual(student1, student2)

        student3 = Student(1001, 'Alberto Mihai', 215)
        self.assertNotEqual(student1, student3)

    def test_validate_student(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1002, 'Alberto Mihai', 215)
        self.__validator.validate(student1)
        self.__validator.validate(student2)

        student3 = Student(1002, 'Alberto', 215)
        self.assertRaises(ValidationException, self.__validator.validate, student3)
        student4 = Student(0, 'Alberto Mihai', 1)
        self.assertRaises(ValidationException, self.__validator.validate, student4)
        student5 = Student(1, 'Alberto Mihai', 0)
        self.assertRaises(ValidationException, self.__validator.validate, student5)
