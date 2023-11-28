[toc]

## USART

效果:能使用USART1正常发送接收，并把我们发送的信息显示在串口上；可以使用printf,scanf	函数

注:==要用此法记得勾选USART1的NVIC==

C:\Users\86180\Desktop\KEIL project\USART

魔法棒-Target-使用microlib

main.c 27-31关于寄存器的宏定义+一些要用的引用

main.c 97 开启接收中断(其实是我们的发送)

main.c 153-176 (USER CODE 4) 接收回调函数

usart.c  142-154 printf,scanf的重定向(不想用这两个函数的可以直接用HAL_UART_Transmit)



## DMA串口空闲接收

除USART外：

删掉main.c 98

main.c 32

main.c 99

main.c 178-186

```c
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)//在DMA模式下接收一定数量的数据，直到接收到预期数量的数据或发生空闲事件
HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)//串口空闲中断处理函数
```

## OLED

效果:实现I2C通讯的OLED使用，包括输出字符，汉字等

注:把.h文件加入工程的步骤:魔法棒-C++-Include Path-.h文件所属的文件夹

C:\Users\86180\Desktop\KEIL project\IIC

创建三个空白文件，分别为OLED_I2C的.c/.h文件,codetab.h文件,复制对应文件

main.c 27-34 关于寄存器的宏定义+一些要用的引用(部分是串口的，懒得改了)

main.c 99 OLED初始化

按照想法使用OLED_I2C中的函数显示内容

==16*16的点阵字体取模方式：共阴——列行式——逆向输出==

如果要显示图片，需要：

1. 将图片用画图软件打开，更改像素至123-64以内
2. 另存为BMP的单色图
3. DrawBMP函数中对角线的x,y差值应该正好是像素值，不然会被缩短/拉长
4. 记得在main中宏部分加上extern const unsigned char=对应位图名，不然报错



## 同系列移植

1. 更换启动文件
2. 魔术棒->Target 修改芯片型号
3. 魔术棒->c/c++ 修改define



后面再出问题就到定义/网上查