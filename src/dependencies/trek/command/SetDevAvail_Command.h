#ifndef SETDEVAVAIL_COMMAND_H
#define SETDEVAVAIL_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class SetDevAvail_Command : public AbstractCommandPDU
{
public:

    // Command fields

    int device = 0;                         // (160:8) UINT Device ID's are defined on the "names, id" tab
    int state = 0;                          // (168:8) UINT State of device as defined on the "names, id" tab

    SetDevAvail_Command();

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

} // namespace isat_trek

#endif // SETDEVAVAIL_COMMAND_H
