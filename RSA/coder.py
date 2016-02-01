import math
from keygen import Key, CreateKeys
from primemath import PowerMod
from converter import Converter

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
		self.BlockSize = int(math.log2(K.module) / 5)
		if self.BlockSize <= 0:
			raise KeyLengthError
	
	def CodeString(self, string):
		IntBlocks = Converter.GetIntBlocks(strint, self.BlockSize)
		
			
	
		
# CreateKeys(6, 8, "OpenKey", "ClosedKey")
# ok = Key.ReadFromFile("OpenKey")
string = 'Вот такая классная строка большой длины'
byte = Converter.GetIntBlocks(string, 6)
print(byte)
restr = Converter.GetString(byte)
print(restr)

