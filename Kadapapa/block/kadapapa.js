'use strict';

goog.provide('Blockly.Blocks.kadapapa');

goog.require('Blockly.Blocks');

Blockly.Blocks.kadapapa.HUE = "#DB4288";

var KADAPAPA_PORTS = [
    [Blockly.MIXLY_KADAPAPA_PORT1, "1"],
    [Blockly.MIXLY_KADAPAPA_PORT2, "2"],
    [Blockly.MIXLY_KADAPAPA_PORT3, "3"],
    [Blockly.MIXLY_KADAPAPA_PORT4, "4"],
    [Blockly.MIXLY_KADAPAPA_PORT5, "5"],
    [Blockly.MIXLY_KADAPAPA_PORT6, "6"]

];

var KADAPAPA_RGB_INDEXS = [
    [Blockly.MIXLY_KADAPAPA_ALL, "0"],
    [Blockly.MIXLY_KADAPAPA_FIRST, "1"],
    [Blockly.MIXLY_KADAPAPA_SECOND, "2"],
    [Blockly.MIXLY_KADAPAPA_THIRD, "3"],
    [Blockly.MIXLY_KADAPAPA_FOURTH, "4"],
    [Blockly.MIXLY_KADAPAPA_FIFTH, "5"],
    [Blockly.MIXLY_KADAPAPA_SIXTH, "6"],
    [Blockly.MIXLY_KADAPAPA_SEVENTH, "7"],
    [Blockly.MIXLY_KADAPAPA_EIGHTH, "8"]
];

var KADAPAPA_PORTS_MOTOR = [
    [Blockly.MIXLY_KADAPAPA_PORT7, "7"],
    [Blockly.MIXLY_KADAPAPA_PORT8, "8"]
];

var KADAPAPA_TFT_ORIENTATION = [
    [Blockly.MIXLY_KADAPAPA_DIGITRON_UPWARD, "1"],
    [Blockly.MIXLY_KADAPAPA_DIGITRON_DOWNWARD, "3"],
    [Blockly.MIXLY_KADAPAPA_DIGITRON_LEFT, "4"],
    [Blockly.MIXLY_KADAPAPA_DIGITRON_RIGHT, "2"]
];

var KADAPAPA_TFT_CORRDS = {
    xvalue: [
        ["3", "3"],
        ["15", "15"],
        ["27", "27"],
        ["39", "39"],
        ["51", "51"],
        ["63", "63"],
        ["75", "75"],
        ["87", "87"],
        ["99", "99"],
        ["111", "111"],
        ["123", "123"],
    ],
    yvalue: [
        ["2", "2"],
        ["18", "18"],
        ["34", "34"],
        ["50", "50"],
        ["66", "66"],
        ["82", "82"],
        ["98", "98"],
        ["114", "114"],
    ],
};

var KADAPAPA_BUZZER_PARAMETER = {
    tones: [
        ["B0", '31'],
        ["C1", '33'],
        ["D1", '37'],
        ["E1", '41'],
        ["F1", '44'],
        ["G1", '49'],
        ["A1", '55'],
        ["B1", '62'],
        ["C2", '65'],
        ["D2", '73'],
        ["E2", '82'],
        ["F2", '87'],
        ["G2", '98'],
        ["A2", '110'],
        ["B2", '123'],
        ["C3", '131'],
        ["D3", '147'],
        ["E3", '165'],
        ["F3", '175'],
        ["G3", '196'],
        ["A3", '220'],
        ["B3", '247'],
        ["C4", '262'],
        ["D4", '294'],
        ["E4", '330'],
        ["F4", '349'],
        ["G4", '392'],
        ["A4", '440'],
        ["B4", '494'],
        ["C5", '523'],
        ["D5", '587'],
        ["E5", '659'],
        ["F5", '698'],
        ["G5", '784'],
        ["A5", '880'],
        ["B5", '988'],
        ["C6", '1047'],
        ["D6", '1175'],
        ["E6", '1319'],
        ["F6", '1397'],
        ["G6", '1568'],
        ["A6", '1760'],
        ["B6", '1976'],
        ["C7", '2093'],
        ["D7", '2349'],
        ["E7", '2637'],
        ["F7", '2794'],
        ["G7", '3136'],
        ["A7", '3520'],
        ["B7", '3951'],
        ["C8", '4186'],
        ["D8", '4699'],
    ],
    beats: [
        [Blockly.MIXLY_KADAPAPA_BUZZER_BEAT_HALF, '500'],
        [Blockly.MIXLY_KADAPAPA_BUZZER_BEAT_QUATER, '250'],
        [Blockly.MIXLY_KADAPAPA_BUZZER_BEAT_EIGHTH, '125'],
        [Blockly.MIXLY_KADAPAPA_BUZZER_BEAT_WHOLE, '1000'],
        [Blockly.MIXLY_KADAPAPA_BUZZER_BEAT_DOUBLE, '2000'],
        [Blockly.MIXLY_KADAPAPA_BUZZER_BEAT_ZERO, '0'],
    ],
};

