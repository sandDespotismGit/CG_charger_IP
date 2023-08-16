#include "cg_charger_ip.h"

// gcc -o test test.cpp radSens1v2.cpp -lwiringPi
CG_Charger_Ip::~CG_Charger_Ip()
{
}

/*Initialization function and sensor connection. Returns false if the sensor is not connected to the I2C bus.*/
bool CG_Charger_Ip::init()
{
    Wire.beginTransmission(DEFAULT_I2C_ADDRESS); // safety check, make sure the sensor is connected
    Wire.write(0x0);
    if (Wire.endTransmission(true) != 0){
        return false;
    } else {
        return true;
    }
}
/*read 1 byte from register*/
bool CG_Charger_Ip::register_read_byte(uint8_t regAddr, uint8_t *retrieveData)
{
    Wire.beginTransmission(DEFAULT_I2C_ADDRESS);
    Wire.write(regAddr);
    Wire.endTransmission(false);

    Wire.requestFrom(DEFAULT_I2C_ADDRESS, 1);
    if (!Wire.readBytes(retrieveData, 1))
    {
        return false;
    }
    return true;
}

/*write 1 byte to register*/
bool CG_Charger_Ip::register_write_byte(uint8_t regAddr, uint8_t regData)
{
    Wire.beginTransmission(DEFAULT_I2C_ADDRESS);
    Wire.write(regAddr);
    Wire.write(regData);
    if (Wire.endTransmission())
    {
        return false;
    }
    return true;
}
bool CG_Charger_Ip::setConverter(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL0, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL0, bitSet(reg_data, 5));
        }
        else if  ( state == 0){
            exec_status = register_write_byte(SYS_CTL0, bitClear(reg_data, 5));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::setCharging(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL0, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL0, bitSet(reg_data, 4));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL0, bitClear(reg_data, 4));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::autoEnableifPower(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL0, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL0, bitSet(reg_data, 2));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL0, bitClear(reg_data, 2));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::setButtonTurnOff(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL0, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL0, bitSet(reg_data, 0));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL0, bitClear(reg_data, 0));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::setBOOSTenabled(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL0, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL0, bitSet(reg_data, 1));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL0, bitClear(reg_data, 1));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::chooseBOOSTcontrol(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL1, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL1, bitSet(reg_data, 7));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL1, bitClear(reg_data, 7));
        }
    }
    return exec_status; 
}
bool CG_Charger_Ip::shortPressBoost(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL1, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL1, bitSet(reg_data, 5));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL1, bitClear(reg_data, 5));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::turnOffIfBatLow(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL1, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL1, bitSet(reg_data, 0));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL1, bitClear(reg_data, 0));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::chooseLongPressButTime(uint8_t state ){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL2, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(SYS_CTL2, bitSet(reg_data, 4));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL2, bitClear(reg_data, 4));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::chooseAutoOffTime(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(SYS_CTL2, &reg_data)){
        if (state == 3){
            exec_status = register_write_byte(SYS_CTL2, bitSet(bitSet(reg_data, 3), 2));
        }
        else if (state == 2){
            exec_status = register_write_byte(SYS_CTL2, bitClear(bitSet(reg_data, 3), 2));
        }
        else if (state == 1){
            exec_status = register_write_byte(SYS_CTL2, bitSet(bitClear(reg_data, 3), 2));
        }
        else if(state == 0){
            exec_status = register_write_byte(SYS_CTL2, bitClear(bitClear(reg_data, 3), 2));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::stopChargingLevel(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(Charger_CTL0, &reg_data)){
        if (state == 3){
            exec_status = register_write_byte(Charger_CTL0, bitSet(bitSet(reg_data, 1), 0));
        }
        else if (state == 2){
            exec_status = register_write_byte(Charger_CTL0, bitClear(bitSet(reg_data, 1), 0));
        }
        else if (state == 1){
            exec_status = register_write_byte(Charger_CTL0, bitSet(bitClear(reg_data, 1), 0));
        }
        else if(state == 0){
            exec_status = register_write_byte(Charger_CTL0, bitClear(bitClear(reg_data, 1), 0));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::chooseVCCbatLevel(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(Charger_CTL2, &reg_data)){
        if (state == 3){
            exec_status = register_write_byte(Charger_CTL2, bitSet(bitSet(reg_data, 3), 2));
        }
        else if (state == 2){
            exec_status = register_write_byte(Charger_CTL2, bitClear(bitSet(reg_data, 3), 2));
        }
        else if (state == 1){
            exec_status = register_write_byte(Charger_CTL2, bitSet(bitClear(reg_data, 3), 2));
        }
        else if(state == 0){
            exec_status = register_write_byte(Charger_CTL2, bitClear(bitClear(reg_data, 3), 2));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::chooseDCchargeIn(uint8_t state){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(Charger_CTL3, &reg_data)){
        if (state == 1){
            exec_status = register_write_byte(Charger_CTL3, bitSet(reg_data, 5));
        }
        else if(state == 0){
            exec_status = register_write_byte(Charger_CTL3, bitClear(reg_data, 5));
        }
    }
    return exec_status;
}
bool CG_Charger_Ip::isChargingOn(){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(REG_READ0, &reg_data)){
        return (bool)bitRead(reg_data, 3);
    }
    return exec_status;
}
bool CG_Charger_Ip::isFullyCharge(){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(EG_READ1, &reg_data)){
        return (bool)bitRead(reg_data, 3);
    }
    return exec_status;
}
bool CG_Charger_Ip::isLightPower(){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(EG_READ2, &reg_data)){
        return (bool)bitRead(reg_data, 2);
    }
    return exec_status;
}
bool CG_Charger_Ip::doublePressKey(){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(EG_READ3, &reg_data)){
        return (bool)bitRead(reg_data, 2);
    }
    return exec_status;
}
bool CG_Charger_Ip::longPressKey(){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(EG_READ3, &reg_data)){
        return (bool)bitRead(reg_data, 1);
    }
    return exec_status;
}
bool CG_Charger_Ip::shortPressKey(){
    uint8_t reg_data;
    bool exec_status = false;
    if (register_read_byte(EG_READ3, &reg_data)){
        return (bool)bitRead(reg_data, 0);
    }
    return exec_status;
}
