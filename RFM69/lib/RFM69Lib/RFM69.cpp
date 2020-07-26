#include "RFM69.h"

namespace RFM69Radio {

//! Sets the given Address to Write access for the RFM69. Top bit set to 1.
#define RFM69_WRITE_ADDR(addr) (((uint8_t)addr) | 0x80)   
//! Sets the given Address to READ access for the RFM69. Top Bit set to 0
#define RFM69_READ_ADDR(addr)  ((((uint8_t) addr) & 0x7F))

RFM69::RFM69() {
}

RFM69::~RFM69() {
}


/*************************************************HAL access Functions*********************************/
void RFM69::spi_attach(RFM69SPI::InitFnc init_function, 
                        RFM69SPI::BeginFnc begin_function,
                        RFM69SPI::EndFnc end_function,
                        RFM69SPI::ReadFnc read_function, 
                        RFM69SPI::WriteFnc write_function) {
    
    // Assign the values of the pointers.
    this->spi_func.init_function = init_function;
    this->spi_func.begin_function = begin_function;
    this->spi_func.end_function = end_function;
    this->spi_func.read_function = read_function;
    this->spi_func.write_function = write_function;
}

void RFM69::spi_attach( RFM69SPI &spiFuncs) {
    // Copy and Assign the values of the pointers.
    this->spi_func.init_function = spiFuncs.init_function;
    this->spi_func.begin_function = spiFuncs.begin_function;
    this->spi_func.end_function = spiFuncs.end_function;
    this->spi_func.read_function = spiFuncs.read_function;
    this->spi_func.write_function = spiFuncs.write_function;
}




/***********************************************RFM69 Register access functions**************************/
bool RFM69::write_reg( RFM69RegisterAddresses reg, uint8_t value) {

    //! Store the result of all SPI access.
    bool res = true;
    //! Stores the address for write access.
    uint8_t addr = RFM69_WRITE_ADDR(reg);

    // Validate SPI access functions before we try and use them.
    if(!this->spi_func.validate()) {
        return false;
    }

    // Begin SPI transfer.
    res &= this->spi_func.begin_function(spi_id);
    // Write out the address of the register to write to.
    res &= this->spi_func.write_function(spi_id, sizeof(addr), &addr );
    // Write out the payload to the register.
    res &= this->spi_func.write_function(spi_id, sizeof(value), &value);
    // End the transfer.
    res &= this->spi_func.end_function(spi_id);

    return res;
}


bool RFM69::write_reg( RFM69Register &reg ) {
    uint8_t byte = reg.get_byte();
    return write_reg( reg.get_reg_address(), byte );
}


 bool RFM69::read_reg( RFM69RegisterAddresses reg, uint8_t* value ) {

    //! Store the result of all SPI access.
    bool res = true;
    //! Stores the address for read access.
    uint8_t addr = RFM69_READ_ADDR(reg);

    // Validate SPI access functions before we try and use them.
    if(!this->spi_func.validate()) {
        return false;
    }

    // Begin SPI transfer.
    res &= this->spi_func.begin_function(spi_id);
    // Write out the address of the register to read from.
    res &= this->spi_func.write_function(spi_id, sizeof(addr), &addr );
    // Read in the payload from the register.
    res &= this->spi_func.read_function(spi_id, sizeof(value), value);
    // End the transfer.
    res &= this->spi_func.end_function(spi_id);

    return res;
 }


 bool RFM69::read_reg( RFM69Register &reg ) {
    uint8_t byte;
    bool result = read_reg( reg.get_reg_address(), &byte );
    reg = byte;
    return result;
}

void RFM69::set_mode(RFM69::OpMode mode) {  
    RegOpMode opMode;
    bool res = true;

    // Read in the current setting, modify mode and write it back.
    res &= read_reg(opMode);
    opMode._mode = (uint8_t) mode;
    res &= write_reg(opMode);

    if(res) {
        // If saved in register, save it locally.
        currMode = mode;
    }
}

RFM69::OpMode RFM69::get_mode(void) {
    // Read in the mode from the register.
    RegOpMode opMode;

    read_reg(opMode);
    return (RFM69::OpMode) opMode._mode;
}

void RFM69::set_freq_deviation(uint16_t freq_deviation) {

    RegFdevMsb msb;
    RegFdevLsb lsb;
    // Equation from datasheet.
    uint16_t reg_value = freq_deviation / FSTEP;

    // Write the two bytes to the registers.
    msb.set_byte( (uint8_t)((reg_value & 0xFF00) >> 8));
    lsb.set_byte((uint8_t)((reg_value & 0x00FF)));
    write_reg(msb);
    write_reg(lsb);
}

uint16_t RFM69::get_freq_deviation(void) {
    RegFdevMsb msb;
    RegFdevLsb lsb;

    // Read in the two values and combine.
    read_reg(msb);
    read_reg(lsb);
    uint16_t reg_value = lsb | (msb << 8);
    // Equation from datasheet.
    return reg_value * FSTEP;
}

int8_t RFM69::read_temp(void) {
    
    RegTemp1 tempControl;
    RegTemp2 tempResult;

    // Start the measurement.
    tempControl._tempMeasStart = true;
    write_reg(tempControl);

    // Poll the reg until the measurement is complete.
    do {
        read_reg(tempControl);
    } while (tempControl._tempMeasRunning);
    
    // Finnally, read the result and return it.
    read_reg(tempResult);
    return tempControl;
}
}