import socket
from io import BytesIO
from time import time
from threading import Thread,Lock
from os import urandom
import sys
import argparse
import logging

class Server(object):
    def __init__(self,port,file = None):
        self.server_socket =socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind(('',port))
        logging.info(f"server is binded to port {port}")
        self.lock = Lock()
        self.chunk_size = 1024*1024*10
        self.file_size = 1024*1024*100
        self.time_list = []
        
        if file is None:
            self.file = BytesIO()
            self.generate_random_file()
        else:
            self.file = open(file,'rb')
    def generate_random_file(self,block_size = 1024):
        for i in range(self.file_size//block_size):
            self.file.write(urandom(block_size))
    def start(self):
        self.server_socket.listen(5)
        try:
            client_socket, client_addr = self.server_socket.accept()
            Thread(target=self.handler,args=(client_socket)).start()
        except KeyboardInterrupt:
            logging.warning("KeyboardInterrupt recived!")
            if len(self.time_list) > 0:
                logging.info(f"average download time: {sum(self.time_list)/len(self.time_list)} sec")
                
    def handler(self,client_socket):
        client_addr = client_socket.getpeername()
        logging.info(f"{client_addr[0]} begin downloading file")
        btime = time()
        idx=0
        try:
            while True:
                self.lock.acquire()
                self.file.seek(idx*self.chunk_size)
                buffer = self.file.read(self.chunk_size)
                self.lock.release()
                try :
                    if not buffer:
                        break
                    client_socket.send(buffer)
                    idx+=1
                except BrokenPipeError:
                    logging.warning(f"{client_addr[0]} connection broken!")
                    raise BrokenPipeError
                except ConnectionResetError:
                    logging.warning(f"{client_addr[0]} connection reset!")
                    raise ConnectionResetError
        except:
            pass
        else :
            etime = time()
            logging.info(f"{client_addr[0]} download finished.")
            logging.info(f"time used: {round(etime-btime,2)} sec")
            self.time_list.append(etime-btime)
        finally:
            client_socket.close()
            

if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG,
        format='[%(asctime)s][%(levelname)s] - %(message)s',datefmt='%H:%M:%S')
    args = argparse.ArgumentParser()
    args.add_argument("-p","--port",help="Server port.",type=int)
    args.add_argument("-f","--file",help="File to be downloaded.",type=str)
    args = args.parse_args()
    
    port = 54321
    file = None
    if args.port:
        port = args.port
    if args.file:
        file = args.file
    Server(port,file).start()
            
        
            