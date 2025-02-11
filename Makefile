# Default target (build everything)
all: signal_delay mars_rover_sim earth_receiver_sim



# Light speed signal delay part
signal_delay: signal_delay.o ephemeris/ephemeris_data.o network/comms_manager.o mars-rover/rover.o logger/logger.o
	g++ signal_delay.o ephemeris/ephemeris_data.o network/comms_manager.o mars-rover/rover.o logger/logger.o -o signal_delay

signal_delay.o: main.cpp
	g++ -c main.cpp -o signal_delay.o



# Mars-Earth communication of rover sensors data with signal delay in real-time
mars_rover_sim: mars_rover_sim.o ephemeris/ephemeris_data.o network/comms_manager.o mars-rover/rover.o logger/logger.o
	g++ mars_rover_sim.o ephemeris/ephemeris_data.o network/comms_manager.o mars-rover/rover.o logger/logger.o -o mars_rover_sim

mars_rover_sim.o: mars_rover_sim.cpp
	g++ -c mars_rover_sim.cpp -o mars_rover_sim.o


earth_receiver_sim: earth_receiver_sim.o logger/logger.o
	g++ earth_receiver_sim.o logger/logger.o -o earth_receiver_sim

earth_receiver_sim.o: earth_receiver_sim.cpp
	g++ -c earth_receiver_sim.cpp -o earth_receiver_sim.o



# Common modules 
ephemeris/ephemeris_data.o: ephemeris/ephemeris_data.cpp
	g++ -c ephemeris/ephemeris_data.cpp -o ephemeris/ephemeris_data.o

network/comms_manager.o: network/comms_manager.cpp
	g++ -c network/comms_manager.cpp -o network/comms_manager.o

mars-rover/rover.o: mars-rover/rover.cpp
	g++ -c mars-rover/rover.cpp -o mars-rover/rover.o

logger/logger.o: logger/logger.cpp
	g++ -c logger/logger.cpp -o logger/logger.o

# Clean compiled files
clean:
	rm -f *.o ephemeris/*.o network/*.o mars-rover/*.o logger/*.o signal_delay mars_rover_sim earth_receiver_sim