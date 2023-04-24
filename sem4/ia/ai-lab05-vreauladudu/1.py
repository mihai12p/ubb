import os
import csv
from math import sqrt
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error

FILE_TO_LOAD = "sport"

def ReadCSV(FileName: str) -> list:
    labels = []
    with open(FileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count != 0:
                print(f'\tWeight: {row[0]}, Waist: {row[1]}, Pulse: {row[2]} | PredictedWeight: {row[3]}, PredictedWaist: {row[4]}, PredictedPulse: {row[5]}')
                realLabels = [int(row[0]), int(row[1]), int(row[2])]
                predictedLabels = [int(row[3]), int(row[4]), int(row[5])]
                labels.append([realLabels, predictedLabels])
            line_count += 1

    return labels

def RegressionError(labels: list) -> list:
    r = []
    p = []

    for label in labels:
        realLabel = label[0]
        predictedLabel = label[1]

        # MAE = MeanAbsoluteError
        mae = sum(abs(r - c) for r, c in zip(realLabel, predictedLabel)) / len(realLabel)
        # RMSE = RootMeanSquareError
        rmse = sqrt(sum((r - c) ** 2 for r, c in zip(realLabel, predictedLabel)) / len(realLabel))

        print('MAE: {0} | RMSE: {1} {2}'.format(mae, rmse, mean_squared_error(realLabel, predictedLabel, squared=False)))

        r += realLabel
        p += predictedLabel

    return r, p

if __name__ == "__main__":
    filePath = os.path.join(os.path.curdir,  FILE_TO_LOAD + '.csv')
    labels = ReadCSV(filePath)

    r, p = RegressionError(labels)

    indexes = [i for i in range(len(r))]
    real, = plt.plot(indexes, r, 'ro', label = 'real')
    computed, = plt.plot(indexes, p, 'bo', label = 'computed')
    plt.legend([real, (real, computed)], ["Real", "Computed"])
    plt.show()