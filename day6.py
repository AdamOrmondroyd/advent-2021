import numpy as np

num_days = 256
buffer = 10  # to allow for births which will happen after the end

births = np.zeros((num_days + buffer))
input = np.genfromtxt("input6.txt", delimiter=",")
input = input.astype(int)
num_fish = len(input)

print(input)
for i in input:
    births[i] += 1
print(births)

num_born_today = 0
for i in range(num_days):
    print(i)
    num_born_today = births[i]
    num_fish += num_born_today
    births[i + 7] += num_born_today
    births[i + 9] += num_born_today

print(num_fish)
