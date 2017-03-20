'use strict';

goog.provide('Blockly.Arduino.kadapapa');

goog.require('Blockly.Arduino');


/*<!--==============================Output==============================-->*/

/**
 * 设置(接口)数字输出(低电平)
 */
Blockly.Arduino.runWdigital = function() {
    var Port_Wdigital = this.getTitleValue("PORT");
    var State_Wdigital = this.getTitleValue('Wdigital');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Wdigital'] = 'KA_Port ' + 'wdigital_' + Port_Wdigital + '(' + Port_Wdigital + ');';
    Blockly.Arduino.setups_['setup_Wdigital'] = 'pinMode(s1, OUTPUT);\n';
    var code = 'wdigital_' + Port_Wdigital + '.dWrite1(' + State_Wdigital + ');\n';
    return code;
    //return [code, Blockly.Arduino.ORDER_ATOMIC];//后面的值会出现‘,0’，目前不知道干什么用
};

/**
 * 设置(接口)PWM输出(0)
 */
Blockly.Arduino.runPwm = function() {
    var Port_Pwm = this.getTitleValue("PORT");
    var Value_pwm = Blockly.Arduino.valueToCode(this, 'Pwm', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Pwm'] = 'KA_Port ' + 'wanalog_' + Port_Pwm + '(' + Port_Pwm + ');';
    var code = 'wanalog_' + Port_Pwm + '.aWrite1(' + Value_pwm + ');\n';
    return code;
};

/**
 * 设置(接口)LED状态为(关)
 */
Blockly.Arduino.runLed = function() {
    var Port_Led = this.getTitleValue("PORT");
    var State_Led = this.getTitleValue('Led');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Led'] = 'KA_Port ' + 'LED_' + Port_Led + '(' + Port_Led + ');';
    var code = 'LED_' + Port_Led + '.dWrite1(' + State_Led + ');\n';
    return code;
};

/**
 * 设置(接口)振动器状态(关)
 */
Blockly.Arduino.runVibrator = function() {
    var Port_Vibrator = this.getTitleValue("PORT");
    var State_Vibrator = this.getTitleValue('Vibrator');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Vibrator'] = 'KA_Port ' + 'Vibrator_' + Port_Vibrator + '(' + Port_Vibrator + ');';
    var code = 'Vibrator_' + Port_Vibrator + '.dWrite1(' + State_Vibrator + ');\n';
    return code;
};

/**
 * 设置(接口)数码管显示(0)
 */
Blockly.Arduino.runDigition = function() {
    var Port_Digition = this.getTitleValue("PORT");
    var Value_Digition = Blockly.Arduino.valueToCode(this, 'num', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Digitron'] = '#include "KA_Digitron.h"';
    Blockly.Arduino.definitions_['var_Digitron'] = 'KA_Digitron ' + 'digd_' + Port_Digition + '(' + Port_Digition + ');';
    var code = 'digd_' + Port_Digition + '.display(' + value_Digition + ');\n';
    return code;
};

/**
 * 设置(接口)RGB(全部)颜色(无)
 */
Blockly.Arduino.runRGB = function() {
    var Port_RGB = this.getTitleValue('PORT');
    var Indexs_RGB = this.getTitleValue('RGB_Indexs');
    var Color_RGB = this.getFieldValue('RGBcolor');
    var Color = goog.color.hexToRgb(Color_RGB);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_RGB'] = '#include "KA_RGBLed.h"';
    Blockly.Arduino.definitions_['var_RGB'] = 'KA_RGBLed ' + 'rgbled_' + Port_RGB + '(' + Port_RGB + ',' + '10);';
    var code = 'rgbled_' + Port_RGB + '.setColor(' + Indexs_RGB + ',' + Color + ');\n';
    code += 'rgbled_' + Port_RGB + '.show();\n';
    return code;
};

/**
 * 设置(接口)舵机角度为(0)
 */
Blockly.Arduino.runServo = function() {
    var Port_Servo = this.getTitleValue('PORT');
    var Value_Angle = Blockly.Arduino.valueToCode(this, 'Angle', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Servo'] = '#include "KA_Servo.h"';
    Blockly.Arduino.definitions_['var_Servo'] = 'KA_Servo ' + 'servo_' + Port_Servo + '(' + Port_Servo + ');';
    Blockly.Arduino.setups_['setup_Servo'] = 'servo_' + Port_Servo + '.begin();';
    var code = 'servo_' + Port_Servo + '.write(' + Value_Angle + ');\n';
    return code;
};

/**
 * 设置(接口)电机转速为(0)
 */
Blockly.Arduino.runMotor = function() {
    var Port_Motor = this.getTitleValue('PORT');
    var Value_Speed = Blockly.Arduino.valueToCode(this, 'Speed', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Motor'] = '#include "KA_DCMotor.h"';
    Blockly.Arduino.definitions_['var_Motor'] = 'KA_DCMotor ' + 'motor_' + Port_Motor + '(' + Port_Motor + ');';
    var code = 'motor_' + Port_Motor + '.run(' + Value_Speed + ');\n';
    return code;
};

/**
 * 播放蜂鸣器音调为()节拍为()
 */
Blockly.Arduino.runBuzzer = function() {
    var Value_Tonality = Blockly.Arduino.valueToCode(this, 'Tonality', Blockly.Arduino.ORDER_ATOMIC);
    var Value_Beat = Blockly.Arduino.valueToCode(this, 'Beat', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Buzzer'] = '#include "KA_Buzzer.h"';
    Blockly.Arduino.definitions_['var_Buzzer'] = 'KA_Buzzer ' + 'buzzer;';
    var code = 'buzzer' + '.tone(' + Value_Tonality + ',' + Value_Beat + ');\n';
    return code;
};

/*<!--==============================Analog Input==============================-->*/

/**
 * 读取(接口)模拟量
 */
Blockly.Arduino.getAnalog = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'lightsensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'lightsensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 光线传感器(接口1)
 */
Blockly.Arduino.getLightSensor = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'avalues_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'avalues_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 声音传感器(接口1)
 */
Blockly.Arduino.getSoundSensor = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'soundsensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'soundsensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 震动传感器(接口1)
 */
Blockly.Arduino.getShake = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'shakesensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'shakesensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 压力传感器(接口1)
 */
Blockly.Arduino.getPressure = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'pressuresensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'pressuresensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 气体传感器(接口1)
 */
Blockly.Arduino.getGasSensor = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'gassensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'gassensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 火焰传感器(接口1)
 */
Blockly.Arduino.getFlameSensor = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'flamesensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'flamesensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * TVOC传感器(接口1)
 */
Blockly.Arduino.getTVOCSensor = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'tvocsensor_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'tvocsensor_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 温度传感器(接口1)
 */
Blockly.Arduino.getTemperature = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Temperature'] = '#include "KA_Temperature.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Temperature ' + 'temperature_' + Port_Analog + '(' + Port_Analog + ');';
    Blockly.Arduino.setups_['setup_Temperature'] = 'temperature_' + Port_Analog + '.begin();';
    var code = 'temperature_' + Port_Analog + '.get_temp()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 湿度传感器(接口1)
 */
Blockly.Arduino.getHumidity = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'avalues_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'avalues_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 温湿度传感器(接口1)
 */
Blockly.Arduino.getHumiture = function() {
    var Port_Analog = this.getTitleValue('PORT');
    var Type_Humiture = this.getTitleValue('Humiture');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Humiture'] = '#include "KA_Humiture.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Humiture ' + 'humiture_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'humiture_' + Port_Analog + '.getValue(' + Type_Humiture + ')';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 超声波传感器(接口1)
 */
Blockly.Arduino.getUltrasonic = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Ultrasonic'] = '#include "KA_Ultrasonic.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Ultrasonic ' + 'ultrasonic_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'ultrasonic_' + Port_Analog + 'distanceCm(400)';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 陀螺仪(轴)(角度)
 */

Blockly.Arduino.getGyro = function() {
    var Value_Axis = this.getTitleValue('AXIS');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Gyro'] = '#include "KA_Gyro.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Gyro ' + 'gyro;';
    Blockly.Arduino.setups_['setup_Gyro'] = 'gyro' + '.begin();';
    var code = 'gyro' + '.getAngle(' + Value_Axis + ')';
    //   code += 'gyro' + '.update();\n';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * PM2.5传感器(接口1)
 */
/*
Blockly.Arduino.getPM25 = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'avalues_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'avalues_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
*/
/**
 * 空气检测传感器(接口1)
 */
/*
Blockly.Arduino.getAirMonitors = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'avalues_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'avalues_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
*/
/**
 * CO2传感器(接口1)
 */
/*
Blockly.Arduino.getCo2 = function() {
    var Port_Analog = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Analog'] = 'KA_Port ' + 'avalues_' + Port_Analog + '(' + Port_Analog + ');';
    var code = 'avalues_' + Port_Analog + '.aRead2()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};
*/
/*<!--==============================Digital Input==============================-->*/

/**
 * 读取(接口)数字量
 */
Blockly.Arduino.getDigital = function() {
    var Port_Digital = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Digital'] = 'KA_Port ' + 'dvalues_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'dvalues_' + Port_Digital + '.dpRead1()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 红外收发传感器(接口1)
 */
Blockly.Arduino.getLinefollower = function() {
    var Port_Digital = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Digital'] = 'KA_Port ' + 'linefollower_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'linefollower_' + Port_Digital + '.dpRead1()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 微动开关(接口1)
 */
Blockly.Arduino.getLimitswitch = function() {
    var Port_Digital = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Digital'] = 'KA_Port ' + 'lsw_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'lsw_' + Port_Digital + '.dpRead1()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 带灯按键(接口1)
 */
Blockly.Arduino.getButtonswitch = function() {
    var Port_Digital = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Digital'] = 'KA_Port ' + 'bsw_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'bsw_' + Port_Digital + '.dpRead1()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 自锁按键(接口1)
 */
Blockly.Arduino.getSelfholdswitch = function() {
    var Port_Digital = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Digital'] = 'KA_Port ' + 'ssw_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'ssw_' + Port_Digital + '.dpRead1()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 人体热释电传感器(接口1)
 */
Blockly.Arduino.getPirmotion = function() {
    var Port_Digital = this.getTitleValue('PORT');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['var_Digital'] = 'KA_Port ' + 'pir_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'pir_' + Port_Digital + '.dpRead1()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 数码管按键按下(接口1)
 */
Blockly.Arduino.getFourkey = function() {
    var Port_Digital = this.getTitleValue('PORT');
    var Key_Digital = this.getTitleValue('KEY');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Fourkey'] = '#include "KA_Digitron.h"';
    Blockly.Arduino.definitions_['var_Fourkey'] = 'KA_Digitron ' + 'digk_' + Port_Digital + '(' + Port_Digital + ');';
    var code = 'digk_' + Port_Digital + '.getkey()' + '==' + '(' + Key_Digital + ')';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * 触摸按键按下(接口1)
 */
Blockly.Arduino.getTouchkey = function() {
    var Port_Touchkey = this.getTitleValue('PORT');
    var Key_Touchkey = this.getTitleValue('KEY');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_Touchkey'] = '#include "KA_TouchKey.h"';
    Blockly.Arduino.definitions_['var_Touchkey'] = 'KA_TouchKey ' + 'TouchKey_' + Port_Touchkey + '(' + Port_Touchkey + ');';
    var code = 'TouchKey_' + Port_Touchkey + '.getkey()' + '==' + '(' + Key_Touchkey + ')';
    var code1 = 'TouchKey_' + Port_Touchkey + 'coding();';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/**
 * RFID卡片动作是(接口1)
 */
Blockly.Arduino.getRFID = function() {

};

/*<!--==============================TFT Screen==============================-->*/

/**
 * 设置整屏颜色为()
 */
Blockly.Arduino.runFillScreen = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.fillScreen(' + Color + ');\n';
    return code;
};

/**
 * 绘制线段 起点()终点()颜色()
 */
Blockly.Arduino.runDrawLine = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X1 = Blockly.Arduino.valueToCode(this, 'x1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y1 = Blockly.Arduino.valueToCode(this, 'y1value', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.drawLine(' + TFT_X + ',' + TFT_Y + ',' + TFT_X1 + ',' + TFT_Y1 + ',' + Color + ');\n';
    return code;
};

/**
 * 绘制矩形 起点()尺寸()颜色()
 */
Blockly.Arduino.runDrawRect = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X1 = Blockly.Arduino.valueToCode(this, 'x1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y1 = Blockly.Arduino.valueToCode(this, 'y1value', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.drawRect(' + TFT_X + ',' + TFT_Y + ',' + TFT_X1 + ',' + TFT_Y1 + ',' + Color + ');\n';
    return code;
};

/**
 * 绘制圆形 起点()半径()颜色()
 */
Blockly.Arduino.runDrawCircle = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_R = Blockly.Arduino.valueToCode(this, 'rvalue', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.drawCircle(' + TFT_X + ',' + TFT_Y + ',' + TFT_R + ',' + Color + ');\n';
    return code;
};

/**
 * 绘制三角形 起点()顶点()顶点()颜色()
 */
Blockly.Arduino.runDrawTriangle = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X1 = Blockly.Arduino.valueToCode(this, 'x1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y1 = Blockly.Arduino.valueToCode(this, 'y1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X2 = Blockly.Arduino.valueToCode(this, 'x2value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y2 = Blockly.Arduino.valueToCode(this, 'y2value', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.drawTriangle(' + TFT_X + ',' + TFT_Y + ',' + TFT_X1 + ',' + TFT_Y1 + ',' + TFT_X2 + ',' + TFT_Y2 + ',' + Color + ');\n';
    return code;
};

/**
 * 填充矩形 起点()尺寸()颜色()
 */
Blockly.Arduino.runFillRect = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X1 = Blockly.Arduino.valueToCode(this, 'x1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y1 = Blockly.Arduino.valueToCode(this, 'y1value', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.fillRect(' + TFT_X + ',' + TFT_Y + ',' + TFT_X1 + ',' + TFT_Y1 + ',' + Color + ');\n';
    return code;
};

/**
 * 填充圆形 起点()半径()颜色()
 */
Blockly.Arduino.runFillCircle = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_R = Blockly.Arduino.valueToCode(this, 'rvalue', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.fillCircle(' + TFT_X + ',' + TFT_Y + ',' + TFT_R + ',' + Color + ');\n';
    return code;
};

/**
 * 填充三角形 起点()顶点()顶点()颜色()
 */
Blockly.Arduino.runFillTriangle = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X1 = Blockly.Arduino.valueToCode(this, 'x1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y1 = Blockly.Arduino.valueToCode(this, 'y1value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_X2 = Blockly.Arduino.valueToCode(this, 'x2value', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y2 = Blockly.Arduino.valueToCode(this, 'y2value', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    var code = 'Screen' + '.fillTriangle(' + TFT_X + ',' + TFT_Y + ',' + TFT_X1 + ',' + TFT_Y1 + ',' + TFT_X2 + ',' + TFT_Y2 + ',' + Color + ');\n';
    return code;
};

/**
 * 显示ASCII字符 起点()字体()颜色()背景色()字符()
 */
Blockly.Arduino.runDrawChar = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var Color_TFT = this.getFieldValue('Background');
    var Color1 = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_S = Blockly.Arduino.valueToCode(this, 'svalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_C = Blockly.Arduino.valueToCode(this, 'cvalue', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    Color1 = ((Number(Color1[0]) & 0xF8) << 8) | ((Number(Color1[1]) & 0xFC) << 3) | (Number(Color1[2]) >> 3);
    var code = 'Screen' + '.drawChar(' + TFT_X + ',' + TFT_Y + ',' + TFT_C + ',' + Color + ',' + Color1 + ',' + TFT_S + ');\n';
    return code;
};

/**
 * 显示字符串 起点()字体()颜色()背景色()字符串()
 */
Blockly.Arduino.runText = function() {
    var Color_TFT = this.getFieldValue('Color');
    var Color = goog.color.hexToRgb(Color_TFT);
    var Color_TFT = this.getFieldValue('Background');
    var Color1 = goog.color.hexToRgb(Color_TFT);
    var TFT_X = Blockly.Arduino.valueToCode(this, 'xvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_Y = Blockly.Arduino.valueToCode(this, 'yvalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_S = Blockly.Arduino.valueToCode(this, 'svalue', Blockly.Arduino.ORDER_ATOMIC);
    var TFT_C = Blockly.Arduino.valueToCode(this, 'cvalue', Blockly.Arduino.ORDER_ATOMIC);
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    Color = ((Number(Color[0]) & 0xF8) << 8) | ((Number(Color[1]) & 0xFC) << 3) | (Number(Color[2]) >> 3);
    Color1 = ((Number(Color1[0]) & 0xF8) << 8) | ((Number(Color1[1]) & 0xFC) << 3) | (Number(Color1[2]) >> 3);
    var code = 'Screen' + '.text(' + TFT_X + ',' + TFT_Y + ',' + TFT_S + ',' + Color + ',' + Color1 + ',' + 'String(' + TFT_C + ')' + ');\n';
    return code;
};

/**
 * 面向
 */
Blockly.Arduino.runSetRotation = function() {

    var Orientation_TFT = this.getFieldValue('Orientation');
    Blockly.Arduino.definitions_['define_arduino'] = '#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_kadapapa'] = '#include "KA_Block.h"';
    Blockly.Arduino.definitions_['define_TFT'] = '#include "KA_TFT.h"';
    Blockly.Arduino.definitions_['var_TFT'] = 'KA_TFT ' + 'Screen;';
    Blockly.Arduino.setups_['setup_TFT'] = 'Screen' + '.begin();\n';
    var code = 'Screen' + '.setRotation(' + Orientation_TFT + ');\n';
    return code;
};

/*<!--==============================END==============================-->*/