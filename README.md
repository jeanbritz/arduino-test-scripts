# Test scripts

## SIM5216_http_get

This script does a simple HTTP GET request to a server and displays the output onto a terminal screen.

The code used in the "SIM5216_HTTP_GET.ino" is very similar to <a href="http://www.cooking-hacks.com/documentation/tutorials/arduino-3g-gprs-gsm-gps">this</a>
because they used the SIM5218 module, where I have used the Itead 3G shield with the SIM5216.

When I have received the Itead 3G Shield there was no working example given.

These are my instructions to send AT commands from an Arduino Uno to an Itead 3G shield using SoftwareSerial:
<ol>
<li>First you will need a registered SIM card slotted into the SIM card holder located on the bottom of the shield</li>
<li>The SIM5216 default baud rate is set to 115200 and because the Arduino Uno does not allow us to use the hardware UART pins (D0 and D1) for any other communication we need to lower the baud rate to be able to use a software UART implementation.</li>
<li>Luckily this shield comes with an USB interface. For Windows users to be able to use this interface, you will need drivers.</li>
<li>The drivers was not easy for me to obtain, but for you it is available <a href="https://github.com/jeanbritz/ArduinoSkripsie/blob/master/WindowsDrivers_SIM5218_2.4.00.rar">here</a> . Download them now!</li>
<li>You will need a mini-USB cable to communicate between your computer and the SIM5216 module using AT commands. </li>
<li>If you have a mini-USB cable then plug it in and stack your Itead 3G shield on top of the Arduino Uno. Supply power to Arduino using its USB-interface or by connecting an external power supply to its power jack.</li>
<li>Check if your 3G shield shows any signs of life (i.e. if the shield has enough power then at least 3 of the 4 LEDs will be shining. If not, try pressing the reset or power buttons on the shield.</li>
<li>Plug in the mini-USB cable between the shield and the computer's USB port and open <em>Device Manager</em> to see if there are any new hardware detected.</li>
<li>Right-click on the drivers and select <em>Update Driver</em> or something similar. Locate the files that you have downloaded and use their directory path to install the drivers with them.</li> 
<li>When you have successfully installed the drivers, you will have serial COM ports that have the label: SimTech HS-USB AT Port 9000 or something similar. </li>
<li>Try connecting to the port with the above mentioned label using a terminal program (e.g. TeraTerm, ClearTerminal or HyperTerminal etc.)</li>
<li>Connect to the COM port using these settings:
  <ul>
  <li>Baud rate: 115200</li>
<li>Data bits: 8</li>
<li>Stop bits: 1</li>
<li>Other settings: None</li>
</ul></li>
<li>When you're connected type "AT" and press Enter. If the response is "OK", you are in my friend!</li>
<li>Now you need to change the baud rate on the SIM5216 for good. In the terminal's windows, type "AT+IPREX=9600" and press Enter. This will change the baud rate to 9600 permanently, which will make the Arduino Uno compatible to communicate with the SIM5216 module using AT commands over SoftwareSerial.</li>
<li>You will also need to change "AT+CSOCKAUTH", "AT+CGSOCKCONT" and "AT+CGATT", but these settings depend on your mobile operator's APN name, username, password and additional settings. (This information can be obtained by slotting the SIM card into a mobile phone and request the settings to access the internet.)</li>
<li><a href="http://www.mt-system.ru/sites/default/files/simcom_sim5215_sim5216_atc_en_v1.20.pdf">Click here</a> to read the AT Command manual.</li>
<li>If you are sure all the settings had been set correctly, then you can upload the Arduino sketch to see whether it will compile successfully.</li>
<li>When it has done uploading, open the Serial Monitor in Arduino IDE to see if there is any response. The status LED on the shield will blink faster indicating that data is busy being transmitted.</li>
Please note: The web server used in the sketch does not exist anymore, so I would advise you to make your own web server.
<b>Another important note: </b> Please make sure the SoftwareSerial receive buffer is big enough. It must be at least 128 bytes for receiving HTTP responses successfully.
For Windows users to change this, go to "Program Files/Arduino/libraries/SoftwareSerial" and edit SoftwareSerial.h. In this file there is a <code>#define _SS_MAX_RX_BUFF 64</code>. Change the 64 to 128, otherwise your HTTP reponses will not be received correctly. (FYI: The buffer's size must be increased, because the Arduino's software UART is too slow for the large quantity of bytes being sent by the SIM5216 module.
</ol>
My advice when developing:
<ul>
<li>Every byte retrieved via <code>gsmSerial.read()</code> must be put into an array. The Arduino is very slow with receiving a byte and directly transmitting it to the terminal window.</li>
<li>Keep HTTP requests short obviously. Try to develop a separate API for communicating with the GSM.</li>
<li>Main solution when using this Itead 3G shield is to buy an Arduino Mega 2560 instead!</li>
</ul>





