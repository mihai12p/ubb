import time
import subprocess

JAVA_EXE_PATH = r'C:\Users\example\.jdks\jbr-17.0.7\bin\java.exe'
JAVA_CLASS_PATH = r'D:\ppd\lab 1\myjava\out\production\myjava'
CPP_EXE_PATH = r'D:\ppd\lab 1\mycpp'
TASK = 'line'  # line/column

if __name__ == '__main__':
    configs_cpp = [
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_10_10_3.in', 'static', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_10_10_3.in', 'dynamic', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_10_10_3.in', 'static', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_10_10_3.in', 'dynamic', 'parralel', '4', TASK],

        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'static', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'dynamic', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'static', 'parralel', '2', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'dynamic', 'parralel', '2', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'static', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'dynamic', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'static', 'parralel', '8', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'dynamic', 'parralel', '8', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'static', 'parralel', '16', TASK],
        [CPP_EXE_PATH + '/conv-c++_1000_1000.exe', 'data_1000_1000_5.in', 'dynamic', 'parralel', '16', TASK],

        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'static', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'dynamic', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'static', 'parralel', '2', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'dynamic', 'parralel', '2', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'static', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'dynamic', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'static', 'parralel', '8', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'dynamic', 'parralel', '8', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'static', 'parralel', '16', TASK],
        [CPP_EXE_PATH + '/conv-c++_10_10000.exe', 'data_10_10000_5.in', 'dynamic', 'parralel', '16', TASK],

        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'static', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'dynamic', 'sequential', '1', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'static', 'parralel', '2', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'dynamic', 'parralel', '2', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'static', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'dynamic', 'parralel', '4', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'static', 'parralel', '8', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'dynamic', 'parralel', '8', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'static', 'parralel', '16', TASK],
        [CPP_EXE_PATH + '/conv-c++_10000_10.exe', 'data_10000_10_5.in', 'dynamic', 'parralel', '16', TASK]
    ]

    configs_java = [
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10_3.in', 'sequential', '1', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10_3.in', 'parralel', '4', TASK],

        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_1000_1000_5.in', 'sequential', '1', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_1000_1000_5.in', 'parralel', '2', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_1000_1000_5.in', 'parralel', '4', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_1000_1000_5.in', 'parralel', '8', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_1000_1000_5.in', 'parralel', '16', TASK],

        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10000_5.in', 'sequential', '1', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10000_5.in', 'parralel', '2', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10000_5.in', 'parralel', '4', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10000_5.in', 'parralel', '8', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10_10000_5.in', 'parralel', '16', TASK],

        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10000_10_5.in', 'sequential', '1', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10000_10_5.in', 'parralel', '2', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10000_10_5.in', 'parralel', '4', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10000_10_5.in', 'parralel', '8', TASK],
        [JAVA_EXE_PATH, '-cp', JAVA_CLASS_PATH, 'Main', 'data_10000_10_5.in', 'parralel', '16', TASK]
    ]

    for config in configs_cpp:  # configs_cpp/configs_java
        total_time = 0
        num_runs = 10
        
        for _ in range(num_runs):
            start_time = time.time()
            subprocess.run(config, check=True)
            total_time += time.time() - start_time

            if not 'sequential' in config:
                with open('data.out', 'r') as f1, open('data.out.sequential', 'r') as f2:
                    content1 = f1.read()
                    content2 = f2.read()
                    assert content1 == content2
        
        average_time = total_time / num_runs
        print(f'For configuration {config}, average time taken: {average_time:.5f} seconds')