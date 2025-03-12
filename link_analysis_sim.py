import socket
import logging
import matplotlib.pyplot as plt
import numpy as np
import datetime


def handle_udp_packets(data_dict, udp_packets):
    logging.info(f"handle_udp_packets -> Accumulate packets batch")

    for packet in udp_packets:
        fields = packet.split(';')
        
        date, ra, dec, mars_coords, sun_coords, distance, angle, signal_delay = fields
        
        if signal_delay == 'inf':
            signal_delay = 9999999999999

        Mars_x, Mars_y, Mars_z = mars_coords.split(',')
        Sun_x, Sun_y, Sun_z = sun_coords.split(',')

        data_dict["Date"].append(datetime.datetime.strptime(date, '%b %d, %Y'))
        data_dict["RA"].append(float(ra))
        data_dict["Dec"].append(float(dec))
        data_dict["Mars Coordinates"].append(mars_coords)
        data_dict["Sun Coordinates"].append(sun_coords)  
        data_dict["Mars_x"].append(float(Mars_x))
        data_dict["Mars_y"].append(float(Mars_y))
        data_dict["Mars_z"].append(float(Mars_z))
        data_dict["Sun_x"].append(float(Sun_x))
        data_dict["Sun_y"].append(float(Sun_y))
        data_dict["Sun_z"].append(float(Sun_z))
        data_dict["Distance"].append(float(distance))
        data_dict["Angle"].append(float(angle))
        data_dict["Signal Delay"].append(float(signal_delay))

    logging.info(f"handle_udp_packets -> Accumulate packets batch -> Done")
    return data_dict


i = 0
def link_line_plot(data_dict):
    logging.info(f"""link_line_plot -> Generating mars_distance_signal_delay_angle_subplots""")
    global i


    # Use a dark background theme
    plt.style.use("dark_background")

    # Create a figure with a 3x2 grid (3 rows, 2 columns)
    fig = plt.figure(figsize=(20, 8))  

    ax1 = fig.add_subplot(3, 2, 1)  # [0, 0]
    ax2 = fig.add_subplot(3, 2, 3, sharex=ax1)  # [1, 0]
    ax3 = fig.add_subplot(3, 2, 5, sharex=ax1)  # [2, 0]
    ax4 = fig.add_subplot(3, 2, (2, 6), projection='3d') # Spans rows 0, 1, 2 in column 1

    ax1.set_facecolor("#1E1E1E")
    ax2.set_facecolor("#1E1E1E")
    ax3.set_facecolor("#1E1E1E")
    ax4.set_facecolor("#1E1E1E")


    # Plot Distance in the first subplot
    ax1.plot(data_dict["Date"], data_dict["Distance"], color="cyan", label="Distance (AU)")
    ax1.set_ylabel("Distance (AU)", color="cyan")
    ax1.set_title("Mars-Earth Distance Over Time")
    ax1.grid(True, alpha=0.2)
    ax1.set_ylim(0, 2.7)
    ax1.set_xlim(np.datetime64('2020-01-01'), np.datetime64('2030-12-31'))

    # Plot Signal Delay in the second subplot
    ax2.plot(data_dict["Date"], data_dict["Signal Delay"], color="magenta", label="Signal Delay (s)")
    ax2.set_ylabel("Signal Delay (s)", color="magenta")
    ax2.set_title("Mars-Earth Signal Delay Over Time")
    ax2.grid(True, alpha=0.2)
    ax2.set_ylim(100, 1600)
    ax2.set_xlim(np.datetime64('2020-01-01'), np.datetime64('2030-12-31'))


    # Plot Angle in the third subplot
    ax3.plot(data_dict["Date"], data_dict["Angle"], color="yellow", label="Angle (D)")
    ax3.set_ylabel("Angle (d)", color="yellow")
    ax3.set_title("Mars-Sun Angle Over Time")
    ax3.grid(True, alpha=0.2)
    ax3.set_ylim(0, 180)
    ax3.set_xlim(np.datetime64('2020-01-01'), np.datetime64('2030-12-31'))


    # Plot Mars - Sun coordinates
    ax4.plot(data_dict['Mars_x'], data_dict['Mars_y'], c='r', label='Mars')
    ax4.plot(data_dict['Sun_x'], data_dict['Sun_y'], c='y', label='Sun')
    ax4.scatter(data_dict['Mars_x'][-1], data_dict['Mars_y'][-1], c='r', marker='o', s=100)
    ax4.scatter(data_dict['Sun_x'][-1], data_dict['Sun_y'][-1], c='y', marker='o', s=100)

    # Set labels and title
    ax4.set_xlabel('X Coordinate')
    ax4.set_ylabel('Y Coordinate')
    ax4.set_zlabel('Z Coordinate')
    ax4.set_title('Mars and Sun Coordinates Over Time')
    ax4.legend()



    plt.tight_layout()
    ax3.set_xlabel("Date")
    fig.patch.set_facecolor("#1c1c1c")


    # Save the figure
    plt.savefig(f"""link-analysis-plots/signal_delay_{i:003}.png""")
    i += 1

    logging.info(f"""link_line_plot -> Saved link-analysis-plots/signal_delay_{i:003}.png""")



def receive_udp_data(ip="127.0.0.1", port=12345, buffer_size=1024):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    udp_socket.bind((ip, port))
    logging.info(f"receive_udp_data -> UDP receiver listening on {ip}:{port}...")
    packets_list = []
    data_dict = {
        "Date": [],
        "RA": [],
        "Dec": [],
        "Mars Coordinates": [],
        "Sun Coordinates": [],
        "Mars_x": [], "Mars_y": [], "Mars_z": [],
        "Sun_x": [], "Sun_y": [], "Sun_z": [],
        "Distance": [],
        "Angle": [],
        "Signal Delay": []
    }

    try:
        while True:
            # Receive data
            data, addr = udp_socket.recvfrom(buffer_size)
            decoded_data = data.decode('utf-8') 
            logging.info(f"{decoded_data}")

            packets_list.append(decoded_data)

            if len(packets_list) == 50:
                data_dict = handle_udp_packets(data_dict, packets_list)
                link_line_plot(data_dict)
                packets_list = []
                
            
    except KeyboardInterrupt:
        udp_socket.close()
        logging.info(f"receive_udp_data -> UDP socket closed...")




if __name__ == "__main__":
    logging.basicConfig(level = "INFO")
    receive_udp_data("127.0.0.1", 12345)