Blockly.Blocks['TFT_Coords_X'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
            .appendField(new Blockly.FieldDropdown(KADAPAPA_TFT_CORRDS.xvalue), 'X_Coords');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['TFT_Coords_Y'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
            .appendField(new Blockly.FieldDropdown(KADAPAPA_TFT_CORRDS.yvalue), 'Y_Coords');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['Buzzer_Tones'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
            .appendField(new Blockly.FieldDropdown(KADAPAPA_BUZZER_PARAMETER.tones), 'Tones');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['Buzzer_Beats'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
            .appendField(new Blockly.FieldDropdown(KADAPAPA_BUZZER_PARAMETER.beats), 'Beats');
        this.setOutput(true, Number);
    }
};

Blockly.Arduino.TFT_Coords_X = function() {
    var code = this.getFieldValue('X_Coords');
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.TFT_Coords_Y = function() {
    var code = this.getFieldValue('Y_Coords');
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.Buzzer_Tones = function() {
    var code = this.getFieldValue('Tones');
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.Buzzer_Beats = function() {
    var code = this.getFieldValue('Beats');
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};


/*<!--==============================Output==============================-->*/

/**
 * 设置(接口)数字输出(低电平)
 */
Blockly.Blocks.runWdigital = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT") //"接口"
            //.appendTitle(new Blockly.FieldImage("../../media/kadapapa/Led_R.png", 200, 40)) //添加图片，最后的值为模块的长、宽
            .appendTitle(Blockly.MIXLY_KADAPAPA_DIGITAL + Blockly.MIXLY_KADAPAPA_OUTPUT) //"数字+输出"
            .appendField(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_HIGH, "HIGH"],
                [Blockly.MIXLY_KADAPAPA_LOW, "LOW"]
            ]), 'Wdigital'); //"状态实例"
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 设置(接口)PWM输出(0)
 */
Blockly.Blocks.runPwm = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("true")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT") //"接口"
            .appendTitle(Blockly.MIXLY_KADAPAPA_PWM + Blockly.MIXLY_KADAPAPA_OUTPUT) //"PWM输出"
        this.appendValueInput("Pwm", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('');
    }
};

/**
 * 设置(接口)LED状态为(关)
 */
Blockly.Blocks.runLed = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("true")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(Blockly.MIXLY_KADAPAPA_LED)
            .appendTitle(new Blockly.FieldImage("../../media/kadapapa/Led_R.png", 40, 40))
            .appendTitle(Blockly.MIXLY_KADAPAPA_STATE)
            .appendTitle(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_ON, "HIGH"],
                [Blockly.MIXLY_KADAPAPA_OFF, "LOW"]
            ]), 'Led'); //"状态实例"
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

/**
 * 设置(接口)振动器状态(关)
 */
Blockly.Blocks.runVibrator = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("true")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VIBRATOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Vibrator.png", 40, 40))
            .appendTitle(Blockly.MIXLY_KADAPAPA_STATE)
            .appendField(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_ON, "HIGH"],
                [Blockly.MIXLY_KADAPAPA_OFF, "LOW"]
            ]), 'Vibrator'); //"状态实例"
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

/**
 * 设置(接口)数码管显示(0)
 */
Blockly.Blocks.runDigition = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("true")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DIGITION)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Digition.png", 40, 40));
        this.appendValueInput("num", Number)
            .setCheck(Number)
            //.setAlign(Blockly.ALIGN_LEFT) //居左 (默认)             
            //.setAlign(Blockly.ALIGN_CENTRE) //居中
            .setAlign(Blockly.ALIGN_RIGHT) //居右
            .appendTitle(Blockly.MIXLY_KADAPAPA_DISPALY);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('');
    }
};

/**
 * 设置(接口)RGB(全部)颜色(无)
 */
