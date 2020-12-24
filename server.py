import socketserver

class MyTCPHandler(socketserver.BaseRequestHandler):
	def handle(self):
		self.data = self.request.recv(2048).strip()
		print("{} wrote:".format(self.client_address[0]))
		print(self.data)
		print("self.client_adress {}".format(self.client_address))
		self.request.sendall(self.data.upper())

if __name__ == "__main__":
	with socketserver.TCPServer(('127.0.0.1', 80), MyTCPHandler) as server:
		server.serve_forever()
