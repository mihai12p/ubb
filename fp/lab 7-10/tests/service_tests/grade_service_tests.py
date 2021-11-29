from unittest import TestCase
from domain.entities import Student, Task, Grade
from domain.validators import GradeValidator
from repository.repo import InMemoryStudentRepository, InMemoryTaskRepository, InMemoryGradeRepository
from service.serv import GradeService

class TestCaseTaskMemoryRepo(TestCase):
    def setUp(self):
        self.__s_repo = InMemoryStudentRepository()
        self.__t_repo = InMemoryTaskRepository()
        self.__repo = InMemoryGradeRepository()
        self.__validator = GradeValidator()
        self.__service = GradeService(self.__repo, self.__validator, self.__s_repo, self.__t_repo)

    def test_assign_task(self):
        student1 = Student(12, 'Mihai Panduru', 215)

        self.__s_repo.store(student1)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')

        self.__t_repo.store(task1)
        self.__t_repo.store(task2)

        assigned_task1 = self.__service.assign_task(student1, task1)
        assigned_task2 = self.__service.assign_task(student1, task2)

        self.assertTrue(len(self.__repo.get_all_grades()) == 2)
        self.assertTrue(assigned_task1.getStudentId() == student1.getStudentId())
        self.assertTrue(assigned_task2.getLaboratory_Task() == task2.getLaboratory_Task())

    def test_evaluate_task(self):
        student1 = Student(12, 'Mihai Panduru', 215)

        self.__s_repo.store(student1)

        task1 = Task('7_2', 'Catalog', '8/11/2021')

        self.__t_repo.store(task1)

        self.__service.assign_task(student1, task1)
        evaluated_task1 = self.__service.evaluate_task(student1, task1, 5)

        self.assertTrue(evaluated_task1.getGrade() == 5)

    def test_statistics_students_for_task(self):
        student1 = Student(12, 'Mihai Panduru', 215)
        student2 = Student(22, 'Adelin Gradinaru', 217)
        student3 = Student(23, 'Alberto Mihai', 213)
        student4 = Student(25, 'Kevin Axmann', 219)

        self.__s_repo.store(student1)
        self.__s_repo.store(student2)
        self.__s_repo.store(student3)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')
        task4 = Task('9_1', 'Parlament', '1/5/2024')

        self.__t_repo.store(task1)
        self.__t_repo.store(task2)
        self.__t_repo.store(task3)
        self.__t_repo.store(task4)

        grade1 = Grade(student2.getStudentId(), task1.getLaboratory_Task(), 6)
        grade2 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 4)
        grade3 = Grade(student3.getStudentId(), task1.getLaboratory_Task(), 3)
        grade4 = Grade(student3.getStudentId(), task2.getLaboratory_Task(), 6.9)
        grade5 = Grade(student2.getStudentId(), task3.getLaboratory_Task(), 9)
        grade6 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 3)
        grade7 = Grade(student4.getStudentId(), task2.getLaboratory_Task(), 9)
        grade8 = Grade(student4.getStudentId(), task4.getLaboratory_Task(), 10)
        grade9 = Grade(student2.getStudentId(), task4.getLaboratory_Task(), 10)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)
        self.__repo.store(grade4)
        self.__repo.store(grade5)
        self.__repo.store(grade6)
        self.__repo.store(grade7)
        self.__repo.store(grade8)
        self.__repo.store(grade9)

        statistics = self.__service.statistics_students_for_task(task1)

        self.assertTrue(len(statistics) == 3)
        self.assertTrue(statistics[0].getStudent() == student2)
        self.assertTrue(statistics[0].getGrade() == 6)
        self.assertTrue(statistics[1].getStudent() == student3)
        self.assertTrue(statistics[1].getGrade() == 3)
        self.assertTrue(statistics[2].getStudent() == student1)
        self.assertTrue(statistics[2].getGrade() == 4)

    def test_statistics_students(self):
        student1 = Student(12, 'Mihai Panduru', 215)
        student2 = Student(22, 'Adelin Gradinaru', 217)
        student3 = Student(23, 'Alberto Mihai', 213)
        student4 = Student(25, 'Kevin Axmann', 219)

        self.__s_repo.store(student1)
        self.__s_repo.store(student2)
        self.__s_repo.store(student3)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')
        task4 = Task('9_1', 'Parlament', '1/5/2024')

        self.__t_repo.store(task1)
        self.__t_repo.store(task2)
        self.__t_repo.store(task3)
        self.__t_repo.store(task4)

        grade1 = Grade(student2.getStudentId(), task1.getLaboratory_Task(), 6)
        grade2 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 4)
        grade3 = Grade(student3.getStudentId(), task1.getLaboratory_Task(), 3)
        grade4 = Grade(student3.getStudentId(), task2.getLaboratory_Task(), 6.9)
        grade5 = Grade(student2.getStudentId(), task3.getLaboratory_Task(), 9)
        grade6 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 3)
        grade7 = Grade(student4.getStudentId(), task2.getLaboratory_Task(), 9)
        grade8 = Grade(student4.getStudentId(), task4.getLaboratory_Task(), 10)
        grade9 = Grade(student2.getStudentId(), task4.getLaboratory_Task(), 10)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)
        self.__repo.store(grade4)
        self.__repo.store(grade5)
        self.__repo.store(grade6)
        self.__repo.store(grade7)
        self.__repo.store(grade8)
        self.__repo.store(grade9)

        statistics = self.__service.statistics_students()

        self.assertTrue(len(statistics) == 2)
        self.assertTrue(statistics[0].getStudent() == student1)
        self.assertTrue(statistics[0].getGrade() == 4.0)
        self.assertTrue(statistics[1].getStudent() == student3)
        self.assertTrue(statistics[1].getGrade() == 4.95)

    def test_blackbox_statistics_top3(self):
        student1 = Student(12, 'Mihai Panduru', 215)
        student2 = Student(22, 'Adelin Gradinaru', 217)
        student3 = Student(23, 'Alberto Mihai', 213)
        student4 = Student(25, 'Kevin Axmann', 219)

        self.__s_repo.store(student1)
        self.__s_repo.store(student2)
        self.__s_repo.store(student3)

        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('7_3', 'Revelion', '12/1/2022')
        task4 = Task('9_1', 'Parlament', '1/5/2024')

        self.__t_repo.store(task1)
        self.__t_repo.store(task2)
        self.__t_repo.store(task3)
        self.__t_repo.store(task4)

        grade1 = Grade(student2.getStudentId(), task1.getLaboratory_Task(), 6)
        grade2 = Grade(student1.getStudentId(), task1.getLaboratory_Task(), 4)
        grade3 = Grade(student3.getStudentId(), task1.getLaboratory_Task(), 3)
        grade4 = Grade(student3.getStudentId(), task2.getLaboratory_Task(), 6.9)
        grade5 = Grade(student2.getStudentId(), task3.getLaboratory_Task(), 9)
        grade6 = Grade(student2.getStudentId(), task2.getLaboratory_Task(), 3)
        grade7 = Grade(student4.getStudentId(), task2.getLaboratory_Task(), 9)
        grade8 = Grade(student4.getStudentId(), task4.getLaboratory_Task(), 10)
        grade9 = Grade(student2.getStudentId(), task4.getLaboratory_Task(), 10)

        self.__repo.store(grade1)
        self.__repo.store(grade2)
        self.__repo.store(grade3)
        self.__repo.store(grade4)
        self.__repo.store(grade5)
        self.__repo.store(grade6)
        self.__repo.store(grade7)
        self.__repo.store(grade8)
        self.__repo.store(grade9)

        statistics = self.__service.statistics_top3()

        self.assertTrue(len(statistics) == 3)
        self.assertTrue(statistics[0].getGrade() == 3)
        self.assertTrue(statistics[1].getGrade() == 3)
        self.assertTrue(statistics[2].getGrade() == 2)
        