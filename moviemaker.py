import glob
import cv2
import tqdm
from natsort import natsorted

file_list = glob.glob("contour_*.png")
new_file_list = natsorted(file_list)
print(new_file_list)
img_one = cv2.imread(new_file_list[0])
# print(img_one.shape)

fourcc = cv2.VideoWriter_fourcc('m', 'p', '4', 'v')
video = cv2.VideoWriter("contour.mp4", fourcc, 5.0, (img_one.shape[1], img_one.shape[0]))

for filename in tqdm.tqdm(new_file_list):
    img = cv2.imread(filename)
    video.write(img)
video.release()
