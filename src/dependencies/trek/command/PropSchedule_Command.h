#ifndef PROPSCHEDULE_COMMAND_H
#define PROPSCHEDULE_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class PropSchedule_Command : public AbstractCommandPDU
{
public:

    // Command fields

    PropSchedule_Command();

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

#endif // PROPSCHEDULE_COMMAND_H
