
import cv2 
import numpy as np

XTRANSLATE = 3.75
YTRANSLATE = 4.3
height , width = 0,0
def bilinearinterpolation(xbar,ybar,a,b,src_img):
    value1 = (1-a)*(1-b)*(src_img[xbar][ybar])
    value2 = (1-a)*(b)*(src_img[xbar+1][ybar])
    value3 = (a)*(1-b)*(src_img[xbar][ybar+1])
    value4 = (a)*(b)*(src_img[xbar+1][ybar+1])
    resultant = value1+value2+value3+value4
    return resultant

def getpixel (image,xtrans,ytrans) :    
        FloorA,FloorB  = int(xtrans),int(ytrans)
        af = xtrans-FloorA
        bf = ytrans-FloorB
        
        #print(a,b,FloorA,FloorB)
        if (xtrans > 0 and ytrans > 0 ) and (xtrans <= height and ytrans <= width):
            a = bilinearinterpolation(FloorA,FloorB,af,bf,image)
            return a
        else:
            a = 0
            return a
        
img = cv2.imread('test.pgm',0)  
height, width = img.shape
img_new = np.zeros((height,width))
for y in range(height):
    for x in range(width):
        #print(x,y,"\t")
        img_new[x][y] = getpixel(img,x-XTRANSLATE,y-YTRANSLATE)
for y in range(height):
    for x in range(width):
        #print(x,y,"\t")
        img[x][y] =img_new[x][y]
        
cv2.imshow('image', img)  
cv2.waitKey(0)         
cv2.destroyAllWindows()  