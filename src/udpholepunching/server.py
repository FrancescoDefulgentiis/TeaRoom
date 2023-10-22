import socket
list_ip =[]



# Define the IP address and port to listen on
listen_ip = "0.0.0.0"  # Listen on all available network interfaces
listen_port = 12345  # Choose an available port

# Create a UDP socket
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the specified IP address and port
udp_socket.bind((listen_ip, listen_port))
# Print my ip address and port number
myip=udp_socket.getsockname()[0]
myport=udp_socket.getsockname()[1]
print(f"My ip address is: {myip}")
print(f"My port number is: {myport}")
print(f"Listening on {listen_ip}:{listen_port}")

def find_couple(list_item):
    for j,element in enumerate(list_item):
        for i,element2 in enumerate(list_item):
            
            if element[0]==element2[2] and element[2]==element2[0] and i!=j:
                return element[0],element[1],element2[0],element2[1],min(i,j),max(i,j)

while True:
    # Receive data from the socket
    data, addr = udp_socket.recvfrom(1024)  # Buffer size is 1024 bytes
    data = data.decode()
    list_ip.append([addr[0],addr[1],data])
    print(list_ip)
    if len(list_ip)!=1:
        couples=find_couple(list_ip)
        udp_socket.sendto(f"{couples[0]}/{couples[1]}".encode(), (addr[0], addr[1]))
        udp_socket.sendto(f"{couples[2]}/{couples[3]}".encode(), (couples[0], couples[1]))
        list_ip.pop(couples[4])
        list_ip.pop(couples[5-1])
        print(f"Sent: {couples[0]}/{couples[1]} to {addr[0]}:{addr[1]}")
        print(f"Sent: {couples[2]}/{couples[3]} to {couples[0]}:{couples[1]}")