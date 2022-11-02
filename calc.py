import cv2 as cv
import os
import math

li = []


def rad(x):
    return x * (math.pi / 180)


def click_event(event, x, y, flag, params):
    # checking for left mouse clicks
    if event == cv.EVENT_LBUTTONDOWN:
        print(x, ' ', y)
        li.append(f'{x} {y}')
        return [x, y]


def get_file_list():
    files = os.listdir("./single_picture_videos")
    return files


def run_basic():
    file_list = get_file_list()

    for i in range(len(file_list)):
        print(file_list[i])
        li.append(str("./single_picture_videos/" + file_list[i]))
        img = cv.imread("./single_picture_videos/" + file_list[i])
        cv.namedWindow("image")
        cv.imshow("image", img)
        cv.setMouseCallback('image', click_event)
        cv.waitKey(0)

    cv.destroyAllWindows()
    o = open("py_results/coords.txt", "w")
    res_string = ""
    for i in range(len(li)):
        res_string += li[i] + "\n"
    o.write(res_string)
    o.close()


def run_specific(file):
    img = cv.imread("./single_picture_videos/" + file)
    cv.namedWindow("image")
    cv.imshow("image", img)
    cv.setMouseCallback('image', click_event)
    cv.waitKey(0)
    cv.destroyAllWindows()


def get_real_distance():
    file_list = get_file_list()
    img = cv.imread("./single_picture_videos/" + file_list[-1])
    cv.namedWindow("image")
    cv.imshow("image", img)
    cv.setMouseCallback("image", click_event)
    cv.waitKey(0)
    cv.destroyAllWindows()
    x1 = int(li[0].split(" ")[0])
    y1 = int(li[0].split(" ")[1])
    x2 = int(li[1].split(" ")[0])
    y2 = int(li[1].split(" ")[1])
    pixel_d = math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)  # in pixel
    real_d = 20  # cm
    scale = pixel_d / real_d  # distance in pixel per centimeter
    print(scale)
    o = open("py_results/scale_in_pixel_per_centimeter.txt", "w")
    o.write(str(scale))
    o.close()


run_specific("PA260011027.png")
