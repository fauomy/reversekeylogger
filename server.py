import socket

# next create a socket object
s = socket.socket()
ip = "192.168.1.7"  # change the IP
port = 1234  # change the port

s.bind((ip, port))
s.listen(5)

print("socket created and is listening")

c, addr = s.accept()
print('Got connection from', addr)

while True:
    received = c.recv(1024).decode(errors='ignore')
    decrypted = "".join([chr(ord(i) - 2) for i in received])
    print(decrypted)
