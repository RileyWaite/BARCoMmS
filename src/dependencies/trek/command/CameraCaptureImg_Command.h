#ifndef CAMERACAPTUREIMG_COMMAND_H
#define CAMERACAPTUREIMG_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class CameraCaptureImg_Command : public AbstractCommandPDU
{
public:

    // Command fields

    int avgBrightness;                      // (160:8) UINT A number from X to Y, where the closer to Y the increased exposure
    int fill;                               // (168:8) UINT

    CameraCaptureImg_Command();

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

#endif // CAMERACAPTUREIMG_COMMAND_H
