from tests.domain_tests import student_tests, task_tests, grade_tests

import unittest
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(student_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(task_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(grade_tests))
