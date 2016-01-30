import math
from keygen import Key, CreateKeys
from primemath import PowerMod


class IntCoder:
	def __init__(self, K):
		self.Key = K
		
	def CodeInt(self, n):
		if n < self.Key.module:
			return PowerMod(n, self.Key.exponent, self.Key.module)
		else:
			raise Overflow
			
class StringCoder:
	def __init__(self, K):
		self.Key = K
		self.IntCoder = IntCoder(K)
# TODO разбивать строки на блоки и шифровать их

# CreateKeys(3, 4, "OpenKey", "ClosedKey")
ok = Key.ReadFromFile("OpenKey")
ck = Key.ReadFromFile("ClosedKey")
print(ok, ck)