Blockly.Blocks.runRGB = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(Blockly.MIXLY_KADAPAPA_RGB)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/RGB.png", 40, 40));
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_RGB_INDEXS), "RGB_Indexs");
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#ff0000"), "RGBcolor");
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setInputsInline(true);
    }
};

/**
 * 设置(接口)舵机角度为(0)
 */
Blockly.Blocks.runServo = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("true")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SERVO)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Servo.png", 40, 40))
        this.appendValueInput("Angle", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_ANGLE);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('');
    }
};

/**
 * 设置(接口)电机转速为(0)
 */
Blockly.Blocks.runMotor = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SET) //"设置"
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS_MOTOR), "PORT")
            .appendTitle(Blockly.MIXLY_KADAPAPA_MOTOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Motor.png", 40, 40));
        this.appendValueInput('Speed', Number)
            .setCheck(Number)
            .appendTitle(Blockly.MIXLY_KADAPAPA_SPEED);
        this.setPreviousStatement(true);
        this.setNextStatement(true);
        this.setInputsInline(true);
    }
};

/**
 * 播放蜂鸣器音调为()节拍为()
 */
Blockly.Blocks.runBuzzer = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("true")
            .appendTitle(Blockly.MIXLY_KADAPAPA_PLAY + Blockly.MIXLY_KADAPAPA_BUZZER)
            //            .appendField(new Blockly.FieldImage("../../media/kadapapa/Buzzer.jpg", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
        this.appendValueInput("Tonality", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_TONALITY);
        this.appendValueInput("Beat", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_BEAT);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

/*<!--==============================Analog Input==============================-->*/

/**
 * 读取(接口)模拟量
 */
Blockly.Blocks.getAnalog = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_READ + Blockly.MIXLY_KADAPAPA_ANALOG + Blockly.MIXLY_KADAPAPA_QUANTITY)
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 光线传感器(接口1)
 */
Blockly.Blocks.getLightSensor = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_LIGHT + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/LightSensor.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 声音传感器(接口1)
 */
Blockly.Blocks.getSoundSensor = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SOUND + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/SoundSensor.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 震动传感器(接口1)
 */
Blockly.Blocks.getShake = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SHAKE + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Shake.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 压力传感器(接口1)
 */
Blockly.Blocks.getPressure = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_PRESSURE + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Pressure.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 气体传感器(接口1)
 */
/*
Blockly.Blocks.getGasSensor = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_GAS + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/GasSensor.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/
/**
 * 火焰传感器(接口1)
 */
Blockly.Blocks.getFlameSensor = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_FLAME + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/FlameSensor.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * TVOC传感器(接口1)
 */
/*
Blockly.Blocks.getTVOCSensor = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_TVOC + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/TVOCSensor.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/**
 * 温度传感器(接口1)
 */
Blockly.Blocks.getTemperature = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_TEMPERATURE + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Temperature.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 湿度传感器(接口1)
 */
Blockly.Blocks.getHumidity = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_LIGHT + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Humidity.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 温湿度传感器(接口1)
 */
Blockly.Blocks.getHumiture = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_HUMITURE + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Humiture.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_TEMPERATURE, "2"],
                [Blockly.MIXLY_KADAPAPA_HUMIDITY, "1"]
            ]), "Humiture");
        this.setOutput(true, Number);
    }
};

/**
 * 超声波传感器(接口1)
 */
Blockly.Blocks.getUltrasonic = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ULTRASONIC + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Ultrasonic.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 红外接收传感器(接口1)
 */
/*
Blockly.Blocks.getInfrared = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_LIGHT + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_sound.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/**
 * 陀螺仪(轴)(角度)
 */
Blockly.Blocks.getGyro = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_GYRO + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Gyro.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_AXIS_X, "1"],
                [Blockly.MIXLY_KADAPAPA_AXIS_Y, "2"],
                [Blockly.MIXLY_KADAPAPA_AXIS_Z, "3"]
            ]), "AXIS");
        this.setOutput(true, Number);
    }
};

/**
 * PM2.5传感器(接口1)
 */
/*
Blockly.Blocks.getPM25 = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_PM25 + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/PM25.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/**
 * 空气检测传感器(接口1)
 */
/*
Blockly.Blocks.getAirMonitors = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_AIR + Blockly.MIXLY_KADAPAPA_MONITORS + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/AirMonitors.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/**
 * CO2传感器(接口1)
 */
/*
Blockly.Blocks.getCo2 = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_CO2 + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Co2.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/**
 * 计时器
 */
