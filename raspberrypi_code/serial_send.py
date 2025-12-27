import serial
import sys
import time

# Serial Port and Speed Settings
serial_port = '/dev/ttyUSB0'  # Check if ACM0 instead!
baud_rate = 9600

# Serial Port Initialization
ser = serial.Serial(serial_port, baud_rate, timeout=1)
time.sleep(2)  # Allow Arduino to reset

def send_data(data):
    ser.write((data + "\n").encode())  # Always send newline
    ser.flush()

    # Listen for Arduino response
    time.sleep(0.05)  # Give it time to respond
    while ser.in_waiting > 0:
        response = ser.readline().decode().strip()
        if response:
            print("Arduino:", response)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python send_data.py servo3=45")
        sys.exit(1)

    command = sys.argv[1]
    send_data(command)
    print("Sent:", command)

