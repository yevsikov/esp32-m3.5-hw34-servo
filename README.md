# ESP32 - Learning Project

This is a small educational project for the [Embedded Development course](https://beetroot.academy/courses/online/kurs-embedded-development)

## Circuit Diagram

```
ESP32-S3

                    +----------------------+
3.3V ---------------|                      |
                    |      ESP32-S3        |
GPIO4 --------------|                      |
GPIO5 --------------|                      |
                    |                      |
                    |                      |
                    |                      |
                    |                      |
GND ----------------|                      |
                    +----------------------+


Potentiometer

+-------+
|       |--- 3.3V
|   O   |--- GPIO4
|       |--- GND
+-------+


Servo

             +----------------+     
+5V ---------┼🔴              |    |
GND ---------┼🟤              |----+
GPIO5 -------┼🟠              |
             +----------------+

```


## Result

![Result](./result.gif)

If GIF preview is not displayed in your viewer, open it directly: [result.gif](./result.gif)