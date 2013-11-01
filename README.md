# Test scripts

## SIM5216_http_get

This script does a simple HTTP GET request to a server and displays the output in the terminal screen.

This code is very similar to <a href="http://www.cooking-hacks.com/documentation/tutorials/arduino-3g-gprs-gsm-gps">this</a>
because they used the SIM5218 module, where I have used the Itead 3G shield with the SIM5216
When I have received the Itead 3G Shield there was no working example given.

These are my instructions to send AT commands to a Itead 3G shield:
<ol>
<li>The SIM5216 default baud rate is 115200 and the Arduino Uno does not allow you to use the hardware UART pins (D0 and D1) for any other communication except to a terminal screen.</li>
<li>Luckily this shield comes with a debuggable USB interface. For a person to access it, you need drivers.</li>
<li>The drivers are not easy to get for Windows, but you can <a href="https://github.com/jeanbritz/ArduinoSkripsie/blob/master/WindowsDrivers_SIM5218_2.4.00.rar">click here</a> to get them. Install them first!</li>
<li>You need a mini-USB cable to communicate with the SIM5216 module with AT commands. </li>
<li>If you have one, stack your Itead 3G shield on top of the Arduino and power up the Arduino via USB or a power supply</li>
<li>Then check to see if your 3G shield is on. Atleast 3 of the 4 LEDs must be on. If it is not try pressing the reset or power button on the shield</li>
<li>Plug in the mini-USB cable between the shield and computer USB port and open Device Manager and see if there are new hardware detected</li>
<li>When you have successfully installed the drivers, you will have serial COM ports that have the label: SimTech HS-USB AT Port 9000 or simlilar to that </li>
<li>Try connecting to that port in a terminal program (e.g. TeraTerm, ClearTerminal or HyperTerminal etc.)</li>
<li>Connect to the COM port that shows something like this:
  <ul>
  <li>Baud rate: 115200</li>
<li>Data bits: 8</li>
<li>Stop bits: 1</li>
<li>Other settings: None</li>
</ul></li>


</ol>




