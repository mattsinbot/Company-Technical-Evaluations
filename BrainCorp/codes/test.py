import matplotlib.pyplot as plt
from pathlib import Path
from sklearn import svm
import numpy as np
import cv2

trainDataPath = "/home/nobug-ros/Desktop/cpp_practice/BrainCorp/find_phone/"
# labelFileName = "labelsTest.txt"
labelFileName = "labels.txt"
annoFileName = "annoTest.txt"

annoFileHandle = open(trainDataPath+annoFileName, 'w')
labelData = open(trainDataPath+labelFileName, 'r')

showPatch = False
patchHalfHeight, patchHalfWidth = 32, 32
countLine = 0
while True:
    line = labelData.readline()
    if not line:
        break
    elif countLine > 0:
        annoFileHandle.write("\n")
        countLine += 1
    else:
        countLine += 1
    val = line.split(" ")
    train_img_name = trainDataPath+val[0]
    config = Path(train_img_name)
    if config.is_file():
        img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
        imgH, imgW = img.shape[0], img.shape[1]
        centerPixelX = int(float(val[1])*img.shape[1])
        centerPixelY = int(float(val[2])*img.shape[0])
        topLeftPxl = [centerPixelY-patchHalfHeight, centerPixelX-patchHalfWidth]
        bottomRightPxl = [centerPixelY+patchHalfHeight, centerPixelX+patchHalfWidth]
        if topLeftPxl[0] < 0:
            topLeftPxl[0] = 0
        if topLeftPxl[1] < 0:
            topLeftPxl[1] = 0
        if bottomRightPxl[0] > imgH:
            bottomRightPxl[0] = imgH
        if bottomRightPxl[1] > imgW:
            bottomRightPxl[1] = imgW
        annoFileHandle.write(val[0] + "," + str(topLeftPxl[0]) + "," + str(topLeftPxl[1])
                             + "," + str(bottomRightPxl[0]) + "," + str(bottomRightPxl[1]))
        posPatch = img[topLeftPxl[0]:bottomRightPxl[0], topLeftPxl[1]:bottomRightPxl[1]]
        posPatch = cv2.resize(posPatch, (2*patchHalfHeight, 2*patchHalfWidth))
        if showPatch:
            plt.imshow(cv2.cvtColor(posPatch, cv2.COLOR_BGR2RGB))
            plt.show()
