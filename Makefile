signal_delay: signal_delay.o ephemeris/ephemeris_data.o network/comms_manager.o mars-rover/rover.o 
	g++ signal_delay.o ephemeris/ephemeris_data.o network/comms_manager.o mars-rover/rover.o -o signal_delay


signal_delay.o: main.cpp
	g++ -c main.cpp -o signal_delay.o

ephemeris/ephemeris_data.o: ephemeris/ephemeris_data.cpp
	g++ -c ephemeris/ephemeris_data.cpp -o ephemeris/ephemeris_data.o

network/comms_manager.o: network/comms_manager.cpp
	g++ -c network/comms_manager.cpp -o network/comms_manager.o

mars-rover/rover.o: mars-rover/rover.cpp
	g++ -c mars-rover/rover.cpp -o mars-rover/rover.o
