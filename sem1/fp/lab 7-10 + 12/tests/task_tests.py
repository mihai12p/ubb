from unittest import TestCase
from domain.entities import Task
from domain.validators import TaskValidator
from exceptions.exceptions import ValidationException

class TestCaseTaskDomain(TestCase):
    def setUp(self):
        self.__validator = TaskValidator()

    def test_create_task(self):
        task1 = Task('7_2', 'Catalog', '8/11/2021')
        self.assertTrue(task1.getLaboratory_Task() == '7_2')
        self.assertTrue(task1.getDescription() == 'Catalog')
        self.assertTrue(task1.getDeadline() == '8/11/2021')

        task1.setLaboratory_Task('8_4')
        task1.setDescription('Gestionare')
        task1.setDeadline('3/12/2021')

        self.assertTrue(task1.getLaboratory_Task() == '8_4')
        self.assertTrue(task1.getDescription() == 'Gestionare')
        self.assertTrue(task1.getDeadline() == '3/12/2021')

    def test_equal_task(self):
        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('7_2', 'Complex', '2/3/2022')

        self.assertEqual(task1, task2)

        task3 = Task('8_4', 'Complex', '2/3/2022')
        self.assertNotEqual(task1, task3)

    def test_validate_task(self):
        task1 = Task('7_2', 'Catalog', '8/11/2021')
        task2 = Task('8_4', 'Complex', '2/3/2022')
        self.__validator.validate(task1)
        self.__validator.validate(task2)

        task3 = Task('7_2', 'Gestionare', '8.11.2021')
        self.assertRaises(ValidationException, self.__validator.validate, task3)
        task4 = Task('7 2', 'Gestionare', '8/11/2021')
        self.assertRaises(ValidationException, self.__validator.validate, task4)
        task5 = Task('', '', '')
        self.assertRaises(ValidationException, self.__validator.validate, task5)
