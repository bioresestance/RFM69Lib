#include "RFM69.h"

//! Sets the given Address to Write access for the RFM69. Top bit set to 1.
#define RFM69_WRITE_ADDR(addr) (((uint8_t)addr) | 0x80)   
//! Sets the given Address to READ access for the RFM69. Top Bit set to 0
#define RFM69_READ_ADDR(addr)  ((((uint8_t) addr) & 0x7F))

RFM69::RFM69() {
}

RFM69::~RFM69() {
}


void RFM69::spi_attach(RFM69SPI::InitFnc init_function, 
                        RFM69SPI::BeginFnc begin_func,
                        RFM69SPI::EndFnc end_func,
                        RFM69SPI::ReadFnc read_function, 
                        RFM69SPI::WriteFnc write_function) {
    
    // Assign the values of the pointers.
    this->spi_func.init_function = init_function;
    this->spi_func.begin_function = begin_func;
    this->spi_func.end_function = end_func;
    this->spi_func.read_function = read_function;
    this->spi_func.write_function = write_function;
}


bool RFM69::write_reg( RFM69RegisterAddresses reg, uint8_t num_to_write, uint8_t* buff ) {

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
    res &= this->spi_func.write_function(spi_id, num_to_write, buff);
    // End the transfer.
    res &= this->spi_func.end_function(spi_id);

    return res;
}


 bool RFM69::read_reg( RFM69RegisterAddresses reg, uint8_t num_to_read, uint8_t* buff ) {

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
    res &= this->spi_func.read_function(spi_id, num_to_read, buff);
    // End the transfer.
    res &= this->spi_func.end_function(spi_id);

    return res;
 }