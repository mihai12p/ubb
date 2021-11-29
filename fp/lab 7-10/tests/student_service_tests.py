from unittest import TestCase
from domain.validators import StudentValidator
from exceptions.exceptions import ValidationException
from repository.repo import InMemoryStudentRepository, InFileStudentRepository
from service.serv import StudentService

class TestCaseStudentMemoryService(TestCase):
    def setUp(self):
        self.__repo = InMemoryStudentRepository()
        self.__validator = StudentValidator()
        self.__service = StudentService(self.__repo, self.__validator)

    def test_add_student(self):
        added_student = self.__service.add_student(1002, 'Alberto Mihai', 215)
        added_student2 = self.__service.add_student(1001, 'Mihai Panduru', 217)

        self.assertTrue(len(self.__repo.get_all_students()) == 2)
        self.assertTrue(added_student.getStudentName() == 'Alberto Mihai')
        self.assertTrue(added_student2.getStudentGroup() == 217)

    def test_delete_student(self):
        self.__service.add_student(1002, 'Alberto Mihai', 215)
        self.__service.add_student(1001, 'Mihai Panduru', 217)

        self.assertRaises(ValidationException, self.__service.delete_student, 1003)

    def test_vcopy_student(self):
        added_student = self.__service.add_student(1002, 'Alberto Mihai', 215)

        self.assertFalse(id(added_student) == id(self.__service.get_copy_of_a_student(added_student.getStudentId())))

    def test_update_student(self):
        added_student = self.__service.add_student(1002, 'Alberto Mihai', 215)

        self.__service.modify_student(added_student.getStudentId(), 77777, 'Adelin Gradinaru', 666)

        self.assertTrue(added_student.getStudentId() == 77777)
        self.assertTrue(added_student.getStudentName() == 'Adelin Gradinaru')
        self.assertTrue(added_student.getStudentGroup() == 666)

class TestCaseStudentFileService(TestCase):
    def setUp(self):
        self.__repo = InFileStudentRepository('tests/data/test_student_service.txt')
        self.__validator = StudentValidator()
        self.__service = StudentService(self.__repo, self.__validator)
        self.tearDown()

    def test_add_student(self):
        added_student = self.__service.add_student(1002, 'Alberto Mihai', 215)
        added_student2 = self.__service.add_student(1001, 'Mihai Panduru', 217)

        self.assertTrue(len(self.__repo.get_all_students()) == 2)
        self.assertTrue(added_student.getStudentName() == 'Alberto Mihai')
        self.assertTrue(added_student2.getStudentGroup() == 217)

    def test_delete_student(self):
        self.__service.add_student(1002, 'Alberto Mihai', 215)
        self.__service.add_student(1001, 'Mihai Panduru', 217)

        self.assertRaises(ValidationException, self.__service.delete_student, 1003)

    def test_vcopy_student(self):
        added_student = self.__service.add_student(1002, 'Alberto Mihai', 215)

        self.assertFalse(id(added_student) == id(self.__service.get_copy_of_a_student(added_student.getStudentId())))

    def test_update_student(self):
        added_student = self.__service.add_student(1002, 'Alberto Mihai', 215)

        self.__service.modify_student(added_student.getStudentId(), 77777, 'Adelin Gradinaru', 666)

        self.assertTrue(added_student.getStudentId() == 77777)
        self.assertTrue(added_student.getStudentName() == 'Adelin Gradinaru')
        self.assertTrue(added_student.getStudentGroup() == 666)

    def tearDown(self):
        self.__repo.remove_all()
