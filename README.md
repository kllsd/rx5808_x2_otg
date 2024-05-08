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

本项目将rx5808接收机和usb视频采集卡整合，做成usb图传，配合usb线可连接任何支持usb视频流的设备实现图传。

## CH32X035C8T6

CH32X035C8T6是南京沁恒微电子新推出的工业级RISC-V单片机，主频48MHz，20K SRAM，62K Flash <br>
IDE使用Mounriver Studio
[下载地址](http://www.mounriver.com/)

原RX5808接收机有两个版本，一个是使用STM32作为主控，另一个是使用ESP32作主控，这里作者随便拿了手头上的一个单片机做的试验版，目前只有简单的图形界面和按键控制。
后续会持续更新代码，更喜欢原版本的界面的话可以克隆本项目的pcb工程，将主控更改成想要即可。

完整工程在X035C8T6_RX5808文件夹
- [X035C8T6_RX5808](/X035C8T6_RX5808/)

## RX5808 5.8g视影音模块

RX5808模块在淘宝咸鱼上都有卖的，价格基本在20-30之间，注意要买spi模式的，不然开关模式只有8个频段，RX5808的代码非常简单，可以移植到各种单片机上。

买到开关模式的RX5808模块也不必悲伤，将RX5808模块开盖按照下图操作即可改为spi模式

<img src="https://github.com/kllsd/rx5808_x2_otg/blob/main/img/rx5808_1.jpg" width="480px">

RX5808的频率表如下(单位MHz)：

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | CH/GRUP |
| --- | --- | --- | --- | --- | --- | --- | --- | :---: |
| 5865 | 5845 | 5825 | 5805 | 5785 | 5765 | 5745 | 5725 | A |
| 5733 | 5752 | 5771 | 5790 | 5809 | 5828 | 5847 | 5866 | B |
| 5705 | 5685 | 5665 | 5645 | 5885 | 5905 | 5925 | 5945 | C |
| 5740 | 5760 | 5780 | 5800 | 5820 | 5840 | 5860 | 5880 | D |
| 5658 | 5695 | 5732 | 5769 | 5806 | 5843 | 5880 | 5917 | E |
| 5362 | 5399 | 5436 | 5473 | 5510 | 5547 | 5584 | 5621 | F |

## SPI

RX5808模块内部芯片为RTC6715，根据RTC6715的数据手册描述，SPI为25位，其中地址位4位，数据位20位，还有1位读写命令

具体时序参考下图：

<img src="https://github.com/kllsd/rx5808_x2_otg/blob/main/img/rx5808_2.png" width="560px">

SPI片选(SPI_CS)
```C
void RTC6715_SPI_Select(FunctionalState NewState)
{
    Delay_Us(1);
    if(NewState != DISABLE)
    {
        GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_CS);
    }
    else
    {
        GPIO_SetBits(SPI_Soft_GPIO_Port, SPI_Soft_CS);
    }
    Delay_Us(1);
}
```

SPI发送1个比特
```C
void RTC6715_SPI_Send(uint8_t n)
{
    GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_SCK);
    Delay_Us(1);
    if(n == 1)
    {
        GPIO_SetBits(SPI_Soft_GPIO_Port, SPI_Soft_MOSI);
    }
    else {
        GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_MOSI);
    }
    Delay_Us(1);
    GPIO_SetBits(SPI_Soft_GPIO_Port, SPI_Soft_SCK);
    Delay_Us(1);
    GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_SCK);
    Delay_Us(1);
}
```

RX5808设置频率
```C
uint32_t RTC6715_CalculateFrequencyData(u16 frequency)
{
    uint16_t N;
    uint8_t A;
    frequency = (frequency - 479)/2;
    N = frequency/32;
    A = frequency%32;
    return (N << 7 | A);
}

void RTC6715_SetFrequency(u16 frequency)
{
    uint32_t sRegB;
    uint8_t i;

    sRegB = RTC6715_CalculateFrequencyData(frequency);

    // Enable SPI pin
    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
    RTC6715_SPI_Select(ENABLE);

    // Address (0x01)
    RTC6715_SPI_Send(1);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);

    // Read/Write (Write)
    RTC6715_SPI_Send(1);

    // Data (20 LSB bits)
    for (i = 0; i < 20; i++) {
        ((sRegB>>i) & 0x1) ? RTC6715_SPI_Send(1) : RTC6715_SPI_Send(0);
    }

    // Disable SPI pin
    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
}
```

## MS2107

这里的视频采集方案采用ms2107方案，ms2107是一款视频和音频采集芯片，支持cvbs, s-video信号和音频信号转usb。

以下是支持的视频格式：

| YUV422 | MJPEG |
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

作者也用过更便宜的ms2106，但在各种实验之后最终选择ms2107。<br>
虽然ms2106支持的设备更加广泛，且更低的价格，但由于其为了满足低速usb2.0，且最高帧率只有30帧，还会压缩画面再进行传输。<br>
ms2107虽然不会对画质进行压缩，但是ms2107对设备和usb的速度有严苛的要求，太过老旧的设备或太长的usb线都会对传输造成影响。<br>
经作者试验，usb线的长度不要超过30cm，设备端必须是支持usb2.0高速(HIGH SPEED 480Mbps)接口的设备。<br>

### 下载烧录EEPROM

MS2107的软件和程序在MS2107文件夹
- [下载工具&bin文件](/MS2107/)

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
