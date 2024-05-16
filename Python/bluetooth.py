
from serial import Serial
from serial.serialutil import SerialException

class Bluetooth():

    def __init__(self, port: str):
        self.serial = Serial()
        print('Connecting to ', port, '......')

        try:
            self.serial = Serial(port, 9600, timeout=2)
            print('Successfully connect to port: ', port)

        except SerialException:
            print('Failed to connect port: ', port)

    def disconnect(self):
        self.serial.close()

    def write(self, data: str):
        encoded_data = data.encode("utf-8")
        self.serial.write(encoded_data)

    def read(self):
        waiting = self.serial.in_waiting
        if waiting >= 0:
            return self.serial.readline().decode("utf-8")[:-1]
        return ""

def main():
    bt = Bluetooth('COM10')
    bt.write('e2e4')

if __name__ == '__main__':
    main()