#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "isat/net/UDPConnection.h"
#include "isat/utils/ByteBuffer.h"
#include "isat/trek/command/DecommissionEnable_Command.h"
#include "isat/trek/command/Decommission_Command.h"
#include "isat/trek/command/DiagnosticMode_Command.h"
#include "isat/trek/command/OperationalMode_Command.h"
#include "isat/trek/command/SafeMode_Command.h"


// This is not part of the isat flight software. It's intended to be a
// stand alone program to send commands to the fsw for testing
// purposes. Scott uses Trek, but I didn't want to have to mess with
// it. :)

using namespace std;
using namespace isat_net;
using namespace isat_utils;
using namespace isat_trek;

UDPConnection commConn;


void
doDecomEnable(int args, char** argv)
{
   DecommissionEnable_Command decomEnableCommand;
   memset(&decomEnableCommand, 0x0, sizeof(decomEnableCommand));

   decomEnableCommand.commandID = 5;
   
   ByteBuffer buf;
   buf.clear();
   decomEnableCommand.toBytes(buf);
   commConn.send(buf);
}

void
doDecomCommit(int args, char** argv)
{
   Decommission_Command decomCommand;
   memset(&decomCommand, 0x0, sizeof(decomCommand));

   decomCommand.commandID = 6;
   ByteBuffer buf;
   buf.clear();
   decomCommand.toBytes(buf);
   commConn.send(buf);   
}

void
doDiagnosticMode(int args, char** argv)
{
   DiagnosticMode_Command modeCommand;
   memset(&modeCommand, 0x0, sizeof(modeCommand));

   modeCommand.commandID = 42; // XXX: This isn't right, but I can't find a current table of commands and APIDs, so...
   ByteBuffer buf;
   buf.clear();
   modeCommand.toBytes(buf);
   commConn.send(buf);
}

void
doSafeMode(int args, char** argv)
{
   SafeMode_Command modeCommand;
   memset(&modeCommand, 0x0, sizeof(modeCommand));

   modeCommand.commandID = 43; // XXX: This isn't right, but I can't find a current table of commands and APIDs, so...
   ByteBuffer buf;
   buf.clear();
   modeCommand.toBytes(buf);
   commConn.send(buf);
}

void
doOperationalMode(int args, char** argv)
{
   OperationalMode_Command modeCommand;
   memset(&modeCommand, 0x0, sizeof(modeCommand));

   modeCommand.commandID = 44; // XXX: This isn't right, but I can't find a current table of commands and APIDs, so...
   ByteBuffer buf;
   buf.clear();
   modeCommand.toBytes(buf);
   commConn.send(buf);
}

int
main(int args, char** argv)
{
   if (!commConn.create(EndPoint()))
   {
      cout << "Couldn't create command connection. Exiting.\n";
   }

   commConn.setDestEndPoint(EndPoint("127.0.0.1", 8501));

   if (args == 1)
   {
      cout << "\nUsage:\n";
      cout << "   send_command [command] {args}\n";
      cout << "\nWhere command is one of:\n";
      cout << "   decom_enable\n";
      cout << "   decom_commit\n";
      cout << "   safe_mode\n";
      cout << "   oper_mode\n";
      cout << "   diag_mode\n";

      exit(0);
   }
   
   String command(argv[1]);

   if (command == "decom_enable")
      doDecomEnable(args, argv);
   else if (command == "decom_commit")
      doDecomCommit(args, argv);
   else if (command == "safe_mode")
      doSafeMode(args, argv);
   else if (command == "oper_mode")
      doOperationalMode(args, argv);
   else if (command == "diag_mode")
      doDiagnosticMode(args, argv);
   else
      cout << "Unknown mode: '" << command << "'\n";
}
