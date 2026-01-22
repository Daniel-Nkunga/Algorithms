import cv2

def click_and_crop(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, y)

image = cv2.imread("map.png")
cv2.namedWindow("image")
cv2.setMouseCallback("image", click_and_crop)

while True:
    cv2.imshow("image", image)
    cv2.waitKey(1)
