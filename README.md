# rx5808_x2_otg

## Language

- [English](#english)
- [中文](#中文)

---

### English

rx5808_x2_otg is a dual receiver for 5.8g analog signal image transmission for mobile phones or computers based on the rx5808 module

---

### 中文

rx5808_x2_otg是基于rx5808模块的5.8g手机图传双接收机

本项目目的就是把rx5808接收机和usb视频采集卡整合，做成usb图传，配合usb线可连接任何支持usb视频流的设备实现图传。

## MS2107

这里的视频采集方案采用ms2107方案，ms2107是一款av转usb芯片，支持以下信号的转换

<div align="center">

| YUV422  | MJPEG |
| ---------- | -----------|
| 表格单元   | 表格单元   |
| 表格单元   | 表格单元   |

</div>

之前作者也用过更便宜的ms2106，但在各种实验之后还是选择ms2107。
但是ms2106会压缩画质，ms2107就不会，但是ms2107对设备和usb线的长度有要求，usb线的长度不能超过30cm，且手机端必须是支持usb3.0的手机，太老旧的手机可以考虑使用ms2106

---

### LICENSE

- [license](LICENSE)
