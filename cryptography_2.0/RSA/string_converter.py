import random
class string_converter:
	@staticmethod
	def string_to_int_blocks(string, block_size):
		
		start_length = len(string)
		if len(string) % block_size != 0:
			string += (block_size - len(string) % block_size) * b'\x00'
		
		byte_blocks = []
		iterator, limit_length = 0, len(string)
		while iterator * block_size < limit_length:
			byte_blocks.append(string[iterator * block_size : (iterator + 1) * block_size])
			iterator += 1
			
		result_int_blocks = [block_size, start_length]
		for current_block in byte_blocks:
			carry = 0
			for j in range(block_size):
				carry += (256 ** j) * current_block[j]
			result_int_blocks.append(carry)
			
		return result_int_blocks
	
	@staticmethod
	def int_blocks_to_linear_string(int_blocks):
		return b' '.join(int_blocks)
	
	@staticmethod
	def linear_string_to_int_blocs(linear_string):
		return [int(current) for current in linear_string.split(b' ')]
		
	@staticmethod
	def int_blocks_to_byte_string(int_blocks):
		block_size, start_length = int_blocks[0], int_blocks[1]
		int_blocks = int_blocks[2:]
		
		byte_blocks = []
		for current_int_block int int_blocks:
			carry = bytearray()
			for j in range(block_size):
				carry.append((current_int_block // (256 ** j)) % 256)
			byte_blocks.append(carry)
			
		result_byte_string = b''
		for current_byte_block int byte_blocks:
			result_byte_string += bytes(current_byte_block)
		result_byte_string = result_byte_string[:start_length]
		
		return result_byte_string		
		
		
print(string_converter.string_to_int_blocks(b'12313', 2))
