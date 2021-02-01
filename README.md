# ESP32
In this project, I will try to run a **computer vision application on ESP32**. 
 - The application should be able to oranges and apples apart in pictures. <br> 
 - The application will be running on a web server on the ESP32 itself.

But at first, to familiarize with ESP32, I had to run the *Blink* standard example. The following paragraph is somewhat a tutorial to blinking a LED on ESP32 for the first time. 

### BLINKING GPIO2 (ESP-IDF)
#### 1) Installing Prerequisites: ESPRESSIF Toolchain
`sudo apt-get install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0`

### 2) Getting ESP-IDF 
<a href="https://github.com/espressif/esp-idf">ESP-IDF</a> are libraries needed to build applications for the ESP32. Using the following commands: 
1. create directory named *esp*:<br> `mkdir -p ~/esp` 
2. change the working directory to *esp*:<br>`cd ~/esp`
3. clone the esp-idf repository on the *esp* directory: <br>`git clone --recursive https://github.com/espressif/esp-idf.git`<br>

### 3) Installing the tools: 
In this part, we will install the tools use by ESP-IDF, such as: *compiler, debugger, Python packages...*
1. change directory to *esp/esp-idf*, that you had just downloaded by *cloning* the esp-idf repository. <br> `cd ~/esp/esp-idf`
2. install the tools by executing *install.sh*: <br> `./install.sh`

##### The previous steps are one-timers. The following steps are to be repeated every time you build a project. 

### 4) Setting up the env variables: 
1. setting the working directory: <br>`cd ~/esp/esp-idf/` <br>
2. run: <br> `. ./export.sh`

### 5) Build, and Flash the *Blink* example:
The esp-idf comes with a few examples you can run and test. Those examples are to be found in `/esp-idf/examples/get-started' 
1. Copy the *blink* project to `~/esp` directory: 
```
cp -r /esp-idf/examples/get-started/blink .
```
*(On the standard blink example, the GPIO to blink is not specified. Therefore, the code has to be modified beforehand. As an example: `#define BLINK_GPIO 2`)*

2. Connect your device: <br>
*To figure out what port the ESP32 is, use the following command `ls /dev/tty*` before and after plugging the microcontroller in. The name of the port ESP32 is on will show up on the list after plugging it. <br>
The name of the port is usually `/dev/ttyUSB0`* .

3. change directory: <br>
``` 
cd ~/esp/blink
```
4. configure: 
```
idf.py set-target esp32
idf.py menuconfig 
idf.py build
sudo chmod a+rw /dev/ttyUSB0
idf.py -p /dev/ttyUSB0 -b 115200 flash
```
### Web Server (Arduino)


### *references:* 
- *ESP-IDF documentation: <a href= "https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/0"> Get Started </a>*
