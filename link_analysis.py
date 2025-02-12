import pandas as pd
import numpy as np
import logging
import matplotlib
import matplotlib.pyplot as plt


def link_line_plot(df):
    logging.info(f"""link_line_plot -> Generating mars_distance_signal_delay_angle_subplots""")
    # Handle inf values in plot
    df['Signal Delay'] = df['Signal Delay'].replace(np.inf, np.nan)
    max_value = df['Signal Delay'].max()
    df['Signal Delay'] = df['Signal Delay'].replace(np.nan, max_value + 9999999999999)


    df['Date'] = pd.to_datetime(df['Date'], format="%b %d, %Y")


    # Use a dark background theme
    plt.style.use("dark_background")

    # Create a figure with three subplots (stacked vertically)
    fig, axes = plt.subplots(nrows=3, ncols=1, figsize=(16, 8))

    axes[0].set_facecolor("#1E1E1E")
    axes[1].set_facecolor("#1E1E1E")
    axes[2].set_facecolor("#1E1E1E")


    # Plot Distance in the first subplot
    axes[0].plot(df["Date"], df["Distance"], color="cyan", label="Distance (AU)")
    axes[0].set_ylabel("Distance (AU)", color="cyan")
    axes[0].set_title("Mars-Earth Distance Over Time")
    axes[0].grid(True, alpha=0.2)

    # Plot Signal Delay in the second subplot
    axes[1].plot(df["Date"], df["Signal Delay"], color="magenta", label="Signal Delay (s)")
    axes[1].set_ylabel("Signal Delay (s)", color="magenta")
    axes[1].set_title("Mars-Earth Signal Delay Over Time")
    axes[1].grid(True, alpha=0.2)
    axes[1].set_ylim(df['Signal Delay'].min()-200, max_value+1000)


    # Plot Angle in the third subplot
    axes[2].plot(df["Date"], df["Angle"], color="yellow", label="Angle (D)")
    axes[2].set_ylabel("Angle (d)", color="yellow")
    axes[2].set_title("Mars-Sun Angle Over Time")
    axes[2].grid(True, alpha=0.2)


    plt.tight_layout()
    axes[2].set_xlabel("Date")
    fig.patch.set_facecolor("#1c1c1c")


    # Save the figure
    plt.savefig("link-analysis-plots/mars_distance_signal_delay_angle_subplots.png")

    logging.info(f"""link_line_plot -> Saved link-analysis-plots/mars_distance_signal_delay_angle_subplots.png -> done""")




if __name__ == "__main__":
    logging.basicConfig(level = "INFO")


    df = pd.read_csv("link_data.csv", sep=";")

    link_line_plot(df)