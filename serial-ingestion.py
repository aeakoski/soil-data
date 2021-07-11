#!/usr/bin/env python3
import serial
import time
from prometheus_client import start_http_server, Gauge, Counter

SOIL_MOISTURE = Gauge('SOIL_MOISTURE', 'Moisture of the soil', ["location", "unit"])
SOIL_TEMPERATURE = Gauge('SOIL_TEMPERATURE', 'Temperature of the soil', ["location", "unit"])
AIR_MOISTURE = Gauge('AIR_MOISTURE', 'Moisture of the air', ["location", "unit"])
AIR_TEMPERATURE = Gauge('AIR_TEMPERATURE', 'Temperature of the air', ["location", "unit"])
SUNLIGHT = Gauge('SUNLIGHT', 'Sunlight strength', ["location", "unit"])
ERRORS = Counter('ERRORS', 'Error counters')


if __name__ == '__main__':
    print("Starting serial monitoring")
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()
    print("Starting prometheus server")
    start_http_server(3333)
    while True:
        time.sleep(0.5)
        if ser.in_waiting <= 0:
            continue
        line = ser.readline().decode('utf-8').rstrip()
        try:
            location = line.split(":")[0]
            type = line.split(":")[1]
            unit = line.split(":")[2]
            value = float(line.split(":")[3])
        except IndexError:
            ERRORS.inc()
            continue
        labels = {"location": location, "unit": unit}
        try:
            if type == "SOIL-MOISTURE":
                SOIL_MOISTURE.labels(location=location, unit=unit).set(value)
            elif type == "SOIL-TEMPERATURE":
                SOIL_TEMPERATURE.labels(location=location, unit=unit).set(value)
            elif type == "AIR-MOISTURE":
                AIR_MOISTURE.labels(location=location, unit=unit).set(value)
            elif type == "AIR-TEMPERATURE":
                AIR_TEMPERATURE.labels(location=location, unit=unit).set(value)
            elif type == "SUNLIGHT":
                SUNLIGHT.labels(location=location, unit=unit).set(value)
        except ValueError:
            ERRORS.inc()
            continue
