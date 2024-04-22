### struct,pack/unpack

需要`import struct`

使用类似

```python
            data = struct.pack("<bbiiibb",
                                0xAA,     #帧头
                                0xAE,     #帧头
                                tag.id(), #数据id
                                #x的坐标
                                int(10000*tag.x_translation()),#数据1
                                #z的坐标
                                -int(10000*tag.z_translation()),#数据2
                                0xBF,     #标志位表示大于零
                                0xAC)     #帧尾
```

![image-20240410092738798](C:\Users\asus\OneDrive\桌面\NEW_MY\pictrue\image-20240410092738798.png)可以指定打包后的字节顺序

![image-20240410092504874](C:\Users\asus\OneDrive\桌面\NEW_MY\pictrue\image-20240410092504874.png)