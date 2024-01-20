# -*- coding: utf-8 -*-
import  random
import urllib.request
import requests
import json
import re
#定义要爬取的微博大V的微博ID
import requests
import time
from bs4 import BeautifulSoup
# id=(input("1743951792:"))

na='a'
#设置代理IP

iplist=['112.228.161.57:8118','125.126.164.21:34592','122.72.18.35:80','163.125.151.124:9999','114.250.25.19:80']

proxy_addr="125.126.164.21:34592"

# def use_proxy(url,proxy_addr):
#     req=urllib.request.Request(url)
#     req.add_header("User-Agent","Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.221 Safari/537.36 SE 2.X MetaSr 1.0")
#     proxy=urllib.request.ProxyHandler({'http':random.choice(iplist)})
#     opener=urllib.request.build_opener(proxy,urllib.request.HTTPHandler)
#     urllib.request.install_opener(opener)
#     data=urllib.request.urlopen(req).read().decode('utf-8','ignore')
#     return data

def get_text(url):
    data=requests.get(url).text
    soup=BeautifulSoup(data,'html.parser')
    
    with open('test.txt','w') as f:
        f.write(soup.prettify())
    # idx=data.rfind('weibo-text')
    # if(idx==-1):
    #     print('not found')
    # data=data[idx+24:]
    # idx=data.find('</div>')
    # data=data[:idx]

get_text('https://m.weibo.cn/status/4949450945201371')