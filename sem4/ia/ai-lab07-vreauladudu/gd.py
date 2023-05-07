import os
import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model
import random

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
            if len(Y) == 2:
                learntModel = [Y[0] + item1 * Y[1] for item1 in validationInputs[0]]
            else:
                learntModel = [Y[0] + item1 * Y[1] + item2 * Y[2] for item1, item2 in zip(validationInputs[0], validationInputs[1])]
            ax.scatter(validationInputs[0], validationInputs[1], learntModel, label=labels[2], marker='o', color='red')

    ax.legend()
    plt.show()
 
class BGDRegression:
    def __init__(self, learningRate=0.01, noEpochs=100):
        self.noEpochs = noEpochs
        self.learningRate = learningRate
        self.intercept_ = 0.0
        self.coef_ = []

    def fit(self, x, y):
        self.coef_ = [0.0 for _ in range(len(x[0]) + 1)]
        for _ in range(self.noEpochs):
            error = [0.0 for _ in range(len(x[0]) + 1)]
            for i in range(len(x)):
                epsilon = self.compute(x[i]) - y[i]

                for j in range(len(x[0])):
                    error[j] += epsilon * x[i][j]
                error[-1] += epsilon
            
            for j in range(len(x[0])):
                self.coef_[j] = self.coef_[j] - self.learningRate * error[j] / len(x)
            self.coef_[-1] = self.coef_[-1] - self.learningRate * error[-1] / len(x)

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def compute(self, xInput):
        yComputed = self.coef_[-1]
        for i in range(len(xInput)):
            yComputed += self.coef_[i] * xInput[i]
        return yComputed

    def predict(self, xInput):
        return [self.compute(x) for x in xInput]

def iter_minibatches(batchsize, numtraining, X, y):
    batchstartmaker = 0
    while batchstartmaker < numtraining:
        batchrows = range(batchstartmaker, batchstartmaker + batchsize)
        X_batch = X[batchrows.start:batchrows.stop] 
        y_batch = y[batchrows.start:batchrows.stop]
        yield X_batch, y_batch
        batchstartmaker += batchsize

def normalize(listToNormalize: list):
    normalizedList = []
    for list in listToNormalize:
        mean = sum(list) / len(list)
        stdDev = (1 / (len(list) - 1) * sum([(item - mean) ** 2 for item in list])) ** 0.5
        normalizedList.append([(item - mean) / stdDev for item in list])
    return normalizedList

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

    trainInputs[0], trainInputs[1], trainOutput, validationInputs[0], validationInputs[1], validationOutput = \
        normalize([trainInputs[0], trainInputs[1], trainOutput, validationInputs[0], validationInputs[1], validationOutput])
    
    plotData(trainInputs, trainOutput, inputNames, outputName, ["train data", "test data"], validationInputs, validationOutput)

    trainData = []
    for i in range(len(trainInputs[0])):
        trainData.append([trainInputs[0][i], trainInputs[1][i]])
        #trainData.append([trainInputs[0][i]])

    # regressor = linear_model.SGDRegressor(max_iter=100, alpha=0, eta0=0.01, learning_rate='constant')
    # batcherator = iter_minibatches(batchsize=len(trainData), numtraining=len(trainData), X=trainData, y=trainOutput) # batchsize=16 => Mini-Batch GD
    # batches = list(batcherator)
    # noEpochs = 100
    # for _ in range(noEpochs):
    #     random.shuffle(batches)
    #     for X_batch, y_batch in batches:
    #         regressor.partial_fit(X_batch, y_batch)

    regressor = BGDRegression()
    regressor.fit(trainData, trainOutput)

    Y = [regressor.intercept_] # w0
    print(f"w{0}= {Y[0]}")
    for i in range(len(trainData[0])):
        Y.append(regressor.coef_[i]) # wi
        print(f"w{i + 1}= {Y[i + 1]}")
    if len(trainData[0]) == 1:
        print(f"f(x) = {Y[0]} + {Y[1]} * x")
    else:
        print(f"f(x,y) = {Y[0]} + {Y[1]} * x + {Y[2]} * y")

    plotData(trainInputs, trainOutput, inputNames, outputName, ["train data", "test data", "learnt model"], validationInputs, validationOutput, alpha=0.3, Y=Y)

    testData = []
    for i in range(len(validationInputs[0])):
        testData.append([validationInputs[0][i], validationInputs[1][i]])
        #testData.append([validationInputs[0][i]])
    predictedOutputs = regressor.predict(testData)

    plotData(trainInputs, trainOutput, inputNames, outputName, ["train data", "predicted model", "learnt model"], validationInputs, predictedOutputs, alpha=0.3, Y=Y)