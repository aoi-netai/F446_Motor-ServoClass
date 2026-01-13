#include "wrapper.hpp"
#include "servo.hpp"
#include "tim.h"
#include <stdio.h>

// グローバルサーボインスタンス
Servo servo1;

void init(){
	printf("=== Servo Control Initialize ===\n");
	
	// サーボ1をTIM1のチャネル1に設定
	servo1.setTimer(&htim1, TIM_CHANNEL_1);
	
	// サーボの最小・最大パルス幅を設定（オプション）
	// デフォルト: 1000us(1ms) ~ 2000us(2ms)
	servo1.setMinMaxPulseWidth(1000, 2000);
	
	// PWM開始
	servo1.start();
	
	printf("Servo initialized on TIM1 CH1\n");
	
	HAL_Delay(1000);
}

// サーボ角度制御用の状態変数
static int servo_direction = 1;  // 1: 増加, -1: 減少
static float servo_angle = 0.0f;

void loop(){
	// 角度を -90 ~ +90 の範囲でスイープ
	servo_angle += servo_direction * 5.0f;
	
	// 範囲チェック
	if (servo_angle >= 90.0f) {
		servo_angle = 90.0f;
		servo_direction = -1;
	} else if (servo_angle <= -90.0f) {
		servo_angle = -90.0f;
		servo_direction = 1;
	}
	
	// サーボに角度を設定
	servo1.setAngle(servo_angle);
	
	printf("Servo Angle: %.1f°, Pulse Width: %lu us\n", 
		   servo1.getAngle(), servo1.getPulseWidth());
	
	HAL_Delay(100);  // 100ms間隔で更新
}
