#pragma once
#include <stdint.h>
#include <RFM69SPI.h>
#include <RFM69Registers.h>


namespace RFM69Radio {

/**
 * @brief Main class for RFM69 access. 
 * 
 */
class RFM69 {

    
    public:

        /** @brief Enum to specify how the RFM69 module should be controlled. */
        enum class controlMode {
            POLLING_MODE,   //!< The object will periodically poll the module for changes.
            INTERRUPT_MODE  //!< The object will use interrupt pins to know when a change occurs.
        };


        /** @brief Defines the different possible modes of the module. */
        enum class OpMode {
            SLEEP,          //!< Sleep mode.
            STANDBY,        //!< Standby mode.
            FREQ_SYNTH,     //!< Frequency Synthesizer mode. 
            TRANSMIT,       //!< Transmit mode.
            RECEIVE         //!< Reciever mode.
        };

    private:
        //! Holds all of the function pointer for SPI access.
        RFM69SPI spi_func;
        //! ID for the SPI channel.
        uint8_t spi_id = 0xFF;
        //! Holds the current control state.
        controlMode currControlMode = controlMode::POLLING_MODE;
        //! Holds the current operational mode of the module. Defaults to standby at startup.
        OpMode currMode = OpMode::STANDBY;

    public:  
        // Defines the maximum SPI clock for the RFM69, in hertz.
        static const uint32_t max_spi_clock = 10000000u;

        /******************Constructors/Desctructors**************************************/
        // Defaults
        RFM69();
        ~RFM69(); 
        /*********************************************************************************/
        
        /**
         * @brief Attaches the spi function pointers for SPI control.
         * 
         * @param init_function Function pointer to the SPI init function.
         * @param begin_function Function pointer to the SPI Begin transfer function.
         * @param end_function Function pointer to the SPI End transfer function.
         * @param read_function  Function pointer to the SPI read function. 
         * @param write_function Function pointer to the SPi write function.
         */
        void spi_attach(RFM69SPI::InitFnc init_function, 
                        RFM69SPI::BeginFnc begin_function,
                        RFM69SPI::EndFnc end_function,
                        RFM69SPI::ReadFnc read_function, 
                        RFM69SPI::WriteFnc write_function);

        /**
         * @brief Attaches the spi function pointers for SPI control.
         * 
         * @param spiFuncs Struct that holds all required spi access func pointers.
         */
        void spi_attach( RFM69SPI &spiFuncs);

        //TODO
        void io_attach();


        /**
         * @brief Writes a buffer to a given register.
         * 
         * @param reg Register to access.
         * @param value Byte to write. 
         * @return true When all bytes were written successfully.
         * @return false When either an error occurred or not all bytes written.
         */
        bool write_reg( RFM69RegisterAddresses reg, uint8_t value );

        /**
         * @brief Writes the content of a register object to its corresponding RFM69 register. 
         * 
         * @param reg Register object to write its content to. Used to determine address.
         * @return true If the write was successful.
         * @return false If something went wrong in the register write.
         */
        bool write_reg( RFM69Register &reg );

        /**
         * @brief Writes a buffer to a given register.
         * 
         * @param reg Register to access.
         * @param value Byte to read. 
         * @return true When all bytes were written successfully.
         * @return false When either an error occurred or not all bytes written.
         */
        bool read_reg( RFM69RegisterAddresses reg, uint8_t* value );

        /**
         * @brief Reads in the contents of a register to a Register object
         * 
         * @param reg Register object to hold the contents of the read. Used to determine address.
         * @return true If the read was successful.
         * @return false If something went wrong in the register read. 
         */
        bool read_reg( RFM69Register &reg );

        /**
         * @brief Sets the current mode of the module.
         * 
         * @param mode The new mode.
         */
        void set_mode(RFM69::OpMode mode);

        /**
         * @brief Get the current mode.
         * 
         * @return OpMode 
         */
        RFM69::OpMode get_mode( void );


};

}