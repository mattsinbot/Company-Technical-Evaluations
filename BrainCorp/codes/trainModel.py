import numpy as np
import cv2
import matplotlib.pyplot as plt
from pathlib import Path
from sklearn import svm


# Paths to training related data
PATH2 = "/home/nobug-ros/Desktop/cpp_practice/BrainCorp/"
train_data = PATH2 + 'find_phone/'
patchHeight, patchWidth = 60, 60
clf = svm.SVC(gamma='scale')


def checkOverlap(rectA, rectB):
    overLap = True

    if (rectA[0, 0] > rectB[1, 0]) or (rectB[0, 0] > rectA[1, 0]):
        overLap = False

    if (rectA[0, 1] > rectB[1, 1]) or (rectA[0, 1] > rectB[1, 1]):
        overLap = False

    return overLap


def visualizePatch():
    imgName = train_data + '49.jpg'
    topLeft = [185, 395]
    img = cv2.imread(imgName, cv2.IMREAD_UNCHANGED)
    cv2.rectangle(img, (topLeft[1], topLeft[0]), (topLeft[1] + patchWidth, topLeft[0] + patchHeight), (0, 255, 0), 3)
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    plt.show()


def genNegFeat(showPatch=False):
    # Parameters for HOG descriptor
    winSize, blockSize, blockStride, cellSize, nbins = (32, 32), (16, 16), (8, 8), (8, 8), 9
    hog = cv2.HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins)

    # Initialize containers to hold features and labels
    count = 0
    neg_feature_mat = np.zeros((5184, 1))
    neg_lbl = np.zeros((1, 1))
    negSampImg = 2

    anno_data = open(PATH2 + 'anno.txt', 'r')
    while True:
        line = anno_data.readline()
        if not line:
            break
        val = line.split(",")
        train_img_name = train_data + val[0] + ".jpg"
        config = Path(train_img_name)
        if config.is_file():
            img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
            imgH, imgW = img.shape[0], img.shape[1]
            validNeg = 0
            while validNeg < negSampImg:
                topLeft = [int(np.asscalar(np.random.uniform(0, imgH, 1))), int(np.asscalar(np.random.uniform(0, imgW, 1)))]
                botRight = [topLeft[0]+patchHeight, topLeft[1]+patchWidth]
                negRect = np.array([topLeft, botRight])
                posRect = np.array([[int(val[1]), int(val[2])], [int(val[1])+patchHeight, int(val[2])+patchWidth]])
                if negRect[1, 0] < imgH and negRect[1, 1] < imgW:
                    if not checkOverlap(posRect, negRect):
                        validNeg += 1
                        img_gray = cv2.cvtColor(img[negRect[0, 0]:negRect[1, 0], negRect[0, 1]:negRect[1, 1]], cv2.COLOR_BGR2GRAY)
                        hf = hog.compute(img_gray)
                        if count == 0:
                            neg_feature_mat = hf
                            neg_lbl = np.array(-1)
                        else:
                            neg_feature_mat = np.hstack((neg_feature_mat, hf))
                            neg_lbl = np.hstack((neg_lbl, -1))
                        count += 1
                        # plt.imshow(img_gray, cmap='gray')
                        # plt.show()
    anno_data.close()
    return neg_feature_mat, neg_lbl


