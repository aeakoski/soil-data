# soil-data

## Goal
Serial data containing metrics about the farmland is read from the Arduino  sensor and broadcast over serial through USB and saved in Prometheus on the Raspberry Pi

## Sensor serial protocol

A metric from a sensor is written to serial UART on the Arduino. One line per measured metric. A line has the following structure.

```
<LOCATION>:<TYPE>:<UNIT>:<MEASUREMENT>

e.g

...
WHEAT:SOIL-MOISTURE:PERCENT:56
WHEAT:SOIL-TEMPERATURE:CELSIUS:5
RYE:SOIL-TEMPERATURE:CELSIUS:4.9
RYE:SOIL-MOISTURE:PERCENT:6
FIELD:AIR-TEMPERATURE:CELSIUS:15
FIELD:AIR-MOISTURE:PERCENT:15
...

```


## Prometheus and Grafana
Followed this guide:

http://www.d3noob.org/2020/02/installing-prometheus-and-grafana-on.html

Prometheus runns on port 9000
Grafana on port 3000
Prometheus client runns on port 3333

Start `serial-ingestion.py` and let prometheus scrape localhost:3333
