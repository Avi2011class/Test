import math, os
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
			print('ERR')
			return None
			
class StringCoder:
	def __init__(self, K):
		self.Key = K
		self.IntCoder = IntCoder(K)
		self.BlockSize = int(math.log(K.module, 256)) - 2
		if self.BlockSize <= 0:
			print('KeyLengthError')
			exit(-1)
	
	def CodeString(self, string):
		IntBlocks = Converter.GetIntBlocks(string, self.BlockSize)
		CodedIntBlocks = [self.IntCoder.CodeInt(Block) for Block in IntBlocks]
		CodedString = ' '.join(list(map(str, CodedIntBlocks)))
		return CodedString
		
	def CodeIntString(self, CodedString):
		IntBlocks = list(map(int, CodedString.split(' ')))
		DecodedIntBlocks = [self.IntCoder.CodeInt(Block) for Block in IntBlocks]
		DecodedString = Converter.GetString(DecodedIntBlocks)
		return DecodedString
		


