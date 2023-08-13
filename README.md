## 说明
1、MCU：APM32F103

2、bootloader用的generic-none_bootloader，已附上

3、摇杆引脚定义在vial/config.h下，
``` C
/*  joyStick  */
#define ANALOG_JOYSTICK_X_AXIS_PIN B0  //X轴引脚
#define ANALOG_JOYSTICK_Y_AXIS_PIN B1  //Y轴引脚
#define ANALOG_JOYSTICK_CLICK_PIN  A7  //按键，不用注释掉即可
```

4、VIAL定义了三个键码

|  键码  |  说明  |
|  ----  |  ---  |
|  CSO  |   启用摇杆，默认状关闭 |
|  CSU  |   摇杆灵敏度+  |
|  CSD  |   摇杆灵敏度-  |

上电后需要按CSO键（键码在custom，自行添加），才启用摇杆。有概率出现漂移，故默认关闭。

