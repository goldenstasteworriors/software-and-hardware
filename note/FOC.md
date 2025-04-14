## FOC

无刷电机控制是通过交替开关各个mos管实现的，这个过程需要单片机

![image-20250224225242739](../../pictrue/image-20250224225242739.png)

#### 克拉克变换(与逆变换)

降维解耦三相波形，本质是由于基尔霍夫定律，我们不需要考虑三相电流，只需要考虑其中两个



![image-20250224222708608](../../pictrue/image-20250224222708608.png)

![image-20250224222727787](../../pictrue/image-20250224222727787.png)

为了保证前后等幅值等功率，可能在前面会多乘一个系数

反过来升维就是克拉克逆变换

![image-20250224224506281](../../pictrue/image-20250224224506281.png)



### 帕克变换

磁铁在转，不想让坐标系跟它一起乱动，故有了~





### 开环控制

如控制开环速度，实际上就是要控制在给定Uq,Ud时每个时候要转到多少电角度





In file included from E:\FOC\DengFOC_FFBKnob-main\Src\课时4 旋钮力控功能实现-边界模式\Knob_Ctrl_4\AS5600.h:2,
                 from E:\FOC\DengFOC_FFBKnob-main\Src\课时4 旋钮力控功能实现-边界模式\Knob_Ctrl_4\AS5600.cpp:1:
C:\Users\asus\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\libraries\Wire\src/Wire.h: In member function 'double Sensor_AS5600::getSensorAngle()':
C:\Users\asus\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\libraries\Wire\src/Wire.h:127:13: note: candidate 1: 'uint8_t TwoWire::requestFrom(int, int)'
     uint8_t requestFrom(int address, int size);
             ^~~~~~~~~~~
C:\Users\asus\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\libraries\Wire\src/Wire.h:125:13: note: candidate 2: 'uint8_t TwoWire::requestFrom(uint8_t, uint8_t)'
     uint8_t requestFrom(uint8_t address, uint8_t size);
             ^~~~~~~~~~~
C:\Users\asus\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\libraries\Wire\src/Wire.h:127:13: note: candidate 1: 'uint8_t TwoWire::requestFrom(int, int)'
     uint8_t requestFrom(int address, int size);
             ^~~~~~~~~~~
C:\Users\asus\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\libraries\Wire\src/Wire.h:123:13: note: candidate 2: 'uint8_t TwoWire::requestFrom(uint16_t, uint8_t)'
     uint8_t requestFrom(uint16_t address, uint8_t size);
             ^~~~~~~~~~~