import cv2
import numpy as np

#Read image
image = cv2.imread("../assets/putin.jpg")

#create a copy of the image to work on
result = np.copy(image)

#Original x-axis values
originalValues = np.array([0, 50, 100, 150, 200, 255])
#changes Y-axis values for red and blue channel
redValues = np.array([0, 20, 40, 75, 150, 255])
blueValues = np.array([0, 80, 150, 190, 220, 255])

#create lookup table for red channel
allValues = np.arange(0, 256)
redLookupTable = np.interp(allValues, originalValues, redValues)

#create lookup table for blue channel
blueLookupTable = np.interp(allValues, originalValues, blueValues)

#split into channels
B, G, R = cv2.split(result)

#apply mapping to red channel
R = cv2.LUT(R, redLookupTable)
R = np.uint8(R)

#apply mapping to blue channel
B = cv2.LUT(B, blueLookupTable)
B = np.uint8(B)

#mege the channels
result = cv2.merge([B, G, R])

#create windows to display images
cv2.namedWindow("image", cv2.WINDOW_NORMAL)
cv2.namedWindow("result", cv2.WINDOW_NORMAL)

#display images
cv2.imshow("image", image)
cv2.imshow("result", result)

#press esc to exit the program
cv2.waitKey(0)

#close all the opened windows
cv2.destroyAllWindows()