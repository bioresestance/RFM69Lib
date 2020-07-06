#include "RFM69.h"


RFM69::RFM69() {


}

RFM69::~RFM69() {


}

void RFM69::spi_attach(RFM69SPI::InitFnc init_function, 
                        RFM69SPI::BeginFnc begin_func,
                        RFM69SPI::EndFnc end_func,
                        RFM69SPI::ReadFnc read_function, 
                        RFM69SPI::WriteFnc write_function) {
    
    // Ensure valid fnc pointers.
    if( init_function == nullptr || 
        begin_func == nullptr || 
        end_func == nullptr || 
        read_function == nullptr || 
        write_function == nullptr ) {
        return;
    }
    
    // Assign the values of the pointers.
    this->spi_func.init_function = init_function;
    this->spi_func.begin_function = begin_func;
    this->spi_func.end_function = end_func;
    this->spi_func.read_function = read_function;
    this->spi_func.write_function = write_function;
}