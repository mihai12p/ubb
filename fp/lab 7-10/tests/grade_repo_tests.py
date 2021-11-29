from unittest import TestCase
from domain.entities import Student, Task, Grade
from exceptions.exceptions import TaskNotAssignedException
from repository.repo import InMemoryGradeRepository, InFileGradeRepository

class TestCaseGradeMemoryRepo(TestCase):
    def setUp(self):
        self.__repo = InMemoryGradeRepository()

    def test_find_students(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1003, 'Adelin Gradinaru', 217)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 1)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 2)
        grade3 = Grade(student1.getStudentId(), task3.getLaboratory_Task(), 3)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)

        self.assertTrue(self.__repo.findStudents(task2) == [[student2.getStudentId(), grade2.getGrade()]])

    def test_find_tasks(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1003, 'Adelin Gradinaru', 217)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 1)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 2)
        grade3 = Grade(student1.getStudentId(), task3.getLaboratory_Task(), 3)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)

        self.assertTrue(self.__repo.findTasks(student2) == [[task2.getLaboratory_Task(), grade2.getGrade()]])

    def test_find_grades(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1003, 'Adelin Gradinaru', 217)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 1)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 2)
        grade3 = Grade(student1.getStudentId(), task3.getLaboratory_Task(), 3)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)

        self.assertTrue(self.__repo.findGrade(student1.getStudentId(), task3.getLaboratory_Task()) == grade3)

        self.assertRaises(TaskNotAssignedException, self.__repo.findGrade, student1.getStudentId(), task2.getLaboratory_Task())

class TestCaseGradeFileRepo(TestCase):
    def setUp(self):
        self.__repo = InFileGradeRepository('tests/data/test_grade_repo.txt')
        self.tearDown()

    def test_find_students(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1003, 'Adelin Gradinaru', 217)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 1)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 2)
        grade3 = Grade(student1.getStudentId(), task3.getLaboratory_Task(), 3)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)

        self.assertTrue(self.__repo.findStudents(task2) == [[student2.getStudentId(), grade2.getGrade()]])

    def test_find_tasks(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1003, 'Adelin Gradinaru', 217)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 1)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 2)
        grade3 = Grade(student1.getStudentId(), task3.getLaboratory_Task(), 3)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)

        self.assertTrue(self.__repo.findTasks(student2) == [[task2.getLaboratory_Task(), grade2.getGrade()]])

    def test_find_grades(self):
        student1 = Student(1001, 'Mihai Panduru', 215)
        student2 = Student(1003, 'Adelin Gradinaru', 217)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')

        grade1 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 1)
        grade2 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 2)
        grade3 = Grade(student1.getStudentId(), task3.getLaboratory_Task(), 3)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)

        self.assertTrue(self.__repo.findGrade(student1.getStudentId(), task3.getLaboratory_Task()) == grade3)

        self.assertRaises(TaskNotAssignedException, self.__repo.findGrade, student1.getStudentId(), task2.getLaboratory_Task())

    def tearDown(self):
        self.__repo.remove_all()
