import math
import random

def GCD(a, b): # Вычисление наибольшего общего делителя двух натуральных чисел
    while b != 0:
        a, b = b, a % b
    return a

def PowerMod(x, y, mod): # Возведение в степень по модулю
    res = 1
    while y != 0:
        if y % 2 == 1:
            res = (res * x) % mod
            y -= 1
        else:
            x = (x * x) % mod
            y //= 2
    return res

def PrimeTest(n): # Проверка числа на простоту "в лоб", а заем тестом Ферма
    if n == 1:
        return False
    FirstPrimeList = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, \
    37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, \
    103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, \
    173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, \
    241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, \
    317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, \
    401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, \
    479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, \
    571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, \
    647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, \
    739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, \
    827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, \
    919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997]
    for i in FirstPrimeList:
        if i >= n:
            return True
        if n % i == 0:
            return False
    count = 0
    while count < 1000:
        a = random.randint(7, 10 ** 10)
        if GCD(a, n) == 1:
            count += 1
            if PowerMod(a, n - 1, n) != 1:
                return False
        else:
            pass
    return True

def GenerateE(Phi): # Поиск числа, взаимно простого с Phi в порядке приоритета
	for i in [257, 65537, 17]:
		if GCD(i, Phi) == 1:
			return i
	for i in range(1, 100):
		e = random.randint(20, 10000)
		if GCD(e, Phi) == 1:
			return e
	for i in range(1, 100):
		e = random.randint(10 ** 4, 10 ** 6)
		if GCD(e, Phi) == 1:
			return e	
	while True:
		e = random.randint(10 ** 6, 10 ** 12)
		if GCD(e, Phi) == 1:
			return e

def LinearDiophantineEquations(x, y): # Поиск a, b таких, что ax + by = GCD(x, y), причем a > 0
	First = (x, 1, 0)
	Second = (y, 0, 1)
	while Second[0] != 0:
		q = First[0] // Second[0]
		First, Second = Second, (First[0] % Second[0], First[1] - q * Second[1], First[2] - q * Second[2])
	k = 0
	if First[1] < 0:
		k = (-First[1]) // y + 1
	return (k * y + First[1], -k * x + First[2])
	
def GetPrime(MinBytes, MaxBytes):
	result = random.randint(2 ** MinBytes, 2 ** MaxBytes)
	while not PrimeTest(result):
		result = random.randint(2 ** MinBytes, 2 ** MaxBytes)
	return result