/*
Blockly.Blocks.getTimer = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_LIGHT + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_sound.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/
/*<!--==============================Digital Input==============================-->*/

/**
 * 读取(接口)数字量
 */
Blockly.Blocks.getDigital = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_READ + Blockly.MIXLY_KADAPAPA_DIGITAL + Blockly.MIXLY_KADAPAPA_QUANTITY)
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 红外收发传感器(接口1)
 */
Blockly.Blocks.getLinefollower = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_INFRARED + Blockly.MIXLY_KADAPAPA_TRANSMIT_RECEIVE + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Linefollower.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 微动开关(接口1)
 */
Blockly.Blocks.getLimitswitch = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_INCHING + Blockly.MIXLY_KADAPAPA_SWITCH)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Limitswitch.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 带灯按键(接口1)
 */
Blockly.Blocks.getButtonswitch = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_OWN_LIGHT + Blockly.MIXLY_KADAPAPA_KEY)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Buttonswitch.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 自锁按键(接口1)
 */
Blockly.Blocks.getSelfholdswitch = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SELF_HOLD + Blockly.MIXLY_KADAPAPA_KEY)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Selfholdswitch.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 人体热释电传感器(接口1)
 */
Blockly.Blocks.getPirmotion = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_HUMAN_PYROELECTRIC + Blockly.MIXLY_KADAPAPA_SENSOR)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Pirmotion.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};

/**
 * 数码管按键按下(接口1)
 */
Blockly.Blocks.getFourkey = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DIGITION + Blockly.MIXLY_KADAPAPA_KEY)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Digition.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY1, "68"],
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY2, "76"],
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY3, "84"],
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY4, "92"]
            ]), "KEY");
        this.setOutput(true, Number);
    }
};

/**
 * 红外遥控按下(接口1)
 */
/*
Blockly.Blocks.getIrRemote = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_TOUCH + Blockly.MIXLY_KADAPAPA_KEY)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_sound.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/**
 * 触摸按键按下(接口1)
 */
Blockly.Blocks.getTouchkey = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_TOUCH + Blockly.MIXLY_KADAPAPA_KEY)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/Touchkey.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
            .appendTitle(new Blockly.FieldDropdown([
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY1, "68"],
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY2, "76"],
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY3, "84"],
                [Blockly.MIXLY_KADAPAPA_DIGITRON_KEY4, "92"]
            ]), "KEY");
        this.setOutput(true, Number);
    }
};

/**
 * RFID卡片动作是(接口1)
 */
/*
Blockly.Blocks.getRFID = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE);
        this.appendDummyInput("false")
            .appendTitle(Blockly.MIXLY_KADAPAPA_CARD + Blockly.MIXLY_KADAPAPA_ACTION)
            .appendField(new Blockly.FieldImage("../../media/kadapapa/RFID.png", 40, 40))
            .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
        this.setOutput(true, Number);
    }
};
*/

/*<!--==============================TFT Screen==============================-->*/

/**
 * 设置整屏颜色为()
 */
Blockly.Blocks.runFillScreen = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_WHOLE_SCREEN + Blockly.MIXLY_KADAPAPA_DISPALY) //"设置"
            //            .appendField(new Blockly.FieldImage("../../media/kadapapa/jupiter.png", 40, 40))
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 绘制线段 起点()终点()颜色()
 */
