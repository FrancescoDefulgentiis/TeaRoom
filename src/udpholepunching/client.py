import socket
import time
import select
# Define the target machine's IP address and port
target_ip = "172.20.10.8"  # Replace with the target machine's IP
target_port = 12345  # Replace with the target port number

# Create a UDP socket
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Message to send
message = "172.20.10.2"
message = message.encode()

try:
    # Send the message to the target machine
    udp_socket.sendto(message, (target_ip, target_port))
    print(f"Sent: {message} to {target_ip}:{target_port}")
    data, addr = udp_socket.recvfrom(1024)  # Buffer size is 1024 bytes
    data = data.decode()
    print(f"Received data from {addr[0]}:{addr[1]}: {data}")
    ip= data.split("/")[0]
    port= int(data.split("/")[1])
    while True:
        udp_socket.sendto(f"Hello i'm code {ip}".encode(),(ip,port))
        print(f"Sent: Hello i'm code {ip} to {ip}:{port}")
        readble,_,_=select.select([udp_socket],[],[],1)
        if udp_socket in readble:
            data, addr = udp_socket.recvfrom(1024)
            data = data.decode()
            print(f"Received data from {addr[0]}:{addr[1]}: {data}")
        else:
            print("Timeout")
            break


except Exception as e:
    print(f"Error: {e}")

finally:
    udp_socket.close()