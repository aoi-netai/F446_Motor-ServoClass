#include "pwm_device.hpp"

PWMDevice::PWMDevice()
    : _htim(nullptr), _channel(0), _pulseWidth_us(0), _period_us(0), _resolution(0)
{
}

PWMDevice::~PWMDevice()
{
}

void PWMDevice::setTimer(TIM_HandleTypeDef *htim, uint32_t channel)
{
    _htim = htim;
    _channel = channel;

    if (_htim != nullptr) {
        // タイマー周期からPWM周期を計算（マイクロ秒）
        uint32_t timerClk = HAL_RCC_GetSysClockFreq();
        uint32_t prescaler = _htim->Init.Prescaler + 1;
        uint32_t period = _htim->Init.Period + 1;

        // 周期 = (period * prescaler) / timerClk （秒）
        // 周期（マイクロ秒） = (period * prescaler * 1000000) / timerClk
        _period_us = (period * prescaler * 1000000) / timerClk;
        _resolution = _period_us / (period);
    }
}

void PWMDevice::start()
{
    if (_htim != nullptr) {
        HAL_TIM_PWM_Start(_htim, _channel);
    }
}

void PWMDevice::stop()
{
    if (_htim != nullptr) {
        HAL_TIM_PWM_Stop(_htim, _channel);
    }
}

uint32_t PWMDevice::getPulseWidth() const
{
    return _pulseWidth_us;
}

uint32_t PWMDevice::getPeriod() const
{
    return _period_us;
}

uint32_t PWMDevice::getResolution() const
{
    return _resolution;
}

uint32_t PWMDevice::convertPulseWidthToCCR(uint32_t pulseWidth_us) const
{
    if (_resolution == 0) return 0;

    // CCR値 = (pulseWidth_us / _period_us) * (Period + 1)
    uint32_t ccr = (pulseWidth_us * (_htim->Init.Period + 1)) / _period_us;

    // 範囲チェック
    if (ccr > _htim->Init.Period) {
        ccr = _htim->Init.Period;
    }

    return ccr;
}
