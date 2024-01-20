import  socket
from io import BytesIO
from time import time
import sys
import argparse
import logging


class Client(object):
    def __init__(self,addr,file_path = None):
        self.client_socket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        if file_path:
            self.f = open(file_path,'wb')
        else:
            self.f = BytesIO()
        self.client_socket.connect(addr)
        self.chunk_size = 1024*1024*10
    def download(self):
        btime = time()
        while True:
            buffer = self.client_socket.recv(self.chunk_size)
            if not buffer:
                break
            self.f.write(buffer)
        etime = time()
        logging.info(f"time used: {round(etime-btime,2)} sec")
    def close(self):
        self.client_socket.close()
        self.f.close()
        
if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG,
        format='[%(asctime)s][%(levelname)s] - %(message)s',datefmt='%H:%M:%S')
    args = argparse.ArgumentParser()
    args.add_argument("-s","--server",help="IP address of the server.",type=str)
    args.add_argument("-p","--port",help="Server port.",type=int)
    args.add_argument("-o","--output_path",help="Output path.",type=str)
    args = args.parse_args()
    ip = '127.0.0.1'
    port = 54321
    path = None
    if args.server:
        ip = args.server
    if args.port:
        port = args.port
    if args.output_path:
        path = args.output_path
    try:
        Client((ip, port),path).download()
    except:
        logging.warning("download failed!")
    
        
    
    
    