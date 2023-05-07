import os
import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model

FILE_TO_LOAD = "v2_world-happiness-report-2017"

def ReadCSV(FileName: str, inputVariablesName: list, outputVariableName: str) -> list:
    data = []
    dataNames = []
    inputs = []
    output = []
    with open(FileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count != 0:
                data.append(row)
            else:
                dataNames = row
            line_count += 1

    for inputVariableName in inputVariablesName:
        variableIndex = dataNames.index(inputVariableName)
        inputs.append([float(data[i][variableIndex]) for i in range(len(data))])

    variableIndex = dataNames.index(outputVariableName)
    output = [float(data[i][variableIndex]) for i in range(len(data))]

    return inputs, output

def plotDataHistogramInputs(inputs: list, inputVariablesName: list):
    bins = np.linspace(0, 2, 50)

    plt.hist(inputs[0], bins, alpha=0.5, label=inputVariablesName[0])
    plt.hist(inputs[1], bins, alpha=0.5, label=inputVariablesName[1])
    plt.legend(loc='upper right')
    plt.show()

def plotDataHistogramOutput(output: list, outputVariableName: str):
    bins = np.linspace(2, 8, 50)

    plt.hist(output, bins, alpha=0.5, label=outputVariableName)
    plt.legend(loc='upper right')
    plt.show()

def plotData(inputs: list, output: list, inputVariablesName: list, outputVariableName: str, labels: list, validationInputs = None, validationOutput = None, alpha=1, Y: list = None):
    ax = plt.axes(projection ='3d')
    ax.set_xlabel(inputVariablesName[0])
    ax.set_ylabel(inputVariablesName[1])
    ax.set_zlabel(outputVariableName)

    ax.scatter(inputs[0], inputs[1], output, label=labels[0], marker='o', color='green', alpha=alpha)

    if validationInputs:
        ax.scatter(validationInputs[0], validationInputs[1], validationOutput, label=labels[1], marker='^', color='blue')
        if Y is not None:
            learntModel = [Y[0] + item1 * Y[1] + item2 * Y[2] for item1, item2 in zip(validationInputs[0], validationInputs[1])]
            ax.scatter(validationInputs[0], validationInputs[1], learntModel, label=labels[2], marker='o', color='red')

    ax.legend()
    plt.show()

if __name__ == "__main__":
    filePath = os.path.join(os.path.curdir,  'data\\' + FILE_TO_LOAD + '.csv')
    inputNames = ['Economy..GDP.per.Capita.', 'Freedom']
    outputName = 'Happiness.Score'
    inputs, output = ReadCSV(filePath, inputNames, outputName)

    plotDataHistogramInputs(inputs, inputNames)
    plotDataHistogramOutput(output, outputName)

    plotData(inputs, output, inputNames, outputName, ["train data"])

    np.random.seed(5)
    indexes = [i for i in range(len(inputs[0]))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs[0])), replace=False)
    validationSample = [i for i in indexes if not i in trainSample]

    trainInputs = [[inputs[0][i] for i in trainSample], [inputs[1][i] for i in trainSample]]
    trainOutput = [output[i] for i in trainSample]

    validationInputs = [[inputs[0][i] for i in validationSample], [inputs[1][i] for i in validationSample]]
    validationOutput = [output[i] for i in validationSample]

    plotData(trainInputs, trainOutput, inputNames, outputName, ["train data", "test data"], validationInputs, validationOutput)

    regressor = linear_model.LinearRegression()
    trainData = []
    for i in range(len(trainInputs[0])):
        trainData.append([trainInputs[0][i], trainInputs[1][i]])
    regressor.fit(trainData, trainOutput)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
    print(f"w0= {w0}")
    print(f"w1= {w1}")
    print(f"w2= {w2}")
    print(f"f(x,y) = {w0} + {w1} * x + {w2} * y")

    plotData(trainInputs, trainOutput, inputNames, outputName, ["train data", "test data", "learnt model"], validationInputs, validationOutput, alpha=0.3, Y=[w0, w1, w2])

    testData = []
    for i in range(len(validationInputs[0])):
        testData.append([validationInputs[0][i], validationInputs[1][i]])
    predictedOutputs = regressor.predict(testData)

    plotData(trainInputs, trainOutput, inputNames, outputName, ["train data", "predicted model", "learnt model"], validationInputs, predictedOutputs, alpha=0.3, Y=[w0, w1, w2])