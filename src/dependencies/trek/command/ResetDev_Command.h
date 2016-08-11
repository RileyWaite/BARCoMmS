#ifndef RESETDEV_COMMAND_H
#define RESETDEV_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class ResetDev_Command : public AbstractCommandPDU
{
public:

    // Command fields

    int device = 0;                 // (160:8) UINT Device ID's are defined on the "names, id" tab
    int cycleTime = 0;              // (168:8) UINT Time in seconds for device to be turned off

    ResetDev_Command();

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

#endif // RESETDEV_COMMAND_H
