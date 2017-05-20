import socket

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
