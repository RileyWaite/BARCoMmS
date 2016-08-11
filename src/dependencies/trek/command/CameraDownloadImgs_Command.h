#ifndef CAMERADOWNLOADIMGS_COMMAND_H
#define CAMERADOWNLOADIMGS_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class CameraDownloadImgs_Command : public AbstractCommandPDU
{
   public:

      // Command fields

      int numImages;                    // (160:8)   Number of images to send to ground, most recent first.


      CameraDownloadImgs_Command();

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

#endif  // CAMERADOWNLOADIMGS_COMMAND_H
