# Environment-Monitoring-Gadget
A smart-home gadget prototype built using the Arduino embedded platform that provides users with temperature, pressure, and altitude data of the current location of your Arduino Uno/Mega board via a liquid crystal display.

The equipment required is the Adafruit BMP280 I2C or SPI Barometric Pressure & Altitude Sensor, an I2C Interface LCD1602 Adapter, a push-button switch, a 220-ohm resistor, a 16x2 LCD screen, electrical wires, and an Arduino Uno or Arduino Mega. 

The gadget takes new sensor readings every 3 seconds and allows users to change the reading being displayed. Users can choose between three options to display in the screen: temperature in Celsius, pressure in Pascals, or altitude above sea level in Meters. The data displayed can be changed when the user presses the button and holds until the screen updates. The time it takes for the screen to update can be anywhere from a few milliseconds to a maximum of three seconds.
