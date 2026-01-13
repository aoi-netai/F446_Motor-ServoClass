#ifndef INC_PWM_DEVICE_HPP_
#define INC_PWM_DEVICE_HPP_

#include "cstdint"

class PWMDevice {
public:
    PWMDevice();
    virtual ~PWMDevice();

    // ユーザーが操作するpublic API
    void setTimer(TIM_HandleTypeDef *htim, uint32_t channel);
    virtual void start();
    virtual void stop();
    virtual void setPulseWidth(uint32_t pulseWidth_us) = 0;

protected:
    TIM_HandleTypeDef *_htim;
    uint32_t _channel;
    uint32_t _pulseWidth_us;
    uint32_t _period_us;      // PWM周期（マイクロ秒）
    uint32_t _resolution;     // 分解能（マイクロ秒）

    uint32_t convertPulseWidthToCCR(uint32_t pulseWidth_us) const;
};

#endif /* INC_PWM_DEVICE_HPP_ */
