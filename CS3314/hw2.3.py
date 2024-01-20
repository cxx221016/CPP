import numpy as np
import math
import argparse
array=np.array([[1,0,19],[17,19,0],[4,7,10]])

def GetModInv(array,mod):
    mod=int(mod)
    det=np.linalg.det(array)
    inv_det=det
    det=int(det)%mod
    if(det==0):
        print("No inverse")
    if(math.gcd(det,mod)!=1):
        print("No inverse")
    else:
        for i in range(1,mod):
            if((det*i)%mod==1):
                det=i
                break
        array=np.linalg.inv(array)*inv_det
        array=np.around(array)
        array=array*det
        array=array%mod
        return array
    
def GetModMul(mtx1,mtx2,mod):
    mtx= mtx1@mtx2
    mtx=mtx%mod
    return mtx

def HillEncryptImpl(plaintext,key,mod):
    key=np.array(key)
    plaintext=np.array(plaintext)
    len_key=key.size
    len_plaintext=plaintext.size
    assert (len_key==len_plaintext**2),"Key and plaintext size mismatch"
    key=key.reshape(len_plaintext,len_plaintext)
    plaintext=plaintext.reshape(-1,1)
    ciphertext=GetModMul(key,plaintext,mod)
    return ciphertext

def HillDecryptImpl(ciphertext,key,mod):
    key=np.array(key)
    ciphertext=np.array(ciphertext)
    len_key=key.size
    len_ciphertext=ciphertext.size
    assert (len_key==len_ciphertext**2),"Key and ciphertext size mismatch"
    key=key.reshape(len_ciphertext,len_ciphertext)
    ciphertext=ciphertext.reshape(-1,1)
    key=GetModInv(key,mod)
    plaintext=GetModMul(key,ciphertext,mod)
    return plaintext
    

def HillGetKeyImpl(plaintext,ciphertext,mod):
    plaintext=np.array(plaintext)
    ciphertext=np.array(ciphertext)
    len_plaintext=plaintext.size
    len_ciphertext=ciphertext.size
    assert (len_plaintext==len_ciphertext),"Plaintext and ciphertext size mismatch"
    length=int(math.sqrt(len_plaintext))
    plaintext=plaintext.reshape(length,length)
    plaintext=plaintext.T
    ciphertext=ciphertext.reshape(length,length)
    ciphertext=ciphertext.T
    key=GetModMul(ciphertext,GetModInv(plaintext,mod),mod)
    return key


def printascii(ciphertext,lower=False):
    ciphertext=ciphertext.reshape(-1)
    ciphertext=[int(i) for i in ciphertext]
    if lower:
        ciphertext=[chr(i+ord('a')) for i in ciphertext]
    else: 
        ciphertext=[chr(i+ord('A')) for i in ciphertext]
    ciphertext=''.join(ciphertext)
    print("Ciphertext: ",ciphertext)
    
def input2list(str):
    lists=str.split()
    if len(lists)==1:
        res=[]
        for ch in str:
            if(ch.islower()):
                res.append(int(ord(ch)-ord('a')))
            else:
                res.append(int(ord(ch)-ord('A')))
        return res
    else:
        if lists[0].islower():
            res=[int(ord(i)-ord('a')) for i in lists]
        else:
            res=[int(ord(i)-ord('A')) for i in lists]
        return res
    
def HillEncrypt(plaintext,key,mod):
    size=int(math.sqrt(len(key)))
    assert (len(plaintext)%size==0),"Plaintext size mismatch"
    ciphertext=np.array([])
    for i in range(0,len(plaintext),size):
        tmp=HillEncryptImpl(plaintext[i:i+size],key,mod)
        ciphertext=np.append(ciphertext,tmp)
    #print("Ciphertext: ",ciphertext)
    return ciphertext

def HillDecrypt(ciphertext,key,mod):
    size=int(math.sqrt(len(key)))
    assert (len(ciphertext)%size==0),"Ciphertext size mismatch"
    plaintext=np.array([])
    for i in range(0,len(ciphertext),size):
        tmp=HillDecryptImpl(ciphertext[i:i+size],key,mod)
        plaintext=np.append(plaintext,tmp)
    #print("Plaintext: ",plaintext)
    return plaintext

def HillGetKey(plaintext,ciphertext,mod):
    assert (len(plaintext)==len(ciphertext)),"Plaintext and ciphertext size mismatch"
    totallen=len(plaintext)
    size=int(math.sqrt(len(plaintext)))
    for m in range(2,size+1):
        if totallen%m==0 and m**2<=totallen:
            try:
                key=HillGetKeyImpl(plaintext[0:m**2],ciphertext[0:m**2],mod)
                return key
            except:
                continue
        

if __name__=="__main__":
    args=argparse.ArgumentParser()
    args.add_argument("-E","--encrypt",help="Encrypt",action="store_true")
    args.add_argument("-D","--decrypt",help="Decrypt",action="store_true")
    args.add_argument("-G","--getkey",help="Get key",action="store_true")
    args=args.parse_args()
    assert (args.encrypt or args.decrypt or args.getkey),"Please choose one of the options"
    assert (args.encrypt+args.decrypt+args.getkey==1),"Please choose only one option"
    if(args.encrypt):
        #key: 3 4 6 21 15 14 20 23 5
        key=list(map(int,input("Enter key: ").split()))
        plaintext=input2list(input("Enter plaintext: "))
        mod=26
        ciphertext=HillEncrypt(plaintext,key,mod)
        printascii(ciphertext)
    elif(args.decrypt):
        key=list(map(int,input("Enter key: ").split()))
        ciphertext=input2list(input("Enter ciphertext: "))
        mod=26
        plaintext=HillDecrypt(ciphertext,key,mod)
        printascii(plaintext,True)
    elif(args.getkey):
        # plaintext_lists=input("Enter plaintext: ").split()
        # if plaintext_lists[0].islower():
        #     plaintext=[int(ord(i)-ord('a')) for i in plaintext_lists]
        # else:
        #     plaintext=[int(ord(i)-ord('A')) for i in plaintext_lists]
        # ciphertext_lists=input("Enter ciphertext: ").split()
        # if ciphertext_lists[0].islower():
        #     ciphertext=[int(ord(i)-ord('a')) for i in ciphertext_lists]
        # else:
        #     ciphertext=[int(ord(i)-ord('A')) for i in ciphertext_lists]
        plaintext=input2list(input("Enter plaintext: "))
        ciphertext=input2list(input("Enter ciphertext: "))
        mod=26
        key=HillGetKey(plaintext,ciphertext,mod)
        print("Key: \n",key)
    