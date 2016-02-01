import math

class Converter:
	@staticmethod
	def GetIntBlocks(string, BlockSize):
		StartLength = len(string)
		if len(string) % BlockSize != 0:
			string += (BlockSize - len(string) % BlockSize) * b'\x00'
		ByteBlocks = []
		while string != b'':
			ByteBlocks.append(string[:BlockSize])
			string = string[BlockSize:]
		IntBlocks = [BlockSize, StartLength]
		for CurrentBlock in ByteBlocks:
			Buffer = 0
			for j in range(0, BlockSize):
				Buffer += (256 ** j) * CurrentBlock[j]
			IntBlocks.append(Buffer)
		return IntBlocks
	
	@staticmethod
	def GetByteString(IntBlocks):
		BlockSize, StartLength = IntBlocks[0], IntBlocks[1]
		IntBlocks = IntBlocks[2:]

		StringBlocks = []		
		for CurrentIntBlock in IntBlocks:
			Buffer = bytearray()
			for j in range(0, BlockSize):
				Buffer.append((CurrentIntBlock // (256 ** j)) % 256)
			StringBlocks.append(Buffer)
		string = b''
		for CurrentStrBlock in StringBlocks:
			string += bytes(CurrentStrBlock)
		string = string[:StartLength]
		return string
