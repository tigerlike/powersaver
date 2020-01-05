import time
import tensorflow as tf
print("Num GPUs Available: ", len(tf.config.experimental.list_physical_devices('GPU')))

for i in range(0,5):
    time.sleep(1)
    print(i, "seconds")
