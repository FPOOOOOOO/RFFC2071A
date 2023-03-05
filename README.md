1、ESP32 GPIO 模拟 I2C 通过SDATA SCLK LE三条线完成对RFFC2071A的配置
2、主要代码参考了[80C51版本](https://github.com/NightIsDark/RFFC),硬件上ENBL不用，RESET通过4.7K上拉拉高。
3、如果要用2071，需要修改默认的寄存器map、5个步骤的一些具体过程，参考官方Datasheet
4、I2C 前后会多几个时钟因为示波器看了一下这样能保证波形
5、使用的话只需要修改配置的频率、输入的晶振、和一些寄存器
6、有问题可以issue