Blockly.Blocks.runDrawLine = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DRAW + Blockly.MIXLY_KADAPAPA_LINE); //绘制线段
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DESTINATION) //终点
        this.appendValueInput("x1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            //           .appendField(new Blockly.FieldImage("../../media/kadapapa/jupiter.png", 40, 40))
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 绘制矩形 起点()尺寸()颜色()
 */
Blockly.Blocks.runDrawRect = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DRAW + Blockly.MIXLY_KADAPAPA_RECT); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SIZE) //终点
        this.appendValueInput("x1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            //           .appendField(new Blockly.FieldImage("../../media/kadapapa/jupiter.png", 40, 40))
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 绘制圆形 起点()半径()颜色()
 */
Blockly.Blocks.runDrawCircle = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DRAW + Blockly.MIXLY_KADAPAPA_CIRCLE); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_RADIUS) //终点
        this.appendValueInput("rvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('R');
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 绘制三角形 起点()顶点()顶点()颜色()
 */
Blockly.Blocks.runDrawTriangle = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DRAW + Blockly.MIXLY_KADAPAPA_TRIANGLE); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //终点
        this.appendValueInput("x1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //终点
        this.appendValueInput("x2value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y2value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 填充矩形 起点()尺寸()颜色()
 */
Blockly.Blocks.runFillRect = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_FILL + Blockly.MIXLY_KADAPAPA_RECT); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_SIZE) //终点
        this.appendValueInput("x1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            //           .appendField(new Blockly.FieldImage("../../media/kadapapa/jupiter.png", 40, 40))
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 填充圆形 起点()半径()颜色()
 */
Blockly.Blocks.runFillCircle = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_FILL + Blockly.MIXLY_KADAPAPA_CIRCLE); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_RADIUS) //终点
        this.appendValueInput("rvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('R');
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 填充三角形 起点()顶点()顶点()颜色()
 */
Blockly.Blocks.runFillTriangle = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_FILL + Blockly.MIXLY_KADAPAPA_TRIANGLE); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //终点
        this.appendValueInput("x1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y1value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //终点
        this.appendValueInput("x2value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("y2value", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 显示ASCII字符 起点()字体()颜色()背景色()字符()
 */
Blockly.Blocks.runDrawChar = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DISPALY + Blockly.MIXLY_KADAPAPA_ASCII + Blockly.MIXLY_KADAPAPA_CHAR); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendValueInput("svalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_TYPESIZE);
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_BACKGROUND)
            .appendField(new Blockly.FieldColour("#000000"), "Background");
        this.appendValueInput("cvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_CHAR);
        // this.appendDummyInput("")
        //     .appendTitle(Blockly.MIXLY_KADAPAPA_VERTEX) //终点
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 显示字符串 起点()字体()颜色()背景色()字符串()
 */
Blockly.Blocks.runText = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_DISPALY + Blockly.MIXLY_KADAPAPA_STRING); //绘制juxing
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_ORIGIN) //起点
        this.appendValueInput("xvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('X');
        this.appendValueInput("yvalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle('Y');
        this.appendValueInput("svalue", Number)
            .setCheck(Number)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_TYPESIZE);
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_COLOUR)
            .appendField(new Blockly.FieldColour("#FF0000"), "Color");
        this.appendDummyInput("")
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_BACKGROUND)
            .appendField(new Blockly.FieldColour("#000000"), "Background");
        this.appendValueInput("cvalue", String)
            .setCheck(String)
            .setAlign(Blockly.ALIGN_RIGHT)
            .appendTitle(Blockly.MIXLY_KADAPAPA_STRING);
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setInputsInline(true); //模块集成一行，输入在模块内部
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};

/**
 * 面向
 */
Blockly.Blocks.runSetRotation = {
    init: function() {
        this.setColour(Blockly.Blocks.kadapapa.HUE); //设置模块颜色
        this.appendDummyInput("")
            .appendTitle(Blockly.MIXLY_KADAPAPA_FACE) //"设置"
            .appendField(new Blockly.FieldDropdown(KADAPAPA_TFT_ORIENTATION), 'Orientation'); //"状态实例"
        this.setPreviousStatement(true, null); //是否有上面三角
        this.setNextStatement(true, null); //是否有下三角
        this.setTooltip('hello world'); //鼠标停留在模块上显示的内容
    }
};




