from unittest import TestCase
from domain.entities import Student
from exceptions.exceptions import StudentNotFoundException
from repository.repo import InMemoryStudentRepository

class TestCaseStudentMemoryRepo(TestCase):
    def setUp(self):
        self.__repo = InMemoryStudentRepository()

    def test_find_student(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1002, 'Alberto Mihai', 215)
        student3 = Student(1003, 'Alberto Mihai', 215)

        self.__repo.store(student1)
        self.__repo.store(student2)

        self.assertTrue(self.__repo.findStudent(student1.getStudentId()) == student1)
        self.assertTrue(self.__repo.findStudent(student2.getStudentId()) == student2)

        self.assertRaises(StudentNotFoundException, self.__repo.findStudent, student3.getStudentId())
