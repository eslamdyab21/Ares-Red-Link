import requests
import logging
import csv
import sys
import os
import re


def request_data(astro_object, file_name):
    url = f"https://astropixels.com/ephemeris/{astro_object}/{file_name}.html"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    }

    response = requests.get(url, headers=headers)
    html_text = response.text


    logging.info(f"""request_data -> {url} -> done""")
    return html_text



def extract_data(html_text):
    pre_matches = re.findall(r"<pre>(.*?)</pre>", html_text, re.DOTALL)

    table_text = "\n".join(pre_matches).strip()
    lines = table_text.split("\n")

    csv_headers = ['Date', 'JD', 'App GST', 'Equation of Time', 'Apparent R.A', 'Apparent Declination'
                'Distance a.u', 'Ang.Diam', 'Hel.Long', 'Hel.Lat', 'P.A.Axis'] 
    csv_data = []


    for line in lines:
        if line.strip():
            row = [col.strip() for col in line.split("  ") if col.strip()]
            if row[0] in ['Date', '(0 UT)', 'h']:
                continue 
            csv_data.append(row)


    logging.info(f"""extract_data -> done""")
    return csv_headers, csv_data



def save_csv(csv_headers, csv_data, base_dir, file_name):
    if not os.path.exists(base_dir):
        os.makedirs(base_dir)
          
    csv_filename = base_dir + '/' + file_name + '.csv'

    with open(csv_filename, "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(csv_headers)  
        writer.writerows(csv_data)  

    logging.info(f"""save_csv -> {csv_filename} -> done""")



if __name__ == "__main__":
    logging.basicConfig(level = "INFO")

    base_dir = 'source-data'

    astro_object = sys.argv[1]
    file_name = sys.argv[2]

    html_text = request_data(astro_object, file_name)
    csv_headers, csv_data = extract_data(html_text)
    save_csv(csv_headers, csv_data, base_dir, file_name)