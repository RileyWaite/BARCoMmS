#ifndef TELEMQUERY_COMMAND_H
#define TELEMQUERY_COMMAND_H

#include "../dependencies/trek/AbstractCommandPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

/**
 * XXX: Replace with real description in isat.pdu file.
 */
class TelemQuery_Command : public AbstractCommandPDU
{
   public:

      // Command fields

      int pdu = 0;                          // (160:8)   Pdu Id we're querying
      int queryType = 0;                    // (168:8)   time range  == 0, Object Id range == 1
      int start = 0;                        // (176:32)  Start value  (seconds in unix time if time query, object id if objid range query)
      int end = 0;                          // (208:32)  End value


      TelemQuery_Command();

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

#endif  // TELEMQUERY_COMMAND_H
