import time
import subprocess

CPP_EXE_PATH = r'D:\ppd\lab 3\mycpp'

if __name__ == '__main__':
    configs_cpp = [
        ['mpiexec', '-n', '5',  CPP_EXE_PATH + '/conv-c++.exe'],
        ['mpiexec', '-n', '9',  CPP_EXE_PATH + '/conv-c++.exe'],
        ['mpiexec', '-n', '21', CPP_EXE_PATH + '/conv-c++.exe']
    ]

    for config in configs_cpp:
        total_time_t1 = 0
        total_time_t2 = 0
        num_runs = 10
        
        for _ in range(num_runs):
            start_time = time.time()
            result = subprocess.run(config, check=True, capture_output=True)
            total_time_t1 += time.time() - start_time
            total_time_t2 += float(result.stdout.decode())

            with open('data.out', 'r') as f1, open('data.lab2.out', 'r') as f2:
                content1 = f1.read()
                content2 = f2.read()
                assert content1 == content2
        
        average_time_t1 = total_time_t1 / num_runs
        average_time_t2 = total_time_t2 / num_runs
        print(f'For configuration {config}, average time taken T1: {average_time_t1:.5f} and T2: {average_time_t2:.5f} seconds')