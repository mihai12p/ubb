from unittest import TestCase
from domain.entities import Task
from exceptions.exceptions import TaskNotFoundException
from repository.repo import InMemoryTaskRepository

class TestCaseTaskMemoryRepo(TestCase):
    def setUp(self):
        self.__repo = InMemoryTaskRepository()

    def test_find_task(self):
        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        task3 = Task('6_6', 'Complex', '2/3/2022')

        self.__repo.store(task1)
        self.__repo.store(task2)

        self.assertTrue(self.__repo.findTask(task1.getLaboratory_Task()) == task1)
        self.assertTrue(self.__repo.findTask(task2.getLaboratory_Task()) == task2)

        self.assertRaises(TaskNotFoundException, self.__repo.findTask, task3.getLaboratory_Task())
