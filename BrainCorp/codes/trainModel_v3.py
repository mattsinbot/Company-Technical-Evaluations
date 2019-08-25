import matplotlib.pyplot as plt
from pathlib import Path
from sklearn import svm
import numpy as np
import cv2
import pickle

class phoneFinder(object):
    # Parameters for HOG descriptor as class variables
    winSize, blockSize, blockStride, cellSize, nbins = (32, 32), (16, 16), (8, 8), (8, 8), 9

    # Class constructor
    def __init__(self, dataPath):
        # Paths to training related data
        self._PATH2 = dataPath
        self._patchHalfHeight = 32
        self._patchHalfWidth = 32
        self._slidingWinSz = [2*self._patchHalfHeight, 2*self._patchHalfWidth]
        self._slidingStep = 8
        self._hog = cv2.HOGDescriptor(phoneFinder.winSize, phoneFinder.blockSize,
                                phoneFinder.blockStride, phoneFinder.cellSize, phoneFinder.nbins)
        self._clf = svm.SVC(gamma='scale')
        self._labelFileName = "labels.txt"
        self._annoFileName = "anno.txt"
        self._modelParamFileName ='finalized_model.sav'

    @staticmethod
    def checkOverlap(rectA, rectB):
        overLap = True
        if (rectA[0, 0] > rectB[1, 0]) or (rectB[0, 0] > rectA[1, 0]):
            overLap = False
        if (rectA[0, 1] > rectB[1, 1]) or (rectA[0, 1] > rectB[1, 1]):
            overLap = False
        return overLap

    # Generate anno.txt
    def genAnnoFile(self, showPatch = False):
        annoFileHandle = open(trainDataPath + self._annoFileName, 'w')
        labelData = open(trainDataPath + self._labelFileName, 'r')
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
            train_img_name = trainDataPath + val[0]
            config = Path(train_img_name)
            if config.is_file():
                img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
                imgH, imgW = img.shape[0], img.shape[1]
                centerPixelX = int(float(val[1]) * img.shape[1])
                centerPixelY = int(float(val[2]) * img.shape[0])
                topLeftPxl = [centerPixelY - self._patchHalfHeight, centerPixelX - self._patchHalfWidth]
                bottomRightPxl = [centerPixelY + self._patchHalfHeight, centerPixelX + self._patchHalfWidth]
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
                # posPatch = cv2.resize(posPatch, (2 * self._patchHalfHeight, 2 * self._patchHalfWidth))
                if showPatch:
                    plt.imshow(cv2.cvtColor(posPatch, cv2.COLOR_BGR2RGB))
                    plt.show()

    # Generate feature vector from Negative Examples
    def genNegFeat(self, negSampImg=2, showPatch=False):
        # Initialize containers to hold features and labels
        count = 0
        anno_data = open(self._PATH2 + self._annoFileName, 'r')
        while True:
            line = anno_data.readline()
            if not line:
                break
            val = line.split(",")
            train_img_name = self._PATH2 + val[0]
            config = Path(train_img_name)
            if config.is_file():
                img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
                imgH, imgW = img.shape[0], img.shape[1]
                validNeg = 0
                while validNeg < negSampImg:
                    topLeft = [int(np.asscalar(np.random.uniform(0, imgH, 1))), int(np.asscalar(np.random.uniform(0, imgW, 1)))]
                    botRight = [topLeft[0]+2*self._patchHalfHeight, topLeft[1]+2*self._patchHalfWidth]
                    negRect = np.array([topLeft, botRight])
                    posRect = np.array([[int(val[1]), int(val[2])], [int(val[3]), int(val[4])]])
                    if negRect[1, 0] < imgH and negRect[1, 1] < imgW:
                        if not self.checkOverlap(posRect, negRect):
                            validNeg += 1
                            img_gray = cv2.cvtColor(img[negRect[0, 0]:negRect[1, 0], negRect[0, 1]:negRect[1, 1]], cv2.COLOR_BGR2GRAY)
                            hf = self._hog.compute(img_gray)
                            if count == 0:
                                neg_feature_mat = hf
                                neg_lbl = np.array(-1)
                            else:
                                neg_feature_mat = np.hstack((neg_feature_mat, hf))
                                neg_lbl = np.hstack((neg_lbl, -1))
                            count += 1
                            if showPatch:
                                plt.imshow(img_gray, cmap='gray')
                                plt.show()
        anno_data.close()
        return neg_feature_mat, neg_lbl

    # Generate feature vector from Positive Examples
    def genPosFeat(self, showPatch=False):
        anno_data = open(self._PATH2 + self._annoFileName, 'r')
        # Initialize containers to hold features and labels
        count = 0
        while True:
            line = anno_data.readline()
            if not line:
                break
            val = line.split(",")
            # train_img_name = self._PATH2 + val[0] + ".jpg"
            train_img_name = self._PATH2 + val[0]
            config = Path(train_img_name)
            if config.is_file():
                img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
                img_gray = cv2.cvtColor(img[int(val[1]):int(val[3]), int(val[2]):int(val[4])], cv2.COLOR_BGR2GRAY)
                if img_gray.shape[0] != 2*self._patchHalfHeight or img_gray.shape[1] != 2*self._patchHalfWidth:
                    img_gray = cv2.resize(img_gray, (2*self._patchHalfHeight, 2*self._patchHalfWidth))
                hf = self._hog.compute(img_gray)
                if count == 0:
                    pos_feature_mat = hf
                    pos_lbl = np.array(1)
                else:
                    pos_feature_mat = np.hstack((pos_feature_mat, hf))
                    pos_lbl = np.hstack((pos_lbl, 1))
                count += 1
                if showPatch:
                    cv2.rectangle(img, (int(val[2]), int(val[1])),
                                  (int(val[2])+self._featPatchWidth, int(val[1])+self._featPatchHeight), (0, 255, 0), 3)
                    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
                    plt.show()
        anno_data.close()
        return pos_feature_mat, pos_lbl

    # Generate Complete Features and Labels
    def genPosNegFeat(self):
        # Generate Features from Positive Examples
        featsPos, lblPos = self.genPosFeat()
        print(featsPos.shape)
        # Generate Features from Negative Examples
        featsNeg, lblNeg = self.genNegFeat()
        print(featsNeg.shape)
        return np.hstack((featsPos, featsNeg)), np.hstack((lblPos, lblNeg))

    # Train SVM Model
    def trainSVM(self):
        featureX, labelY = self.genPosNegFeat()
        self._clf.fit(featureX.T, labelY)
        pickle.dump(self._clf, open(self._modelParamFileName, 'wb'))

    # Detect Phone
    def detectPhone(self, imgPath, showDetect=True):
        loadedModel = pickle.load(open(self._modelParamFileName, 'rb'))
        img = cv2.imread(imgPath, cv2.IMREAD_UNCHANGED)
        imgH, imgW = img.shape[0], img.shape[1]
        # stepSize = 8
        scoreList = list()
        topLeftList = list()
        for yv in range(0, img.shape[0]-self._slidingWinSz[0], self._slidingStep):
            for xv in range(0, img.shape[1]-self._slidingWinSz[1], self._slidingStep):
                currPatchGray = cv2.cvtColor(img[yv:yv+self._slidingWinSz[0], xv:xv+self._slidingWinSz[1]], cv2.COLOR_BGR2GRAY)
                if self._slidingWinSz[0] != 2*self._patchHalfHeight or self._slidingWinSz[1] != 2*self._patchHalfWidth:
                    currPatchGray = cv2.resize(currPatchGray, (2*self._patchHalfHeight, 2*self._patchHalfWidth))
                hf = self._hog.compute(currPatchGray)
                currScore = np.asscalar(loadedModel.decision_function(hf.T))
                if currScore > 0:
                    scoreList.append(currScore)
                    topLeftList.append([yv, xv])
        scoreMax = max(scoreList)
        scoreMaxInd = scoreList.index(scoreMax)
        centerY, centerX = (topLeftList[scoreMaxInd][0] + self._slidingWinSz[0]/2)/imgH, \
                           (topLeftList[scoreMaxInd][1] + self._slidingWinSz[1]/2)/imgW
        if showDetect:
            # cv2.rectangle(img, (x, y), (x + slidingWinSz[1], y + slidingWinSz[0]), (0, 255, 0), 3)
            cv2.rectangle(img, (topLeftList[scoreMaxInd][1], topLeftList[scoreMaxInd][0]),
                          (topLeftList[scoreMaxInd][1] + self._slidingWinSz[1], topLeftList[scoreMaxInd][0] + self._slidingWinSz[0]),
                          (0, 255, 0), 3)
            plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
            plt.show()
        return centerY, centerX


if __name__ == "__main__":
    trainDataPath = "/home/nobug-ros/Desktop/cpp_practice/BrainCorp/find_phone/"
    testDataPath = "/home/nobug-ros/Desktop/cpp_practice/BrainCorp/find_phone/"
    testFile = "testImages.txt"

    pF = phoneFinder(trainDataPath)
    pF.genAnnoFile()
    pF.trainSVM()

    # Detect images
    with open(testDataPath+testFile, 'r') as testData:
        dataList = testData.readlines()
        for dataTest in dataList:
            dataTest = dataTest.split()
            print('Detecting phone in file: ' + dataTest[0])
            cX, cY = pF.detectPhone(testDataPath + dataTest[0])
            print('Phone detected: x = {}, y = {}'.format(cX, cY))
