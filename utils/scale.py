import cv2
import os
import math
import logging


def getsize(file_path):
    size=os.path.getsize(file_path)
    return size

def size2str(size):
    size=int(size)
    res=[]
    lists=['B ','KB ','MB ','GB ','TB ']
    idx=0
    while size>=1024 :
        res.append(size%1024)
        size=size//1024
        res.append(lists[idx])
        idx+=1
    res.append(size)
    res.append(lists[idx])
    for i in range(len(res)):
        res[i]=str(res[i])
    res= ''.join(res)
    tmplist=res.split(' ')
    tmplist.reverse()
    res=' '.join(tmplist)
    
    return res
        
        

def scale(goal_size,file_path,new_file_path=None):
    if new_file_path==None:
        strs=file_path.split('.')
        strs[-2]=strs[-2]+'.scale'
        new_file_path='.'.join(strs)
    cv2.imwrite(new_file_path,cv2.imread(file_path))
    size=getsize(new_file_path)  
    img=cv2.imread(new_file_path)
    while size>goal_size:
        scale=math.sqrt((goal_size-1024)/size)
        logging.info(f'size: {size2str(size)}, goal_size: {size2str(goal_size)}, scale: {scale}')
        img=cv2.resize(img,(int(img.shape[1]*scale),int(img.shape[0]*scale)),interpolation=cv2.INTER_AREA)
        cv2.imwrite(new_file_path,img)
        size=getsize(new_file_path)
        #img=cv2.imread(new_file_path)
            

logging.basicConfig(level=logging.DEBUG,
        format='[%(asctime)s][%(levelname)s] - %(message)s',datefmt='%H:%M:%S')
scale(600*1024,r'0001.jpg')
