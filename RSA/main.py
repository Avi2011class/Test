import re
import clipboard
from coder import Coder
from keygen import Key

# Корректные ключи по-умолчанию
Key1 = Key(257, 146969)
Key2 = Key(59921, 146969)
Coder1 = Coder(Key1)
Coder2 = Coder(Key2)

while True:
	print('''Выберите действие:
	1. Установить файл ключа для зашифровки
	2. Установить файл ключа для расшифровки
	3. Зашифровать строку
	4. Расшифровать строку
	5. Выйти
>>''', end = '')
	command = int(input())
	if command == 1:
		filename = input('Имя файла: ')
		Key1 = Key.ReadFromFile(filename)
		Coder1 = Coder(Key1)
	elif command == 2:
		filename = input('Имя файла: ')
		Key2 = Key.ReadFromFile(filename)
		Coder2 = Coder(Key2)
	elif command == 3:
		string = input("Введите строку для шифрования: ")
		result = Coder1.CodeString(string)
		clipboard.Set(result)
		print('Зашифрованная срока(скопирована в буфер обмена):', result)
	elif command == 4:
		string = input("Введите строку для дешифрования: ")
		result = Coder2.CodeString(string)
		clipboard.Set(result)
		print('Дешафрованная срока(скопирована в буфер обмена):', result)
	elif command == 5:
		exit(0)
	else:
		print('Попробуем еще разок')
		
		
