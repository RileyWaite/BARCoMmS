#ifndef COMMSCHEDULE_COMMAND_H
#define COMMSCHEDULE_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class CommSchedule_Command : public AbstractCommandPDU
{
public:

    // Command fields

    int numSlots = 0;                   // (160:16) UINT Number of slots of data for each comm pass
    int startTime1 = 0;                 // (176:32) ITWO Unix EPOCH time for the start of the comm pass
    int duration1 = 0;                  // (208:16) UINT Time in seconds for the communication pass
    int dataRate1 = 0;                  // (224:16) UINT Valid values for rates are: 0 = 15kb, 1 = 150kb, 2 = 2.3 Mb.
                                    // 0 = black mode, 1 = activation, 2 = nominal
    int startTime2 = 0;                 // (240:32) ITWO
    int duration2 = 0;                  // (272:16) UINT
    int dataRate2 = 0;                  // (288:16) UINT

    CommSchedule_Command();

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

#endif // COMMSCHEDULE_COMMAND_H
