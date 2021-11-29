class StudentException(Exception):
    pass

class ValidationException(StudentException):
    def __init__(self, msgs):
        self.__err_msgs = msgs

    def getMessages(self):
        return self.__err_msgs

    def __str__(self):
        return 'Validation Exception: ' + str(self.__err_msgs)

class RepositoryException(StudentException):
    def __init__(self, msg):
        self.__msg = msg

    def getMessages(self):
        return self.__msg

    def __str__(self):
        return 'Repository Exception: ' + str(self.__msg)

class StudentNotFoundException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, 'Studentul cautat nu exista.')

class TaskNotFoundException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, 'Problema cautata nu exista.')

class TaskNotAssignedException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, 'Aceasta problema nu este atribuita acestui student.')
