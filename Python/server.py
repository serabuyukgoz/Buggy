import socket
from rosPublisher import rosPub

start = 0

#open led to show all connections bind
def led():
        global start
        if (start == 0):
                rosPub('led')
        start = 2
        
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
		led()
		msg = conn.recv(1024) #mesages received
		rosPub(msg) #mesage sended to ros publisher
	
if __name__ == '__main__':
	javaServer()

