import cv2

# img=cv2.imread(r'D:\Download\0001.jpg')
# img2=cv2.imread(r'D:\Download\0002.jpg')
img=cv2.imread(r'res.jpg')
img2=cv2.imread(r'ret.jpg')
print(img.shape)
print(img2.shape)
imgv=cv2.vconcat([img,img2])

# imgh=cv2.hconcat([img,img2])
cv2.imwrite(r'1.jpg',imgv)
# cv2.imwrite(r'2.jpg',imgh)