#ifndef TRANSMITDATARATE_COMMAND_H
#define TRANSMITDATARATE_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class TransmitDataRate_Command : public AbstractCommandPDU
{
public:

    // Command fields

    int dataRate = 0;                       // (160:16) UINT Valid values for rates are 0 = 15kb, 1 = 150kb, 2 = 2.3Mb
                                        // 0 = black mode, 1 = activation, 2 = nominal
    TransmitDataRate_Command();


    /**
     * Populate the header and command fields from the data in buf.
     *
     * @return true if successful.
     */
    bool fromBytes(ByteBuffer& buf);

    /**
     * Create the binary representation of this instance in the specified buffer.
     *
     * @return true if successful.
     */
    bool toBytes(ByteBuffer& buf);
};

}   // namespace isat_trek

#endif // TRANSMITDATARATE_COMMAND_H
