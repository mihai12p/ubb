import os
import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model, metrics
from math import exp

FILE_TO_LOAD = "iris"

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
    output = [str(data[i][variableIndex]) for i in range(len(data))]

    return inputs, output

def plotData(inputs: list, inputVariablesName: list, output: list):
    noData = len(inputs[0])
    _, ax = plt.subplots(1, 4, figsize=(4 * 4, 4))
    for label in set(output):
        x = [inputs[0][i] for i in range(noData) if output[i] == label]
        y = [inputs[1][i] for i in range(noData) if output[i] == label]
        z = [inputs[2][i] for i in range(noData) if output[i] == label]
        w = [inputs[3][i] for i in range(noData) if output[i] == label]
        ax[0].scatter(x, y, label=label)
        ax[1].scatter(x, z, label=label)
        ax[2].scatter(x, w, label=label)
        ax[3].scatter(y, z, label=label)

    for i in range(len(inputs)):
        ax[i].legend()

    plt.show()

    _, ax = plt.subplots(2, 2, figsize=(8, 8))
    k, j = 0, 0
    for i in range(len(inputs)):
        ax[k, j].hist(inputs[i], 10, label=inputVariablesName[i])
        ax[k, j].legend()
        j += 1
        if j == 2:
            j = 0
            k += 1

    plt.show()

def plotPredictions(inputs: list, output: list, computedOutputs):
    ax = plt.axes(projection ='3d')
    noData = len(inputs[0])
    for crtLabel in set(output):
        x = [inputs[0][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] == crtLabel]
        y = [inputs[1][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] == crtLabel]
        z = [inputs[2][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] == crtLabel]
        w = [inputs[3][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] == crtLabel]
        ax.scatter(x, y, z, label = str(crtLabel) + ' (correct)')

        x = [inputs[0][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] != crtLabel]
        y = [inputs[1][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] != crtLabel]
        z = [inputs[2][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] != crtLabel]
        w = [inputs[3][i] for i in range(noData) if output[i] == crtLabel and computedOutputs[i] != crtLabel]
        ax.scatter(x, y, z, label = str(crtLabel) + ' (incorrect)')

    ax.set_xlabel(inputNames[0])
    ax.set_ylabel(inputNames[1])
    ax.set_zlabel(inputNames[2])
    ax.legend()
    plt.show()

class LogisticRegression:
    def __init__(self, learningRate=0.001, noEpochs=1000):
        self.noEpochs = noEpochs
        self.learningRate = learningRate
        self.intercept_ = 0.0
        self.coef_ = []

    @staticmethod
    def sigmoid(x):
        return 1 / (1 + exp(-x))

    def fit(self, x, y):
        self.coef_ = [0.0 for _ in range(len(x[0]) + 1)]
        for _ in range(self.noEpochs):
            for i in range(len(x)):
                epsilon = self.sigmoid(self.compute(x[i], self.coef_)) - y[i]
                for j in range(len(x[0])):
                    self.coef_[j] = self.coef_[j] - self.learningRate * epsilon * x[i][j]
                self.coef_[-1] = self.coef_[-1] - self.learningRate * epsilon

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def compute(self, xInput, coef):
        yComputed = coef[-1]
        for i in range(len(xInput)):
            yComputed += coef[i] * xInput[i]
        return yComputed

    def predictOneSample(self, sampleFeatures):
        threshold = 0.5
        coefficients = [self.intercept_] + [c for c in self.coef_]
        computedFloatValue = self.compute(sampleFeatures, coefficients)
        computedLabel = 0 if self.sigmoid(computedFloatValue) < threshold else 1 
        return computedLabel

    def predict(self, xInput):
        return [self.predictOneSample(x) for x in xInput]

if __name__ == "__main__":
    filePath = os.path.join(os.path.curdir,  'data\\' + FILE_TO_LOAD + '.csv')
    inputNames = ['sepalLength', 'sepalWidth', 'petalLength', 'petalWidth']
    outputName = 'species'
    inputs, output = ReadCSV(filePath, inputNames, outputName)

    plotData(inputs, inputNames, output)

    np.random.seed(5)
    indexes = [i for i in range(len(inputs[0]))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs[0])), replace=False)
    validationSample = [i for i in indexes if not i in trainSample]

    trainInputs = [[inputs[0][i] for i in trainSample], [inputs[1][i] for i in trainSample], [inputs[2][i] for i in trainSample], [inputs[3][i] for i in trainSample]]
    trainOutput = [output[i] for i in trainSample]

    validationInputs = [[inputs[0][i] for i in validationSample], [inputs[1][i] for i in validationSample], [inputs[2][i] for i in validationSample], [inputs[3][i] for i in validationSample]]
    validationOutput = [output[i] for i in validationSample]

    trainData = []
    for i in range(len(trainInputs[0])):
        trainData.append([trainInputs[0][i], trainInputs[1][i], trainInputs[2][i], trainInputs[3][i]])

    testData = []
    for i in range(len(validationInputs[0])):
        testData.append([validationInputs[0][i], validationInputs[1][i], validationInputs[2][i], validationInputs[3][i]])

    classifier = linear_model.LogisticRegression()
    classifier.fit(trainData, trainOutput)
    w0, w1, w2, w3, w4 = classifier.intercept_[0], classifier.coef_[0][0], classifier.coef_[0][1], classifier.coef_[0][2], classifier.coef_[0][3]
    print('learnt model: f(x, y, z, t) = ', w0, ' + ', w1, '* x + ', w2, '* y +',  w3, '* z +',  w4, '* t')

    computedTestOutputs = classifier.predict(testData)
    confusionMatrix = metrics.confusion_matrix(validationOutput, computedTestOutputs)
    print(confusionMatrix)
    total = sum(confusionMatrix[i][j] for i in range(len(confusionMatrix[0])) for j in range(len(confusionMatrix[0])))
    TP = sum(confusionMatrix[i][i] for i in range(len(confusionMatrix[0])))
    accuracy = TP / total
    print("error:", 1 - accuracy)
    print("accuracy:", accuracy)

    plotPredictions(validationInputs, validationOutput, computedTestOutputs)