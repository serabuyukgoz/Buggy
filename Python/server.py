import socket
from rosPublisher import rosPub

# this function is listening java socket
# when a message received send that data to ros publisher
def javaServer():

        soc = socket.socket() #defining java socket
	host = ""
	port = 2004
	soc.bind((host, port)) #defining IP Adrress and port
	soc.listen(5) #wait for client
	while True:
		conn, addr = soc.accept()
		msg = conn.recv(1024) #mesages received
		rosPub(msg) #mesage sended to ros publisher
	
if __name__ == '__main__':
	javaServer()

