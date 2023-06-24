This console program opens serial port on a Windows PC to which Arduino board is connected.
You can send commands to the Arduino board (single chars) to activate/deactivate sending data from Arduino board to the PC.
When sending is activated program receives the incoming data (in JSON format), prints it to the console
and logs the data to the file.

In the folder ArduinoSketch_JsonSend you can find Arduino sketch to demonstrate activation/deactivation of sending JSON data
from Arduino board through the Serial Port on the Windows PC.
