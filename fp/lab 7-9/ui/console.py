from termcolor import colored
from utilis.dict_operations import get_key_from_dict, get_firstValue_from_dict

class Console:
    '''
    Coordoneaza operatiile primite de la utilizator astfel incat sa se ajunga la raspunsul dorit
    '''

    def __init__(self, student_service, task_service, common_service):
        '''
        __s_service = multimea ce coordoneaza multimea de studenti si validarile acestora
        __t_service = multimea ce coordoneaza multimea de probleme si validarile acestora
        __c_service = multimea ce coordoneaza multimea de studenti si problemele atribuite acestora
        '''

        self.__s_service = student_service
        self.__t_service = task_service
        self.__c_service = common_service

    def __add_student(self):
        '''
        Adauga un student
        '''

        try:
            studentId = int(input('    ID-ul studentului: '))
            studentName = input('    Numele studentului: ')
            studentGroup = int(input('    Grupa studentului: '))
        except:
            print(colored('    ID-ul (int) | Nume (str) | Grupa (int)', 'red'))
            return

        try:
            added_student = self.__s_service.add_student(studentId, studentName, studentGroup)
            print(colored('    Studentul ' + added_student.getStudentName() + ' cu ID-ul ' + str(added_student.getStudentId()) + ' a fost adaugat in grupa ' + str(added_student.getStudentGroup()) + ' cu succes.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __delete_student(self):
        '''
        Sterge un student
        '''

        try:
            studentId = int(input('    ID-ul studentului: '))
        except:
            print(colored('    ID-ul (int)', 'red'))
            return

        try:
            deleted_student = self.__s_service.delete_student(studentId)
            self.__c_service.delete_student(studentId)
            print(colored('    Studentul ' + deleted_student.getStudentName() + ' cu ID-ul ' + str(deleted_student.getStudentId()) + ' a fost sters din grupa ' + str(deleted_student.getStudentGroup()) + ' cu succes.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __modify_student(self):
        '''
        Modifica detaliile unui student
        '''

        try:
            studentId = int(input('    ID-ul studentului: '))
            try:
                get_student = self.__s_service.get_copy_of_a_student(studentId)
            except Exception as e:
                print(colored('    ' + str(e), 'red'))
                return
        except:
            print(colored('    ID-ul (int)', 'red'))
            return

        try:
            modifiedStudentId = int(input('    Noul ID al studentului: '))
            modifiedStudentName = input('    Noul nume al studentului: ')
            modifiedStudentGroup = int(input('    Noua grupa a studentului: '))
        except:
            print(colored('    ID-ul (int) | Nume (str) | Grupa (int)', 'red'))
            return

        try:
            modified_student = self.__s_service.modify_student(studentId, modifiedStudentId, modifiedStudentName, modifiedStudentGroup)
            self.__c_service.update_student(studentId, modifiedStudentId)
            print(colored('    Studentul ' + get_student.getStudentName() + ' cu ID-ul ' + str(get_student.getStudentId()) + ' din grupa ' + str(get_student.getStudentGroup()) + ' a fost modificat cu succes. (Noul ID: %s, Noul nume: %s, Noua grupa: %s)' % (modified_student.getStudentId(), modified_student.getStudentName(), modified_student.getStudentGroup()), 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __show_students(self):
        '''
        Afiseaza lista curenta de studenti
        '''

        students_list = self.__s_service.get_all_students()
        if not len(students_list):
            print(colored('    Nu exista niciun student in lista.', 'red'))
        else:
            print(colored('    Lista curenta de studenti este', 'yellow'))
            for student in students_list:
                print(colored('    ' + str(student), 'green'))
                searched_student = self.__c_service.search_student(student.getStudentId())
                for task in searched_student[1]:
                    if get_firstValue_from_dict(task):
                        print(colored('        ' + str(self.__t_service.get_copy_of_a_task(get_key_from_dict(task))), 'green'), '| Nota:', str(get_firstValue_from_dict(task)))
                    else:
                        print(colored('        ' + str(self.__t_service.get_copy_of_a_task(get_key_from_dict(task))), 'green'))

    def __search_student(self):
        '''
        Cauta un student
        '''

        try:
            studentId = int(input('    ID-ul studentului: '))
        except:
            print(colored('    ID-ul (int)', 'red'))
            return

        try:
            searched_student = self.__c_service.search_student(studentId)
            print(colored('    ' + str(searched_student[0]), 'green'))
            for task in searched_student[1]:
                if get_firstValue_from_dict(task):
                    print(colored('        ' + str(self.__t_service.get_copy_of_a_task(get_key_from_dict(task))), 'green'), '| Nota:', str(get_firstValue_from_dict(task)))
                else:
                    print(colored('        ' + str(self.__t_service.get_copy_of_a_task(get_key_from_dict(task))), 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __add_task(self):
        '''
        Adauga o problema
        '''

        try:
            laboratory_task = input('    Numar laborator_numar problema: ')
            description = input('    Descriere: ')
            deadline = input('    Termen limita: ')
        except:
            print(colored('    Problema (Lab_prob) (str) | Descriere (str) | Termen (dd/mm/YYYY) (str)', 'red'))
            return

        try:
            added_task = self.__t_service.add_task(laboratory_task, description, deadline)
            print(colored('    Problema ' + added_task.getLaboratory_Task() + ' cu termenul limita ' + added_task.getDeadline() + ' a fost adaugata cu succes.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __delete_task(self):
        '''
        Sterge o problema
        '''

        try:
            laboratory_task = input('    Numar laborator_numar problema: ')
        except:
            print(colored('    Problema (Lab_prob) (str)', 'red'))
            return

        try:
            deleted_task = self.__t_service.delete_task(laboratory_task)
            self.__c_service.delete_task(laboratory_task)
            print(colored('    Problema ' + deleted_task.getLaboratory_Task() + ' cu termenul limita ' + deleted_task.getDeadline() + ' a fost stearsa cu succes.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __modify_task(self):
        '''
        Modifica detaliile unei probleme
        '''

        try:
            laboratory_task = input('    Numar laborator_numar problema: ')
            try:
                get_task = self.__t_service.get_copy_of_a_task(laboratory_task)
            except Exception as e:
                print(colored('    ' + str(e), 'red'))
                return
        except:
            print(colored('    Problema (Lab_prob) (str)', 'red'))
            return

        try:
            modifiedLaboratory_task = input('    Noul numar laborator_numar problema: ')
            modifiedDescription = input('    Noua descriere: ')
            modifiedDeadline = input('    Noul termen limita: ')
        except:
            print(colored('    Problema (Lab_prob) (str) | Descriere (str) | Termen (dd/mm/YYYY) (str)', 'red'))
            return

        try:
            modified_task = self.__t_service.modify_task(laboratory_task, modifiedLaboratory_task, modifiedDescription, modifiedDeadline)
            self.__c_service.update_task(laboratory_task, modifiedLaboratory_task)
            print(colored('    Problema ' + get_task.getLaboratory_Task() + ' cu termenul limita ' + get_task.getDeadline() + ' a fost modificata cu succes. (Noua problema: %s, Noua descriere: %s, Noul termen limita: %s)' % (modified_task.getLaboratory_Task(), modified_task.getDescription(), modified_task.getDeadline()), 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __show_tasks(self):
        '''
        Afiseaza lista curenta de probleme
        '''

        tasks_list = self.__t_service.get_all_tasks()
        if not len(tasks_list):
            print(colored('    Nu exista nicio problema in lista.', 'red'))
        else:
            print(colored('    Lista curenta de probleme este', 'yellow'))
            for task in tasks_list:
                print(colored('    ' + str(task), 'green'))
                searched_task = self.__c_service.search_task(task.getLaboratory_Task())
                for student in searched_task[1]:
                    print(colored('        ' + str(self.__s_service.get_copy_of_a_student(student)), 'green'))

    def __search_task(self):
        '''
        Cauta o problema
        '''

        try:
            laboratory_task = input('    Numar laborator_numar problema: ')
        except:
            print(colored('    Problema (Lab_prob) (str)', 'red'))
            return

        try:
            searched_task = self.__c_service.search_task(laboratory_task)
            print(colored('    ' + str(searched_task[0]), 'green'))
            for student in searched_task[1]:
                print(colored('        ' + str(self.__s_service.get_copy_of_a_student(student)), 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __assign_common(self):
        '''
        Atribuie o problema unui student
        '''

        try:
            studentId = int(input('    ID-ul studentului: '))
            laboratory_task = input('    Numar laborator_numar problema: ')
        except:
            print(colored('    ID-ul (int)', 'red'))
            print(colored('    Problema (Lab_prob) (str)', 'red'))
            return

        try:
            s_assigned = self.__c_service.assign_task(studentId, laboratory_task)
            print(colored('    Studentului ' + s_assigned[0].getStudentName() + ' cu ID-ul ' + str(s_assigned[0].getStudentId()) + ' din grupa ' + str(s_assigned[0].getStudentGroup()) + ' i-a fost atribuita problema ' + str(s_assigned[1].getLaboratory_Task()) + ' cu succes.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __evaluate_common(self):
        '''
        Evalueaza problema unui student
        '''

        try:
            studentId = int(input('    ID-ul studentului: '))
            laboratory_task = input('    Numar laborator_numar problema: ')
            grade = int(input('    Nota: '))
        except:
            print(colored('    ID-ul (int)', 'red'))
            print(colored('    Problema (Lab_prob) (str)', 'red'))
            print(colored('    Nota (int)', 'red'))
            return

        try:
            s_evaluate = self.__c_service.evaluate_task(studentId, laboratory_task, grade)
            print(colored('    Studentului ' + s_evaluate[0].getStudentName() + ' cu ID-ul ' + str(s_evaluate[0].getStudentId()) + ' din grupa ' + str(s_evaluate[0].getStudentGroup()) + ' i-a fost evaluata problema ' + str(s_evaluate[1].getLaboratory_Task()) + ' cu nota ' + str(grade) + '.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __generate_common(self):
        '''
        Genereaza random noi entitati Student
        '''

        try:
            entitiesNumber = int(input('    Numarul de entitati de generat: '))
        except:
            print(colored('    Numarul de entitati (int)', 'red'))
            return

        self.__count = 0
        for x in range(entitiesNumber):
            try:
                self.__c_service.generate()
                self.__count += 1
            except Exception as e:
                print(colored('    ' + str(e), 'red'))

        print(colored('    ' + str(self.__count) + ' noi studenti au fost generati si stocati.', 'green'))

    def showUI(self):
        finishedMain = False
        while not finishedMain:
            print('Optiuni disponibile: students, tasks, common, exit')
            option = input('Introduceti optiunea: ').lower().strip()
            if option == 'students':
                finishedSecondary = False
                while not finishedSecondary:
                    print('    Optiuni disponibile: s_add, s_delete, s_update, s_show, s_search, return')
                    option = input('    Introduceti optiunea: ').lower().strip()
                    if option == 's_add':
                        self.__add_student()
                    elif option == 's_delete':
                        self.__delete_student()
                    elif option == 's_update':
                        self.__modify_student()
                    elif option == 's_show':
                        self.__show_students()
                    elif option == 's_search':
                        self.__search_student()
                    elif option == 'return':
                        finishedSecondary = True
                    else:
                        print(colored('    Optiune invalida', 'red'))
            elif option == 'tasks':
                finishedSecondary = False
                while not finishedSecondary:
                    print('    Optiuni disponibile: t_add, t_delete, t_update, t_show, t_search, return')
                    option = input('    Introduceti optiunea: ').lower().strip()
                    if option == 't_add':
                        self.__add_task()
                    elif option == 't_delete':
                        self.__delete_task()
                    elif option == 't_update':
                        self.__modify_task()
                    elif option == 't_show':
                        self.__show_tasks()
                    elif option == 't_search':
                        self.__search_task()
                    elif option == 'return':
                        finishedSecondary = True
                    else:
                        print(colored('    Optiune invalida', 'red'))
            elif option == 'common':
                finishedSecondary = False
                while not finishedSecondary:
                    print('    Optiuni disponibile: assign, evaluate, generate, return')
                    option = input('    Introduceti optiunea: ').lower().strip()
                    if option == 'assign':
                        self.__assign_common()
                    elif option == 'evaluate':
                        self.__evaluate_common()
                    elif option == 'generate':
                        self.__generate_common()
                    elif option == 'return':
                        finishedSecondary = True
                    else:
                        print(colored('    Optiune invalida', 'red'))
            elif option == 'exit':
                finishedMain = True
            else:
                print(colored('Optiune invalida', 'red'))
