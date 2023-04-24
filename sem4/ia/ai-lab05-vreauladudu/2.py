import os
import csv
import matplotlib.pyplot as plt

FILE_TO_LOAD = "flowers"

def ReadCSV(FileName: str) -> list:
    labels = []
    with open(FileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count != 0:
                print(f'\tType: {row[0]}, | PredictedType: {row[1]}')
                labels.append([row[0], row[1]])
            line_count += 1

    return labels

def EvalClassification(labels: list):
    mat = [[0 for _ in range(3)] for _ in range(3)]

    for label in labels:
        realLabel = label[0]
        predictedLabel = label[1]

        if realLabel == 'Daisy':
            if predictedLabel == 'Daisy':
                mat[0][0] += 1
            elif predictedLabel == 'Tulip':
                mat[0][1] += 1
            else:
                mat[0][2] += 1
        elif realLabel == 'Tulip':
            if predictedLabel == 'Daisy':
                mat[1][0] += 1
            elif predictedLabel == 'Tulip':
                mat[1][1] += 1
            else:
                mat[1][2] += 1
        else:
            if predictedLabel == 'Daisy':
                mat[2][0] += 1
            elif predictedLabel == 'Tulip':
                mat[2][1] += 1
            else:
                mat[2][2] += 1

    acc = sum(mat[i][i] for i in range(3)) / len(labels)
    precision = [mat[i][i] / sum(mat[j][i] for j in range(3)) for i in range(3)]
    recall = [mat[i][i] / sum(mat[i][j] for j in range(3)) for i in range(3)]

    return acc, precision, recall

if __name__ == "__main__":
    filePath = os.path.join(os.path.curdir,  FILE_TO_LOAD + '.csv')
    labels = ReadCSV(filePath)

    acc, precision, recall = EvalClassification(labels)
    print("Accuracy {0}\nPrecision {1}\nRecall {2}".format(acc, precision, recall))