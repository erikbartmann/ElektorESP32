import paho.mqtt.client as mqtt
# Callback-Funktion, wenn der Client
# einen Response vom Server empfängt
def on_connect(client, userdata, flags, rc):
    print "Connected with result code "+str(rc)
    # Definition der Subscription
    client.subscribe("/arbeitszimmer/temperatur")

# Callback-Funktion, wenn eine Publish-Message
# vom Server empfangen wird
def on_message(client, userdata, msg):
    print msg.topic+" "+str(msg.payload)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)
client.loop_forever()
