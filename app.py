import paho.mqtt.client as mqtt
from flask import Flask, render_template, make_response, flash, redirect, request, session, abort, url_for

#Start på flask appen 
app = Flask(__name__)

#Connectar till MQTT
mqttc=mqtt.Client()
mqttc.connect("localhost",1883,60)
mqttc.loop_start()

#Skickar användaren till index.html Så man slipper skriva /index.html på slutet av URL:en. 
@app.route('/')
def start():
    return render_template('index.html')

#Skickar användaren till index.html
@app.route('/index.html', methods=['GET', 'POST'])
def index():
    print("index site")
    return render_template('index.html')

#När on-knappen på hemsidan trycks så skickas ett mqtt meddelande som Wemosen tar emot.
@app.route("/on_button", methods=['GET', 'POST'])
def on():
   print("on")
   mqttc.publish('raspsend', "ledon")
   return render_template('index.html')


#När off-knappen på hemsidan trycks så skickas ett mqtt meddelande som Wemosen tar emot.
@app.route("/off_button", methods=['GET', 'POST'])
def off():
    print("off")
    mqttc.publish('raspsend', "ledoff")
    return render_template('index.html')


#Slutet på Flask appen, Ställer in Ip och Port här. 
if __name__== '__main__':
   app.run(host='0.0.0.0', port='8585', debug='True', use_reloader=False)












