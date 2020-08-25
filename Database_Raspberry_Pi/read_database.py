import serial
import time
import MySQLdb as mdb
arduino = serial.Serial("/dev/ttyUSB1", 9600)
data = arduino.readline()
pieces = data.split("\t")
temperature = pieces[0]
humidity = pieces[1]
con = mdb.connet('localhost', 'gtr', 'gtrlab', 'gtr_2nd');
while True:
        cursor = con.cursor()
        cursor = execute("""INSERT INTO ITC VALUES(%s,%s,%s)""", ('', temperature, humidity))
        con.commit()
        cursor.close()
        time.sleep(5)

