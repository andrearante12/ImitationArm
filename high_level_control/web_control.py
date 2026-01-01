from flask import Flask, render_template, request
import serial

app = Flask(__name__)

# Set correct serial port for your Arduino
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/move', methods=['POST'])
def move():
    servo = request.form['servo']
    angle = request.form['angle']
    cmd = f"servo{servo}={angle}\n"
    ser.write(cmd.encode())
    return "OK"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)

