// This console program opens serial port (see const std::string port param. below)
// on a Windows PC to which Arduino board is connected.
// You can send commands to the Arduino board (single chars) to activate/deactivate sending
// data from Arduino board to the PC.
// When sending is activated program receives the incoming data (in JSON format), prints it to the console
// and logs the data to the file (see const std::string log_file_name param. below).

#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <conio.h>

#include "hdr/SerialPort.h"
#include "hdr/logToFile.h"

#define INPUT_DATA_BYTES 1 // read data 1 byte at a time in order to get the end of the message ('}' symbol)

char inputData[INPUT_DATA_BYTES];
const std::string port = {"COM4"};
const std::string log_file_name = {"arduino_log.txt"};
std::string data_received;

int main(){

    SerialPort arduino(port.c_str());

    if (arduino.isConnected()){
        std::cout << "Connected to the port " << port << std::endl;
        std::cout << "You can activate/pause sending data from Arduino by pressing a/p keys...\n\n\n";
    }
    else { std::cin.get(); }


    while (arduino.isConnected()){

        /// getting console input to activate/deactivate messaging without hitting ENTER
        if (kbhit() != 0) {
            char command = getch();
            char *cmd = &command;
            bool write_status = arduino.WriteSerialPort(cmd, sizeof(*cmd));
            if (write_status) {
                if      (command == 'a') std::cout << "Activated successfully!                        " << std::endl;
                else if (command == 'p') std::cout << "Deactivated successfully!                      " << std::endl;
            }
        }

        /// reading data from Arduino
        arduino.ReadSerialPort(inputData, INPUT_DATA_BYTES);
        std::string currentChunk(inputData);
        data_received += currentChunk;

        if (data_received.back() == '\n'){ // '}'
            if (data_received.size() == 1) {
                data_received.clear();
            }
            else {
                data_received.back() = '\r';
                std::cout << "----RECEIVED: " << data_received;
                /// logging received data to file
                if (!logToFile(log_file_name, data_received)) {
                    std::cerr << "Logging to file failed!\n";
                }
                data_received.clear();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    system("pause");

    return 0;
}
