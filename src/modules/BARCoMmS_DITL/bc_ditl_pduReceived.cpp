#include "bc_ditl.h"

#include "../../dependencies/trek/telemetry/Event_Telemetry.h"
#include "../../dependencies/trek/TelemetryIds.h"

void BC_DITL::pduReceived(ByteBuffer buf)
    // Called when the PacketListenerThread emits a PDU
{
    ui->DITL_statusBar->showMessage("Receiving PDU...", 3000);

    buf.setByteOrder(ByteBuffer::BigEndian);

    int APID;
    if(!buf.getBits(0, 32, APID)) qDebug() << "Failed!";

    if(APID==isat_trek::TelemetryIds::EVENT)
    {        isat_trek::Event_Telemetry event;
        event.fromBytes(buf);

        addEvent(new BC_Event(event.timestamp,event.code,event.originId,static_cast<int>(event.type),static_cast<int>(event.severity),"TEMP_MESSAGE","TEMP_FILENAME",66));
    }
}
