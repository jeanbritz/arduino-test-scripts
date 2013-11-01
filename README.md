# Test scripts

## SIM5216_http_get

This script does a simple HTTP GET request to a server and displays the output in the terminal screen.

This code is very similar to <a href="http://www.cooking-hacks.com/documentation/tutorials/arduino-3g-gprs-gsm-gps">this</a>
because they used the SIM5218 module, where I have used the Itead 3G shield with the SIM5216
When I have received the Itead 3G Shield there was no working example given.

These are my instructions to send AT commands from an Arduino Uno to a Itead 3G shield using software serial:
<ol>
<li>Firstly you will need a registered SIM card plugged into the SIM card holder on the bottom of the shield</li>
<li>The SIM5216 default baud rate is 115200 and the Arduino Uno does not allow you to use the hardware UART pins (D0 and D1) for any other communication except to a terminal screen.</li>
<li>Luckily this shield comes with a debuggable USB interface. For a person to access it, you need drivers.</li>
<li>The drivers are not easy to get for Windows, but you can <a href="https://github.com/jeanbritz/ArduinoSkripsie/blob/master/WindowsDrivers_SIM5218_2.4.00.rar">click here</a> to get them. Download them first!</li>
<li>You need a mini-USB cable to communicate with the SIM5216 module with AT commands. </li>
<li>If you have one, stack your Itead 3G shield on top of the Arduino Unp and power up the Arduino via USB or a power supply</li>
<li>Then check to see if your 3G shield is on. Atleast 3 of the 4 LEDs must be on. If it is not try pressing the reset or power button on the shield</li>
<li>Plug in the mini-USB cable between the shield and computer USB port and open Device Manager to see if there are any new hardware detected</li>
<li>Right click on the drivers and select Update Driver or something. Locate the files that you have downloaded and install the drivers with them</li> 
<li>When you have successfully installed the drivers, you will have serial COM ports that have the label: SimTech HS-USB AT Port 9000 or simlilar to that </li>
<li>Try connecting to that port in a terminal program (e.g. TeraTerm, ClearTerminal or HyperTerminal etc.)</li>
<li>Connect to the COM port that shows something like this:
  <ul>
  <li>Baud rate: 115200</li>
<li>Data bits: 8</li>
<li>Stop bits: 1</li>
<li>Other settings: None</li>
</ul></li>
<li>When you're connected type "AT" and if the response is "OK", you are in!</li>
<li>Now you need to change the baud rate permanently. Type "AT+IPREX=19200" and press enter. This will change the baud rate to 19200 permanently.</li>
<li>The following commands needs also needs to be changed, but you need to look it up yourself, because it depends on your mobile operator.</li>
<li><a href="http://www.simcom.ee/documents/wcdma-hspa/sim5216/SIM5216J_AT_Command_Manual_V1.02.pdf">Click here</a> to read the AT Command manual.</li>
<li>You will need to set "AT+CSOCKAUTH", "AT+CGSOCKCONT" and "AT+CGATT" to setup your device for GPRS.</li>
<li>If everything is set, then you can upload the Arduino sketch and see whether it will execute</li>
<li>Please note: The web server used in the sketch is not always accessible, so I would advise you to make your own web server</li>
<li>Another important note please make the software serial buffer bigger!! Go to the Arduino library and edit SoftwareSerial.h. In this field there is a define _SS_MAX_RX_BUFF set to 64, change it to 128, otherwise your HTML reponses becomes corrupt when you get it eventually.
<\li>
</ol>




