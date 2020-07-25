#pragma once
#include <stdint.h>


namespace RFM69Radio {
/**
 * @brief Structure to hold all function pointers for SPI access.
 * 
 */
struct RFM69SPI {


/*********************************************SPI Access Function Pointers*************************************/
    /**
     * @brief Function pointer to a function that will perform initializing of SPI channel.
     * 
     *  This function will be called by the RFM69 class to perform initialization of the 
     *  SPI channel. What the function actually does is up to the implementation. After
     *  all initialization is complete, the function will return an ID value for the SPI channel.
     *  This ID value has no meaning to the class, but is used by the read and write function to 
     *  access the SPI channel. 
     * 
     * @return Returns an ID used for read and write functions. 0xFF if failure.
     */
    typedef uint8_t (*InitFnc)(void);

    /**
     * @brief Function point to a function that sets up the SPI driver to begin a transfer.
     * 
     *  This function is called by the RFM69 class before any bytes are transferred. This function
     *  takes in the SPI ID and should perform any tasks at the driver level to prepare for a transfer.
     *  This may include saving any settings and change over to RFM69 ones and set the chip select pin.
     * 
     *  @param SPIHandle SPI Handle for the RFM69 module.
     * 
     *  @return Whether the task was successful or not. Used to determine if transfer can begin.
     * 
     */
    typedef bool (*BeginFnc)(uint8_t SPIHandle);

    /**
     * @brief Function point to a function that sets up the SPI driver to end a transfer.
     * 
     *  This function is called by the RFM69 class after all bytes are transferred. This function
     *  takes in the SPI ID and should perform any tasks at the driver level to end a transfer.
     *  This may include loading any saved settings and deselect the chip select pin.
     * 
     *  @param SPIHandle SPI handle for the RFM69 module.
     * 
     *  @return Whether the task was successful or not.
     * 
     */
    typedef bool (*EndFnc)(uint8_t SPIHandle);


    /**
     * @brief Function pointer type for SPI read function.
     * 
     * @param SPIHandle SPI handle for the RFM69 module.
     * @param readLength Number of bytes to read. 
     * @param readBuff Buffer to store results of read. Ensure at least length long.
     * 
     * @return Whether the result was successful or not.
     * 
     */
    typedef bool (*ReadFnc)(uint8_t SPIHandle, uint16_t readLength, uint8_t* readBuff);

    /**
     * @brief Function pointer type for SPI write function.
     * 
     * @param SPIHandle SPI handle for the RFM69 module.
     * @param writeLength Number of bytes to write to device. 
     * @param writeBuff Buffer containing bytes to write. Must be at least length long.
     * 
     * @return Whether the result was successful or not.
     */
    typedef bool (*WriteFnc)(uint8_t SPIHandle, uint16_t writeLength, uint8_t* writeBuff);


/*****************************************Function Pointer Holders**********************************/
    InitFnc init_function;
    BeginFnc begin_function;
    EndFnc end_function;
    ReadFnc read_function;
    WriteFnc write_function;
/**********************************************Methods*********************************************/

    /**
     * @brief Validate the current stored function pointers.
     * 
     * @return true If no function pointer is null.
     * @return false If 1 or more are null.
     */
    bool validate() {
        // Check if any function is null. Return true is none are null.
        return !( init_function == nullptr || 
                begin_function == nullptr || 
                end_function == nullptr || 
                read_function == nullptr || 
                write_function == nullptr );
    }

};

}