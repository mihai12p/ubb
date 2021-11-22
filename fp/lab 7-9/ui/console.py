from termcolor import colored

class Console:
    '''
    Coordoneaza operatiile primite de la utilizator astfel incat sa se ajunga la raspunsul dorit
    '''

    def __init__(self, student_service, task_service, grade_service):
        '''
        __s_service = multimea ce coordoneaza multimea de studenti si validarile acestora
        __t_service = multimea ce coordoneaza multimea de probleme si validarile acestora
        __g_service = multimea ce coordoneaza multimea de studenti si problemele atribuite acestora
        '''

        self.__s_service = student_service
        self.__t_service = task_service
        self.__g_service = grade_service

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
            searched_student = self.__s_service.findStudent(studentId)
            self.__g_service.delete_tasks_for_student(searched_student)

            deleted_student = self.__s_service.delete_student(studentId)
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
                search_tasks_for_student = self.__g_service.findTasks(student)
                print(colored('    ' + str(student), 'green'))
                if len(search_tasks_for_student):
                    for taskGrade in search_tasks_for_student:
                        task = taskGrade[0]
                        grade = taskGrade[1]
                        if grade:
                            print(colored('        ' + str(task), 'green'), '| Nota:', str(grade))
                        else:
                            print(colored('        ' + str(task), 'green'))

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
            searched_student = self.__s_service.findStudent(studentId)
            search_tasks_for_student = self.__g_service.findTasks(searched_student)

            print(colored('    ' + str(searched_student), 'green'))
            if len(search_tasks_for_student):
                for taskGrade in search_tasks_for_student:
                    task = taskGrade[0]
                    grade = taskGrade[1]
                    if grade:
                        print(colored('        ' + str(task), 'green'), '| Nota:', str(grade))
                    else:
                        print(colored('        ' + str(task), 'green'))
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
            searched_task = self.__t_service.findTask(laboratory_task)
            self.__g_service.delete_student_for_tasks(searched_task)

            deleted_task = self.__t_service.delete_task(laboratory_task)
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
                search_students_for_task = self.__g_service.findStudents(task)
                print(colored('    ' + str(task), 'green'))
                if len(search_students_for_task):
                    for studentGrade in search_students_for_task:
                        student = studentGrade[0]
                        grade = studentGrade[1]
                        if grade:
                            print(colored('        ' + str(student), 'green'), '| Nota:', str(grade))
                        else:
                            print(colored('        ' + str(student), 'green'))

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
            searched_task = self.__t_service.findTask(laboratory_task)
            search_students_for_task = self.__g_service.findStudents(searched_task)

            print(colored('    ' + str(searched_task), 'green'))
            if len(search_students_for_task):
                for studentGrade in search_students_for_task:
                    student = studentGrade[0]
                    grade = studentGrade[1]
                    if grade:
                        print(colored('        ' + str(student), 'green'), '| Nota:', str(grade))
                    else:
                        print(colored('        ' + str(student), 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __assign_task(self):
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
            student = self.__s_service.findStudent(studentId)
            task = self.__t_service.findTask(laboratory_task)
            t_assigned = self.__g_service.assign_task(student, task)
            print(colored('    Studentului ' + t_assigned.getStudent().getStudentName() + ' cu ID-ul ' + str(t_assigned.getStudent().getStudentId()) + ' din grupa ' + str(t_assigned.getStudent().getStudentGroup()) + ' i-a fost atribuita problema '+ str(t_assigned.getTask().getLaboratory_Task()) + ' cu succes.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __evaluate_task(self):
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
            student = self.__s_service.findStudent(studentId)
            task = self.__t_service.findTask(laboratory_task)
            self.__g_service.evaluate_task(student, task, grade)
            print(colored('    Studentului ' + student.getStudentName() + ' cu ID-ul ' + str(student.getStudentId()) + ' din grupa ' + str(student.getStudentGroup()) + ' i-a fost evaluata problema ' + str(task.getLaboratory_Task()) + ' cu nota ' + str(grade) + '.', 'green'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __generate_student(self):
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
                self.__s_service.generate()
                self.__count += 1
            except Exception as e:
                print(colored('    ' + str(e), 'red'))

        print(colored('    ' + str(self.__count) + ' noi studenti au fost generati si stocati.', 'green'))

    def __statistics_1(self):
        '''
        Creaza statistici pentru un laborator dat
        '''

        try:
            laboratory_task = input('    Numar laborator_numar problema: ')
        except:
            print(colored('    Problema (Lab_prob) (str)', 'red'))
            return

        try:
            searched_task = self.__t_service.findTask(laboratory_task)
            statistics = self.__g_service.statistics_students_for_task(searched_task)

            print(colored('    ' + str(searched_task), 'green'))
            if len(statistics):
                print(colored('        Stundetii ordonati alfabetic dupa nume, nota la problema data sunt', 'yellow'))
                for x in statistics:
                    print(colored('        ' + str(x.getStudent()), 'green'), '| Nota:', str(x.getGrade()))
            else:
                print(colored('        Nu exista niciun astfel de student.', 'red'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __statistics_2(self):
        '''
        Creaza statistici pentru toti studentii cu media notelor mai mica ca 5
        '''

        try:
            statistics = self.__g_service.statistics_students()

            if len(statistics):
                print(colored('        Toti studentii cu media notelor mai mica ca 5 sunt', 'yellow'))
                for x in statistics:
                    print(colored('        ' + str(x.getStudent()), 'green'), '| Media notelor:', str(x.getGrade()))
            else:
                print(colored('        Nu exista niciun astfel de student.', 'red'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def __statistics_top3(self):
        '''
        Creaza statistica top3 a laboratoarelor cu cele mai multe note
        '''

        try:
            statistics = self.__g_service.statistics_top3()

            if len(statistics):
                print(colored('        Top3 laboratoare', 'yellow'))
                for x in statistics:
                    print(colored('        ' + 'Numar laborator_problema: ' + x.getStudent().getLaboratory_Task() + ' | Descriere: ' + x.getStudent().getDescription(), 'green'), '| Numar note:', str(x.getGrade()))
            else:
                print(colored('        Nu exista niciun astfel de laborator.', 'red'))
        except Exception as e:
            print(colored('    ' + str(e), 'red'))

    def showUI(self):
        finishedMain = False
        while not finishedMain:
            print('Optiuni disponibile: students, tasks, common, exit')
            option = input('Introduceti optiunea: ').lower().strip()
            if option == 'students':
                finishedSecondary = False
                while not finishedSecondary:
                    print('    Optiuni disponibile: s_add, s_delete, s_update, s_show, s_search, s_generate, return')
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
                    elif option == 's_generate':
                        self.__generate_student()
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
                    print('    Optiuni disponibile: assign, evaluate, stats1, stats2, t_top3, return')
                    option = input('    Introduceti optiunea: ').lower().strip()
                    if option == 'assign':
                        self.__assign_task()
                    elif option == 'evaluate':
                        self.__evaluate_task()
                    elif option == 'stats1':
                        self.__statistics_1()
                    elif option == 'stats2':
                        self.__statistics_2()
                    elif option == 't_top3':
                        self.__statistics_top3()
                    elif option == 'return':
                        finishedSecondary = True
                    else:
                        print(colored('    Optiune invalida', 'red'))
            elif option == 'exit':
                finishedMain = True
            else:
                print(colored('Optiune invalida', 'red'))
