import socket
import struct
import sys

MCAST_GRP = '224.0.0.22'
MCAST_PORT = 4840
MCAST_IFACE = '192.168.1.31' # TODO parametrize to use own interface IP
IS_ALL_GROUPS = True

print("available interfaces:")
print(socket.gethostbyname_ex(socket.gethostname()))

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
if IS_ALL_GROUPS:
    # on this port, receives ALL multicast groups
    sock.bind(('', MCAST_PORT))
else:
    # on this port, listen ONLY to MCAST_GRP
    sock.bind((MCAST_GRP, MCAST_PORT))

# https://stackoverflow.com/questions/15322242/python-bind-error-on-multicast-bind-on-windows	
group = socket.inet_aton(MCAST_GRP)
iface = socket.inet_aton(MCAST_IFACE) # listen for multicast packets on this interface.	

sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, group+iface)
sock.settimeout(1.000)

print("\nlistening...")
counter = 0
try:
	while True:
		try:
			(data, sender) = sock.recvfrom(2048)
			counter += 1
			print("[%d] received %d bytes from %s" % (counter, len(data), sender))
		except socket.timeout:
			sys.stdout.write('.')
		# end try
	# end while
except KeyboardInterrupt:
	print("\ncancelled by user")
# end try
	