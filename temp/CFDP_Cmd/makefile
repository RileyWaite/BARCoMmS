# WHAT IS THIS:  This is the top-level makefile for the as-delivered CFDP
#   engine.  It builds two sample cfdp applications.  One resembles the
#   typical flight application (sends bigger filedata chunks) and the
#   other resembles the typical ground application (sends smaller filedata
#   chunks).  It also builds a third application that tests the first two.
# WHAT IT DOES:  Builds 3 applications in the TEST sub-directory
#   ('cfdp_flight', 'cfdp_ground', and 'test_cfdp').
#   If it completes successfully, the regression test can be run.

default:  cfdp_flight cfdp_ground test_cfdp

cfdp_flight:
#       Copy the config file used for the flight application:
	cd PUB;   cp cfdp_config.h.flight cfdp_config.h
#       Compile the library (flight version):
	cd PRI;   make clean
#       Compile and link the sample application (flight version):
	cd CODE;   make clean
#       Give the resulting application the appropriate name:
	cd TEST;   mv cfdp_app cfdp_flight

cfdp_ground:
#       Copy the config file used for the ground application:
	cd PUB;   cp cfdp_config.h.ground cfdp_config.h
#       Compile the library (ground version):
	cd PRI;   make clean
#       Compile and link the sample application:
	cd CODE;   make clean
#       Give the resulting application the appropriate name:
	cd TEST;   mv cfdp_app cfdp_ground

test_cfdp:
#       Compile and link the application that tests the cfdp applications:
	cd TEST;   make
