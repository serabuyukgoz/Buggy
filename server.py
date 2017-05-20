import socket
from rosPublisher import rosPublisher

def javaServer:
	soc = socket.socket()
	host = ""
	port = 2004
	soc.bind((host, port))
	soc.listen(5)
	while True:
		conn, addr = soc.accept()
		print ("Got Connection from", addr)
		msg = conn.recv(1024)
		print(msg)
		rosPublisher(msg)
	
	
if __name__ == '__main__':
	javaServer()


	
	
	
	
		