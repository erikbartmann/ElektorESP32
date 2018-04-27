# -*- coding: cp852 -*-
import paho.mqtt.client as mqtt
import sqlite3        # Wird für SQLite-Zugriff benötigt
import datetime       # Wird für Timestamp benötigt
dbfile = 'ds18b20.db' # lokale Datenbank-Datei

# Bei Verbindung Topic initialisieren
def on_connect(client, userdata, flags, rc):
    print "Connected. rc= "+str(rc)
    client.subscribe("/arbeitszimmer/temperatur")

# Callback-Funktion
def on_message(client, userdata, msg):
    mqtt2database(msg.topic, str(msg.payload))

def mqtt2database(mqttTopic, mqttTemperatur):
	try:
		sensorid, t = 1, mqttTemperatur
		dbconnection = sqlite3.connect(dbfile) 
		cursor = dbconnection.cursor()         
		timestamp = str(datetime.datetime.now())
		datensatz = (mqttTopic, 'Temp', sensorid, t, timestamp)
		print datensatz
		sql = 'insert into temperatur \
			   (topic, sensortyp, sensorid, messwert, datum) \
			   values(?, ?, ?, ?, ?)'
		cursor.execute(sql, datensatz) 
		dbconnection.commit()          
		dbconnection.close()           
		print 'DB-Insert ok.'		   
	except sqlite3.Error, e:
		print 'SQLite Error: ', e      

client = mqtt.Client()                 
client.on_connect = on_connect         
client.on_message = on_message         

client.connect("localhost", 1883, 60)  
client.loop_forever()                  
