#include "stdint.h"

class RFM69 {
    public:  

        /******************Constructors/Desctructors**************************************/
        // Defaults
        RFM69();
        ~RFM69(); 



        /***************Register Related Definitions************************************/

        



};

// Enumeration of all of the possible register address in the RFM69HCW
enum class RFM69RegisterAddresses;


class RFM69Register {
protected:
    const uint8_t _default_value;
    const uint8_t _recommended_value;
    const uint8_t _address;

public:
    uint8_t get_default_value()  {return _default_value;}
    uint8_t get_recommended_value() { return _recommended_value;}
    uint8_t get_address() {return _address;}
 
    //! Returns the Current set value.
    virtual uint8_t getValue() = 0;

};