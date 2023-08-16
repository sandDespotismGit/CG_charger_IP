#include <stdint.h>

#if defined(ARDUINO)
#include <Arduino.h>
#include <Wire.h>
#endif


// Default charger_ip i2c device address
#define DEFAULT_I2C_ADDRESS 0xEA

#define SYS_CTL0 0x00
#define SYS_CTL1 0x01
#define SYS_CTL2 0x02
#define Charger_CTL0 0x20
#define Charger_CTL1 0x21
#define Charger_CTL2 0x22
#define Charger_CTL3 0x23
#define CHG_DIG_CTL0 0x24
#define REG_READ0 0x70
#define EG_READ1 0x71
#define EG_READ2 0x72
#define EG_READ3 0x77

class CG_Charger_Ip
{
private:
    uint8_t _charger_addr;

public:
    ~CG_Charger_Ip();
    bool init();
    bool setConverter(uint8_t state);
    bool setCharging(uint8_t state);
    bool autoEnableifPower(uint8_t state);
    bool setButtonTurnOff(uint8_t state);
    bool setBOOSTenabled(uint8_t state);
    bool chooseBOOSTcontrol(uint8_t state);
    bool shortPressBoost(uint8_t state);
    bool turnOffIfBatLow(uint8_t state);
    bool chooseLongPressButTime(uint8_t state);
    bool chooseAutoOffTime(uint8_t state);
    bool stopChargingLevel(uint8_t state);
    bool chooseVCCbatLevel(uint8_t state);
    bool chooseDCchargeIn(uint8_t state);
    bool isChargingOn();
    bool isFullyCharge();
    bool isLightPower();
    bool doublePressKey();
    bool longPressKey();
    bool shortPressKey();
    bool register_read_byte(uint8_t regAddr, uint8_t *retrieveData);
    bool register_write_byte(uint8_t regAddr, uint8_t regData);
};

