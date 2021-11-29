from tests import student_tests, task_tests, grade_tests, student_repo_tests, task_repo_tests, grade_repo_tests, \
                    student_service_tests, task_service_tests, grade_service_tests

import unittest
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(student_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(task_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(grade_tests))

unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(student_repo_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(task_repo_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(grade_repo_tests))

unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(student_service_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(task_service_tests))
unittest.TextTestRunner(verbosity=2).run(unittest.TestLoader().loadTestsFromModule(grade_service_tests))
