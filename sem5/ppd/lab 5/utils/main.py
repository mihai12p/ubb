import time
import subprocess

LAB_PATH = r'D:\ppd\lab 5'
CPP_EXE_PATH = LAB_PATH + r'\concurs\x64\Release'

if __name__ == '__main__':
    configs_cpp = [
        [CPP_EXE_PATH + '/concurs.exe', '4', '2'],
        [CPP_EXE_PATH + '/concurs.exe', '4', '4'],
        [CPP_EXE_PATH + '/concurs.exe', '4', '12']
    ]

    for config in configs_cpp:
        total_time = 0
        num_runs = 10
        
        for _ in range(num_runs):
            start_time = time.time()
            result = subprocess.run(config, check=True)
            total_time += time.time() - start_time

            with open(LAB_PATH + r'\output\Clasament.txt', 'r') as f1, open(LAB_PATH + r'\output\Clasament.txt.sequential', 'r') as f2:
                content1 = f1.read()
                content2 = f2.read()
                assert content1 == content2
        
        average_time = total_time / num_runs
        print(f'For configuration {config}, average time taken: {average_time:.5f} seconds')