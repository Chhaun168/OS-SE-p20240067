import threading
import random
import time

buffer = []

produced = 0
packaged = 0

running = True


def producer(machine_id):
    global produced, running

    pair_id = 1

    while running:

        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"

        if len(buffer) >= 100:
            print("The producing machine is broken")
            running = False
            break

        buffer.append(p1)

        if random.random() < 0.5:
            time.sleep(0.001)

        buffer.append(p2)

        produced += 1
        pair_id += 1

        time.sleep(random.uniform(0, 0.003))


def consumer():
    global packaged, running

    while running:

        if len(buffer) < 2:
            print("The packaging machine is broken")
            running = False
            break

        p1 = buffer.pop(0)
        p2 = buffer.pop(0)

        pair1 = "-".join(p1.split("-")[:2])
        pair2 = "-".join(p2.split("-")[:2])

        if pair1 != pair2:
            print("Pairs are incorrect")
            print(f"{p1} + {p2}")
            running = False
            break

        packaged += 1

        print(
            f"Produced pairs: {produced} | "
            f"Packaged pairs: {packaged} | "
            f"Buffer particles: {len(buffer)}"
        )

        time.sleep(random.uniform(0, 0.003))


for i in range(3):
    threading.Thread(target=producer, args=(i + 1,), daemon=True).start()

threading.Thread(target=consumer, daemon=True).start()

while running:
    time.sleep(0.1)
