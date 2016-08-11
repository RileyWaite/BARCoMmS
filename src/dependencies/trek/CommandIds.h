#ifndef COMMANDIDS_H
#define COMMANDIDS_H

namespace isat_trek
{

class CommandIds 
{
   public:

      enum Commands
      {
         FSW_CONTROL = 1,
         TELEMQUERY = 5,
         CHANGEMODE = 6,
         DECOM_COMMIT = 7,
         DECOM_ENABLE = 8
      };
};

} // namespace isat_trek

#endif  // COMMANDIDS_H
