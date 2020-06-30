#include "RFM69.h"


RFM69::RFM69() {


}

RFM69::~RFM69() {


}

void RFM69::set_spi(RFM69spiInitFnc init_function, RFM69spiReadFnc read_function, RFM69spiWriteFnc write_function) {
    // Ensure valid fnc pointers.
    if( init_function == nullptr || read_function == nullptr || write_function == nullptr ) {
        return;
    }
    // Assign the values of the pointers.
    this->init_function = init_function;
    this->read_function = read_function;
    this->write_function = write_function;
}