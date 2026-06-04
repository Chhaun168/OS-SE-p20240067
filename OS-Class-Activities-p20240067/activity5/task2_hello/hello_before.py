import threading
import random
import time


def process1():
    time.sleep(random.random())
    print("H", end="")
    time.sleep(random.random())
    print("E", end="")


def process2():
    time.sleep(random.random())
    print("L", end="")
    time.sleep(random.random())
    print("L", end="")


def process3():
    time.sleep(random.random())
    print("O", end="")


threads = [
    threading.Thread(target=process1),
    threading.Thread(target=process2),
    threading.Thread(target=process3),
]

for t in threads:
    t.start()

for t in threads:
    t.join()

print()
