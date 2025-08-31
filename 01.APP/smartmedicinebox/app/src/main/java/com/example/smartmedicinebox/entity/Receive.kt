package com.example.smartmedicinebox.entity

data class Receive(
    var heart: String? = null,// 心率
    var blood: String? = null, // 血氧
    var temp: String? = null,// 人体温度
    var temp_b: String? = null,// 人体温度
    var humi_b: String? = null,// 人体温度
    var waning: String? = null,// 报警状态
    var drug1_s: String? = null,// 箱1 开关状态
    var drug2_s: String? = null,// 箱2
    var drug3_s: String? = null,// 箱3
    var drug1: String? = null,// 箱1 数量
    var drug2: String? = null,// 箱2
    var drug3: String? = null, // 箱3
    var drug: String? = null // 使用药品
)
