import socket
import subprocess
class Client:
    def __init__(self, _hostname, _port):
        self.hostname = _hostname
        self.port =_port
        try:
            self.clientSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            self.clientSocket.connect_ex((self.hostname,self.port))
        except:
            self.__init__(self.hostname,self.port)

    def close(self):
        try:
            self.clientSocket.close()
        except Exception as e:
            print(e)

    def sendData(self, _data):
        self.clientSocket.send(_data.encode('utf-8'))


while True:
    try:
        subprocess.call('clear')
        _client = Client("10.0.0.112", 4444)
        print('Pressione 1 para Ligar\nPressione 2 para Desligar\n')
        if int(input()) == 1:
            _client.sendData('Turn ON')
        else:
            _client.sendData('Turn OFF')
        _client.close()
    except KeyboardInterrupt:
        quit(0)
