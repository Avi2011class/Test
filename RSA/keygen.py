import math
import random
from primemath import PrimeTest, GCD, GenerateE, LinearDiophantineEquations, GetPrime

class Key:
	def __init__(self, exponent, module):
		self.exponent = exponent
		self.module = module
	def __str__(self):
		return "Key = {0}: {1}\n".format(self.exponent, self.module)
	@staticmethod
	def ReadFromFile(filename):
		F = open(filename, 'r')
		Pa = F.read().replace('\n', '').split(':')
		F.close()
		return Key(int(Pa[0], 16), int(Pa[1], 16))
	def WriteToFile(self, filename):
		F = open(filename, 'w')
		F.write("{0}:{1}\n".format(hex(self.exponent), hex(self.module)))
		F.flush()
		F.close()
	
def CreateKeys(MinBytes, MaxBytes, OpenKeyFile, ClosedKeyFile):
	if MinBytes > MaxBytes:
		MinBytes, MaxBytes = MaxBytes, MinBytes
	if MinBytes == MaxBytes:
		print('Хочу адекватный диапазон')
		exit(-1)
	P = GetPrime(MinBytes, MaxBytes)
	Q = GetPrime(MinBytes, MaxBytes)
	T = GetPrime(MinBytes, MaxBytes)
	N = P * Q * T
	Phi = (P - 1) * (Q - 1) * (T - 1)
	e = GenerateE(Phi)
	d = LinearDiophantineEquations(e, Phi)[0]
	OpenKey = Key(e, N)
	ClosedKey = Key(d, N)
	OpenKey.WriteToFile(OpenKeyFile)
	ClosedKey.WriteToFile(ClosedKeyFile)