/*

Blockly.Blocks.mb_temperature = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_TEMPERATURE)
		.appendField(new Blockly.FieldImage("../../media/kadapapa/mb_temperature.png", 59, 32))
		.appendTitle("#")
        .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
		.appendTitle("#")
        .appendTitle(new Blockly.FieldDropdown(MAKEBLOCK_SLOTS), "PIN2");
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};

Blockly.Blocks.mb_joystick = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_JOYSTICK)
		.appendTitle(new Blockly.FieldDropdown([["x", "X"], ["y", "Y"]]), "STAT")
		.appendField(new Blockly.FieldImage("../../media/kadapapa/mb_joystick.png", 38, 32))
		.appendTitle("#")
        .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};

Blockly.Blocks.mb_potentiometer = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_POTENTIOMETER)
		.appendField(new Blockly.FieldImage("../../media/kadapapa/mb_potentiometer.png", 40, 32))
		.appendTitle("#")
        .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
    this.setOutput(true, Number);
  }
};

Blockly.Blocks.mb_pyroelectric_infrared = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
	      .appendTitle(Blockly.MIXLY_MB_PYROELECTRIC_INFRARED)
		  .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_pir_motion.png", 42, 32))
		  .appendTitle("#")
	      .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
    this.setOutput(true, Boolean);
  }
};

Blockly.Blocks.mb_chaoshengbo = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
	      .appendTitle(Blockly.MIXLY_MB_CHAOSHENGBO)
		  .appendTitle(new Blockly.FieldDropdown(MAKEBLOCK_UNIT), "PIN2")
		  .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_ultrasonic.png", 37, 32))
		  .appendTitle("#")
	      .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
    this.setOutput(true, Number);
  }
};

Blockly.Blocks.mb_light_grayscale = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
	      .appendTitle(Blockly.MIXLY_MB_LIGHT_GRAYSCALE)
		  .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_light_grayscale.png", 35, 32))
		  .appendTitle("#")
	      .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT");
    this.setOutput(true, Number);
  }
};

Blockly.Blocks.mb_light_grayscale_led = {
  init: function() {
    this.setColour(Blockly.Blocks.kadapapa.HUE);
    this.appendDummyInput("")
	      .appendTitle(Blockly.MIXLY_MB_LIGHT_GRAYSCALE)
		  .appendField(new Blockly.FieldImage("../../media/kadapapa/mb_light_grayscale.png", 35, 32))
		  .appendTitle("#")
	      .appendTitle(new Blockly.FieldDropdown(KADAPAPA_PORTS), "PORT")
		  .appendTitle(Blockly.MIXLY_MB_LIGHT_GRAYSCALE_LED)
		  .appendTitle(new Blockly.FieldDropdown([[Blockly.MIXLY_ON, "lightOn"], [Blockly.MIXLY_OFF, "lightOff"]]), "STAT");
    this.setPreviousStatement(true);
    this.setNextStatement(true);
  }
};


Blockly.Arduino.inout_pinMode = function() {
  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_mode = this.getFieldValue('MODE');
  var code = 'pinMode('+dropdown_pin+', '+dropdown_mode+');\n';
  return code;
};


Blockly.Arduino.inout_digital_write2 = function() {
  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_stat = Blockly.Arduino.valueToCode(this, 'STAT', Blockly.Arduino.ORDER_ATOMIC);
  var code = "";
  if(window.isNaN(dropdown_pin)){
      code = code+'pinMode('+dropdown_pin+', OUTPUT);\n';
  } else {
      if (Blockly.Arduino.setups_['setup_input_' + dropdown_pin]) 
          delete Blockly.Arduino.setups_['setup_input_' + dropdown_pin];
       Blockly.Arduino.setups_['setup_output_' + dropdown_pin] = 'pinMode(' + dropdown_pin + ', OUTPUT);';
   
  }
  code += 'digitalWrite('+dropdown_pin+','+dropdown_stat+');\n'
  return code;
};

Blockly.Arduino.inout_digital_read = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code = 'digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.inout_digital_read2 = function() {
  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
  var code = "";
  if(window.isNaN(dropdown_pin)&&!(new RegExp("^A([0-9]|10|11|12|13|14|15)$").test(dropdown_pin))){
	var funcName='mixly_digitalRead';
	var code2='int'+ ' ' + funcName + '(uint8_t pin) {\n' 
	+ '  pinMode(pin, INPUT);\n'
	+ '  return digitalRead(pin);\n'
	+ '}\n';
    Blockly.Arduino.definitions_[funcName] = code2;
	code = 'mixly_digitalRead('+dropdown_pin+')';
  }else{
    if(Blockly.Arduino.setups_['setup_output_'+dropdown_pin]){
	   //存在pinMode已设为output则不再设为input
	}else{
       Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
	}
	code = 'digitalRead('+dropdown_pin+')';
  }
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.inout_analog_write = function() {
  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
  //var dropdown_stat = this.getFieldValue('STAT');
  var value_num = Blockly.Arduino.valueToCode(this, 'NUM', Blockly.Arduino.ORDER_ATOMIC);
  //Blockly.Arduino.setups_['setup_output'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
  var code = 'analogWrite('+dropdown_pin+','+value_num+');\n';
  return code;
};

Blockly.Arduino.inout_analog_read = function() {
  var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
  //Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code = 'analogRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.inout_buildin_led = function() {
  var dropdown_stat = this.getFieldValue('STAT');
  Blockly.Arduino.setups_['setup_output_13'] = 'pinMode(13, OUTPUT);';
  var code = 'digitalWrite(13,'+dropdown_stat+');\n'
  return code;
};




*/