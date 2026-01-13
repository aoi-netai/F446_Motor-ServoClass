#include "servo.hpp"

Servo::Servo()
    : PWMDevice(),
      _angle(0.0f),
      _minPulseWidth(1000),   // 1ms
      _maxPulseWidth(2000),   // 2ms
      _minAngle(-90.0f),
      _maxAngle(90.0f)
{
}

Servo::~Servo()
{
}

void Servo::setAngle(float angle)
{
    // 角度の範囲チェック
    if (angle < _minAngle) {
        angle = _minAngle;
    } else if (angle > _maxAngle) {
        angle = _maxAngle;
    }

    _angle = angle;

    // 角度をパルス幅に変換して設定
    uint32_t pulseWidth = angleToParseWidth(angle);
    setPulseWidth(pulseWidth);
}

float Servo::getAngle() const
{
    return _angle;
}

void Servo::setPulseWidth(uint32_t pulseWidth_us)
{
    // パルス幅の範囲チェック
    if (pulseWidth_us < _minPulseWidth) {
        pulseWidth_us = _minPulseWidth;
    } else if (pulseWidth_us > _maxPulseWidth) {
        pulseWidth_us = _maxPulseWidth;
    }

    _pulseWidth_us = pulseWidth_us;

    if (_htim != nullptr) {
        uint32_t ccr = convertPulseWidthToCCR(pulseWidth_us);
        __HAL_TIM_SET_COMPARE(_htim, _channel, ccr);
    }
}

void Servo::setMinMaxPulseWidth(uint32_t min_us, uint32_t max_us)
{
    if (min_us < max_us) {
        _minPulseWidth = min_us;
        _maxPulseWidth = max_us;
    }
}

uint32_t Servo::angleToParseWidth(float angle) const
{
    // 角度範囲から0～1に正規化
    float normalized = (angle - _minAngle) / (_maxAngle - _minAngle);

    // 正規化された値をパルス幅に変換
    // パルス幅 = min + normalized * (max - min)
    uint32_t pulseWidth = _minPulseWidth + 
                         (uint32_t)(normalized * (_maxPulseWidth - _minPulseWidth));

    return pulseWidth;
}
