# Ares-Red-Link

# Data Source 
![](images/astropixels_website.png)

We use the ephemeris data available in the  `astropixels` website, this website has recorded historical data for planets in our solar system from 2011.

A _geocentric ephemeris_ is a table that gives the celestial coordinates of an astronomical object over a range of times as seen from Earth's center.

We will be interested in the data window between 2020 to 2024.

<br/>

## Prepare Data
Inside the root directory of the project a python script `astro_ephemeris_data_parser.py` which takes two arguments:
1. `astro_object_type`: can be planets or sun
2. `astro_object_name`: can be sun, mars, earth, .....
3. `year`, the year of which want to analyse
![](images/prepare_data.png)

