import matplotlib.pyplot as plt
from pathlib import Path
from sklearn import svm
import numpy as np
import cv2


class phoneFinder(object):
    # Parameters for HOG descriptor as class variables
    winSize, blockSize, blockStride, cellSize, nbins = (32, 32), (16, 16), (8, 8), (8, 8), 9

    # Class constructor
    def __init__(self, dataPath):
        # Paths to training related data
        self._PATH2 = dataPath
        self._featPatchHeight= 60
        self._featPatchWidth = 60
        self._szFeatVec = 5184
        self._hog = cv2.HOGDescriptor(phoneFinder.winSize, phoneFinder.blockSize,
                                phoneFinder.blockStride, phoneFinder.cellSize, phoneFinder.nbins)
        self._clf = svm.SVC(gamma='scale')

    @staticmethod
    def checkOverlap(rectA, rectB):
        overLap = True
        if (rectA[0, 0] > rectB[1, 0]) or (rectB[0, 0] > rectA[1, 0]):
            overLap = False
        if (rectA[0, 1] > rectB[1, 1]) or (rectA[0, 1] > rectB[1, 1]):
            overLap = False
        return overLap

    # Visualize an Image Patch
    def visualizePatch(self):
        imgName = self._PATH2 + '49.jpg'
        topLeft = [185, 395]
        img = cv2.imread(imgName, cv2.IMREAD_UNCHANGED)
        cv2.rectangle(img, (topLeft[1], topLeft[0]),
                      (topLeft[1] + self._featPatchWidth, topLeft[0] + self._featPatchHeight), (0, 255, 0), 3)
        plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        plt.show()

    # Generate feature vector from Negative Examples
    def genNegFeat(self, negSampImg=2, showPatch=False):
        # Initialize containers to hold features and labels
        count = 0
        neg_feature_mat = np.zeros((self._szFeatVec, 1))
        neg_lbl = np.zeros((1, 1))
        anno_data = open(self._PATH2 + 'anno.txt', 'r')
        while True:
            line = anno_data.readline()
            if not line:
                break
            val = line.split(",")
            train_img_name = self._PATH2 + val[0] + ".jpg"
            config = Path(train_img_name)
            if config.is_file():
                img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
                imgH, imgW = img.shape[0], img.shape[1]
                validNeg = 0
                while validNeg < negSampImg:
                    topLeft = [int(np.asscalar(np.random.uniform(0, imgH, 1))), int(np.asscalar(np.random.uniform(0, imgW, 1)))]
                    botRight = [topLeft[0]+self._featPatchHeight, topLeft[1]+self._featPatchWidth]
                    negRect = np.array([topLeft, botRight])
                    posRect = np.array([[int(val[1]), int(val[2])], [int(val[1])+self._featPatchHeight, int(val[2])+self._featPatchWidth]])
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
        print(self._PATH2)
        anno_data = open(self._PATH2 + 'anno.txt', 'r')
        # Initialize containers to hold features and labels
        count = 0
        pos_feature_mat = np.zeros((self._szFeatVec, 1))
        pos_lbl = np.zeros((1, 1))

        while True:
            line = anno_data.readline()
            if not line:
                break
            val = line.split(",")
            train_img_name = self._PATH2 + val[0] + ".jpg"
            config = Path(train_img_name)
            if config.is_file():
                img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
                img_gray = cv2.cvtColor(img[int(val[1]):int(val[1])+self._featPatchHeight,
                                        int(val[2]):int(val[2])+self._featPatchWidth], cv2.COLOR_BGR2GRAY)
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
        # Generate Features from Negative Examples
        featsNeg, lblNeg = self.genNegFeat()
        return np.hstack((featsPos, featsNeg)), np.hstack((lblPos, lblNeg))

    # Train SVM Model
    def trainSVM(self):
        featureX, labelY = self.genPosNegFeat()
        self._clf.fit(featureX.T, labelY)

    # Detect Phone
    def detectPhone(self, imgPath):
        img = cv2.imread(imgPath, cv2.IMREAD_UNCHANGED)
        slidingWinSz = [60, 60]
        stepSize = 4
        scoreList = list()
        topLeftList = list()
        for yv in range(0, img.shape[0]-slidingWinSz[0], stepSize):
            for xv in range(0, img.shape[1]-slidingWinSz[1], stepSize):
                currPatchGray = cv2.cvtColor(img[yv:yv+slidingWinSz[0], xv:xv+slidingWinSz[1]], cv2.COLOR_BGR2GRAY)
                hf = self._hog.compute(currPatchGray)
                currScore = np.asscalar(self._clf.decision_function(hf.T))
                if currScore > 0:
                    scoreList.append(currScore)
                    topLeftList.append([yv, xv])
        scoreMax = max(scoreList)
        scoreMaxInd = scoreList.index(scoreMax)
        print(topLeftList[scoreMaxInd])


if __name__ == "__main__":
    trainDataPath = "/home/nobug-ros/Desktop/cpp_practice/BrainCorp/find_phone/"
    testDataPath = "/home/nobug-ros/Desktop/cpp_practice/BrainCorp/find_phone/15.jpg"

    pF = phoneFinder(trainDataPath)
    pF.trainSVM()
    pF.detectPhone(testDataPath)
