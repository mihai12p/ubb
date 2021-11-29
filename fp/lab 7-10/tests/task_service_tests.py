from unittest import TestCase
from domain.validators import TaskValidator
from exceptions.exceptions import ValidationException
from repository.repo import InMemoryTaskRepository
from service.serv import TaskService

class TestCaseTaskService(TestCase):
    def setUp(self):
        self.__repo = InMemoryTaskRepository()
        self.__validator = TaskValidator()
        self.__service = TaskService(self.__repo, self.__validator)

    def test_add_task(self):
        added_task = self.__service.add_task('7_2', 'Catalog', '8/11/2021')
        added_task2 = self.__service.add_task('8_4', 'Complex', '2/3/2022')

        self.assertTrue(len(self.__repo.get_all_tasks()) == 2)
        self.assertTrue(added_task.getDeadline() == '8/11/2021')
        self.assertTrue(added_task2.getLaboratory_Task() == '8_4')

    def test_delete_task(self):
        self.__service.add_task('7_2', 'Catalog', '8/11/2021')
        self.__service.add_task('8_4', 'Complex', '2/3/2022')

        self.assertRaises(ValidationException, self.__service.delete_task, '7_3')

    def test_vcopy_task(self):
        added_task = self.__service.add_task('7_2', 'Catalog', '8/11/2021')

        self.assertFalse(id(added_task) == id(self.__service.get_copy_of_a_task(added_task.getLaboratory_Task())))

    def test_update_task(self):
        added_task = self.__service.add_task('7_2', 'Catalog', '8/11/2021')

        self.__service.modify_task(added_task.getLaboratory_Task(), '6_2', 'Revelion', '1/1/2022')

        self.assertTrue(added_task.getLaboratory_Task() == '6_2')
        self.assertTrue(added_task.getDescription() == 'Revelion')
        self.assertTrue(added_task.getDeadline() == '1/1/2022')
