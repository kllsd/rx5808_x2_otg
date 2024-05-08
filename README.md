# rx5808_x2_otg

## Language

- [English](#english)
- [中文](#中文)

---

## English

rx5808_x2_otg is a dual receiver for 5.8g analog signal image transmission for mobile phones or computers based on the rx5808 module

---

## 中文

rx5808_x2_otg是基于rx5808模块的5.8g手机图传双接收机

本项目目的就是把rx5808接收机和usb视频采集卡整合，做成usb图传，配合usb线可连接任何支持usb视频流的设备实现图传。

---

## CH32X035C8T6

原RX5808接收机有两个版本，一个是使用STM32作为主控，另一个是使用ESP32作主控，这里作者随便拿了手头上的一个单片机做的试验版，只有简单的图形界面和按键控制。

---

## MS2107

这里的视频采集方案采用ms2107方案，ms2107是一款视频和音频采集芯片，支持cvbs, s-video信号和音频信号转usb。

以下是支持的视频格式：

| YUV422  | MJPEG |
| ---------- | -----------|
| 720x576@25Hz/20Hz/10Hz/5Hz | 1920x1080@30Hz/20Hz/10Hz/5Hz |
| 720x480@30Hz/20Hz/10Hz/5Hz | 1280x720@60Hz/50Hz/30Hz/10Hz |
| 640x480@30Hz/20Hz/10Hz/5Hz | 800x600@60Hz/50Hz/30Hz/10Hz |
| 480x320@30Hz/20Hz/10Hz/5Hz | 720x576@60Hz/50Hz/30Hz/10Hz |
| 320x240@30Hz/20Hz/10Hz/5Hz | 720x480@60Hz/50Hz/30Hz/10Hz |
|  | 640x480@60Hz/50Hz/30Hz/10Hz |
|  | 480x320@60Hz/50Hz/30Hz/10Hz |
|  | 320x240@60Hz/50Hz/30Hz/10Hz |

推荐使用1280x720@60Hz模式

作者也用过更便宜的ms2106，但在各种实验之后最终选择ms2107。

虽然ms2106支持的设备更加广泛，且更低的价格，但由于其为了满足低速usb2.0，且最高帧率只有30帧，还会压缩画面再进行传输。

ms2107虽然不会对画质进行压缩，但是ms2107对设备和usb的速度有严苛的要求，太过老旧的设备或太长的usb线都会对传输造成影响。

经作者试验，usb线的长度不要超过30cm，设备端必须是支持usb2.0高速(HIGH SPEED 480Mbps)接口的设备。

### 下载烧录EEPROM

- [下载工具&BIN文件](/MS2107/)

(1) 打开下载工具(MS21XX&91XXDownloadTool_1.7.2_BUILD20230104.exe)，选择MS2107

<img src="https://github.com/kllsd/rx5808_x2_otg/blob/main/img/MS2107_1.png" width="480px">

(2) 将板子连接电脑，点击Connect，再点击Read，可以看到读出来的信息（默认是全0xFF)

<img src="https://github.com/kllsd/rx5808_x2_otg/blob/main/img/MS2107_2.png" width="480px">

(3) 点击Open File打开bin文件(MS2107_24C16_Demo_V1.7.1_262E_20220719.bin)，再点击Download下载

<img src="https://github.com/kllsd/rx5808_x2_otg/blob/main/img/MS2107_3.png" width="480px">

(4) 下载完打开设备管理器就能看到设备了

<img src="https://github.com/kllsd/rx5808_x2_otg/blob/main/img/MS2107_4.png" width="480px">

---

### LICENSE

- [license](LICENSE)