def genPosFeat(showPatch=False):
    anno_data = open(PATH2 + 'anno.txt', 'r')
    # Parameters for HOG descriptor
    winSize, blockSize, blockStride, cellSize, nbins = (32, 32), (16, 16), (8, 8), (8, 8), 9
    hog = cv2.HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins)

    # Initialize containers to hold features and labels
    count = 0
    pos_feature_mat = np.zeros((5184, 1))
    pos_lbl = np.zeros((1, 1))

    while True:
        line = anno_data.readline()
        if not line:
            break
        val = line.split(",")
        train_img_name = train_data + val[0] + ".jpg"
        config = Path(train_img_name)
        if config.is_file():
            img = cv2.imread(train_img_name, cv2.IMREAD_UNCHANGED)
            img_gray = cv2.cvtColor(img[int(val[1]):int(val[1])+patchHeight, int(val[2]):int(val[2])+patchWidth], cv2.COLOR_BGR2GRAY)
            # plt.imshow(img_gray, cmap='gray')
            # plt.show()
            hf = hog.compute(img_gray)
            if count == 0:
                pos_feature_mat = hf
                pos_lbl = np.array(1)
            else:
                pos_feature_mat = np.hstack((pos_feature_mat, hf))
                pos_lbl = np.hstack((pos_lbl, 1))
            count += 1
            if showPatch:
                cv2.rectangle(img, (int(val[2]), int(val[1])), (int(val[2])+patchWidth, int(val[1])+patchHeight), (0, 255, 0), 3)
                plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
                plt.show()
    anno_data.close()
    return pos_feature_mat, pos_lbl


def genPosNegFeat():
    featsPos, lblPos = genPosFeat()
    print(featsPos.shape)
    print(lblPos.shape)

    featsNeg, lblNeg = genNegFeat()
    print(featsNeg.shape)
    print(lblNeg.shape)

    featPosNeg = np.hstack((featsPos, featsNeg))
    lblPosNeg = np.hstack((lblPos, lblNeg))
    print(featPosNeg.shape)
    print(lblPosNeg.shape)

    return featPosNeg, lblPosNeg


def trainSVM(feat, lbl):
    clf = svm.SVC(gamma='scale')
    clf.fit(feat, lbl)

    print(clf.classes_)
    print(clf.class_weight_)
    print(clf.predict(feat))
    print(clf.decision_function(feat))
    return clf


def detectPhone(clf):
    winSize, blockSize, blockStride, cellSize, nbins = (32, 32), (16, 16), (8, 8), (8, 8), 9
    hog = cv2.HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins)
    imgName = train_data + 'test.jpg'
    topLeft = [95, 45]
    img = cv2.imread(imgName, cv2.IMREAD_UNCHANGED)
    slidingWinSz = [60, 60]
    stepSize = 5
    scoreList = list()
    topLeftList = list()
    for yv in range(0, img.shape[0]-slidingWinSz[0], stepSize):
        for xv in range(0, img.shape[1]-slidingWinSz[1], stepSize):
            currPatchGray = cv2.cvtColor(img[yv:yv+slidingWinSz[0], xv:xv+slidingWinSz[1]], cv2.COLOR_BGR2GRAY)
            hf = hog.compute(currPatchGray)
            currScore = np.asscalar(clf.decision_function(hf.T))
            if currScore > 0:
                scoreList.append(currScore)
                topLeftList.append([yv, xv])
            # print(clf.predict(hf.T))
            # print(clf.decision_function(hf.T))

            # cv2.rectangle(img, (x, y), (x+slidingWinSz[1], y+slidingWinSz[0]), (0, 255, 0), 3)
            # plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
            # plt.show()
    scoreMax = max(scoreList)
    scoreMaxInd = scoreList.index(scoreMax)
    print(topLeftList[scoreMaxInd])


def test():
    X = np.array([[3, 4], [1, 4], [2, 3], [6, -1], [7, -1], [5, -3]])
    y = np.array([-1, -1, -1, 1, 1, 1])
    # clf = svm.SVC(C=1e5, kernel='linear')
    # clf = svm.SVC(gamma='scale')
    clf.fit(X, y)
    print(clf.class_weight_)
    print(clf.predict(X))
    print(clf.decision_function(X))
    print(clf.classes_)
    # print(clf.)
    # print('w = ', clf.coef_)
    # print('b = ', clf.intercept_)
    # print('Indices of support vectors = ', clf.support_)
    # print('Support vectors = ', clf.support_vectors_)
    # print('Number of support vectors for each class = ', clf.n_support_)
    # print('Coefficients of the support vector in the decision function = ', np.abs(clf.dual_coef_))


if __name__ == "__main__":
    X, y = genPosNegFeat()
    # test()
    clf = trainSVM(X.T, y)
    # visualizePatch()
    detectPhone(clf)
