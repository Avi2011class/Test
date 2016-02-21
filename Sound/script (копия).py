import wave
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math
import random



types = {
    1: np.int8,
    2: np.int16,
    4: np.int32
}


wav = wave.open("sound2.wav", mode="r")
(nchannels, sampwidth, framerate, nframes, comptype, compname) = wav.getparams()

duration = nframes / framerate
w, h = 1000, 800
k = nframes/w/32
DPI = 100
peak = 256 ** sampwidth / 2

content = wav.readframes(nframes)
samples = np.fromstring(content, dtype=types[sampwidth])

plt.figure(1, figsize=(float(w)/DPI, float(h)/DPI), dpi=DPI)
np.set_printoptions(threshold=np.nan)

sta = 6
# 1-------------------------------------------------------------
channel = samples[0::nchannels][:]
channel = [int(x) for x in channel]
axes = plt.subplot(sta, 1, 1, axisbg="k")
axes.plot(channel, "r")
# 2----------------------------------------------------------------

sum_arr = [0] * len(channel)

for n in range(1, 4):
	STEP = 500
	for j in range(STEP):
		sum_arr[0] += abs(channel[j])
	for j in range(1, len(channel) - STEP):
		sum_arr[j] = sum_arr[j - 1] - abs(channel[j - 1]) + abs(channel[j + STEP - 1])

	for j in range(len(sum_arr)):
		sum_arr[j] //= STEP
	channel = sum_arr[:]
		
axes = plt.subplot(sta, 1, 2, axisbg="k")
axes.plot(sum_arr, "g")
# 3------------------------------------------------------------------------
LIM_AMP = max(sum_arr) / 3
for j in range(len(sum_arr)):
	if sum_arr[j] < LIM_AMP:
		sum_arr[j] = 0
axes = plt.subplot(sta, 1, 3, axisbg="k")
axes.plot(sum_arr, "g")
# 4-----------------------------------------
diskr_arr = []
res_arr = [0] * len(sum_arr)
le = len(sum_arr)
STEP = 1500
i = 0
while i < le - STEP:
	su = 0
	j = 0
	while j < STEP:
		su += sum_arr[i + j]
		j += 1
	su //= STEP
	if su > LIM_AMP:
		for j in range(i, i + STEP):
			res_arr[j] = su
		diskr_arr.append(su)
	else:
		for j in range(i, i + STEP):
			res_arr[j] = 0
		diskr_arr.append(su)
	i = i + STEP
axes = plt.subplot(sta, 1, 4, axisbg="k")
axes.plot(res_arr, "g")
# 5--------------------------------------------------------
for i in range(len(diskr_arr)):
	diskr_arr[i] //= 100
MAX_AMP = max(diskr_arr)
MIN_AMP = min(diskr_arr)
diskr_arr = [MIN_AMP] + diskr_arr[:]
for i in range(len(diskr_arr)):
	diskr_arr[i] -= MIN_AMP
axes = plt.subplot(sta, 1, 5, axisbg="k")
axes.plot(diskr_arr, "g")	
# 6----------------------------------------------------------

max_arr = []

STEP = 4
i = 0
while i < len(diskr_arr) - STEP:
	if diskr_arr[i + STEP] - diskr_arr[i] > (MAX_AMP - MIN_AMP) / 4:
		max_arr.append(i)
		i += STEP
	i += 1
print(len(max_arr), max_arr)
# ---------------------------------------------------------

plt.savefig("wave", dpi=DPI)
plt.show()

