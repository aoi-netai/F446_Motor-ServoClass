#ifndef INC_SERVO_HPP_
#define INC_SERVO_HPP_

#include "pwm_device.hpp"

class Servo : public PWMDevice {
public:
    Servo();
    virtual ~Servo();

    // ユーザーが操作するpublic API
    void setAngle(float angle);
    void setMinMaxPulseWidth(uint32_t min_us, uint32_t max_us);
    float getAngle() const;

    // 基底クラスの純仮想関数を実装
    virtual void setPulseWidth(uint32_t pulseWidth_us) override;

private:

    float _angle;              // 現在の角度
    uint32_t _minPulseWidth;   // 最小パルス幅（デフォルト 1000us = 1ms）
    uint32_t _maxPulseWidth;   // 最大パルス幅（デフォルト 2000us = 2ms）
    float _minAngle;           // 最小角度（デフォルト -90度）
    float _maxAngle;           // 最大角度（デフォルト +90度）

    // 内部用メソッド
    uint32_t angleToParseWidth(float angle) const;
};

#endif /* INC_SERVO_HPP_ */
