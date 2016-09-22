# BARCoMmS
Ben, Alissa, and Riley's Communication Management System: iSat FSW Testing Ground Station.

Written by Riley Waite, Ben Kingen, and Alissa Smith. Summer 2016, NASAs MSFC Summer Internship Porgram.

## Description
A ground station test software for the iSat project was written with the intent of replicating a mission-viable ground
station with the Consultative Committee for Space Data Systems’ (CCSDS) File Delivery Protocol (CFDP) capability and a modular
user interface with packet transfer visualization, a satellite command issuer, CFDP command-line integration, and satellite event
history displays. Named BARCoMmS (Ben, Alissa, and Riley’s Communication Management System) after the intern group who wrote the software, the software
will be capable of interfacing with the closed-loop iSat data pipeline during Critical Design Review (CDR), and, as such, will be
integral to the simulation of satellite operations. The system will send and receive CCSDS space packets through specified UDP
ports to the Programmable Telemetry Processor (PTP) with certain ports representing specific virtual channels through which
telemetry and satellite commands will run.

## Dependencies
BARCoMmS was developed under the Qt 4.0.3 environment. Additionally, the software depends on the open source CFDP library, which was inlcluded in the commit.

## Contact Us
Questions about the software can be directed to riley.s.waite@gmail.com.
