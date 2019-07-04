from magneto import Magneto
from multiprocessing import Process, Value, Queue

#initialize shared var for distance
s_distance = Value('l', 0)

#create instance of Process subclass Magneto and pass shared value var
sensor_process = Magneto(shared_distance=s_distance)
sensor_process.start()

#for i in range(100):
while True:
    print(s_distance.value)
