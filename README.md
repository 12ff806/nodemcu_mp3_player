## NodeMCU MP3 player

NodeMCU 制作的 mp3 播放器


## DFPlayer Mini 模块

### 硬件清单

电路图一硬件清单如下:

* NodeMCU (ESP8266)
* 5V usb 供电电源 (给 NodeMCU 供电)
* DFPlayer Mini 模块
* 1.5v 5号电池 x 3 (给 DFPlayer Mini 供电)
* SD card
* Amplifier PAM8403
* 扬声器 x 2


电路图二硬件清单如下:

* NodeMCU (ESP8266)
* DFPlayer Mini 模块
* 1.5v 5号电池 x 6 (9v 给所有模块供电)
* SD card
* Amplifier PAM8403
* 扬声器 x 2
* 7805 稳压器 (输出5v)
* 二极管1N4001 x 1
* 470uF电容 x 1
* 220uF电容 x 1
* 100uF电容 x 1
* 0.1uF电容 x 1


### 电路图一

电路图如下

![](./docs/circuit_map_1_without_amplifier.png)

实物接线图如下

![](./docs/circuit_map_1_without_amplifier.jpeg)


需要注意的是, NodeMCU 和 DFPlayer Mini模块需单独分开供电, 防止产生噪音


### 电路图二

电路图如下

![](/docs/circuit_map_2_with_amplifier.png)

实物接线图如下

![](/docs/circuit_map_2_with_amplifier.jpeg)


### mp3文件命名

* 命名格式 0001.mp3, 0002.mp3, 0255.mp3
* 4位数字后可以加任何字符串, 0001_blablabla.mp3
* 复制mp3到sd卡的顺序会影响播放的顺序, 比如 函数 play(1) 则会播放第一个复制到sd卡的mp3文件


## XY-V17B 模块 (噪音太大 已放弃)

* NodeMCU (ESP8266)
* 5V usb 供电电源 (给 NodeMCU 供电)
* XY-V17B 模块
* SD card
* Amplifier PAM8403
* 扬声器 x 2


## 参考

[电路一参考(少了共地线)](https://stonez56.blogspot.com/2015/03/arduino-dfplayer-mini-mp3-module.html)

[电路二参考](http://markus-wobisch.blogspot.com/2016/09/arduino-sounds-dfplayer.html)

