import re
import tkinter
import sys
from coder import StringCoder
from keygen import Key, CreateKeys

tk = tkinter.Tk()
tk.withdraw()
# корректные ключи по-умолчанию
Key1 = Key.ReadFromFile('OpenKey')
Key2 = Key.ReadFromFile('ClosedKey')
Coder1 = StringCoder(Key1)
Coder2 = StringCoder(Key2)

while True:
	print('''Выберите действие:
	1. Установить файл ключа для зашифровки
	2. Установить файл ключа для расшифровки
	3. Зашифровать файл
	4. Расшифровать файл
	5. Создать новые ключи
	6. Выйти
>>''', end = '')
	command = int(input())
	sys.stdout.flush()
	if command == 1:
		filename = input('Имя файла: ')
		Key1 = Key.ReadFromFile(filename)
		Coder1 = StringCoder(Key1)
	elif command == 2:
		filename = input('Имя файла: ')
		Key2 = Key.ReadFromFile(filename)
		Coder2 = StringCoder(Key2)
	elif command == 3:
		filename = input('Введите имя файла для шифрования: ').replace('\n', '')
		F = open(filename, 'rb')
		st = F.read()
		R = open(filename + '.coded', 'w')
		R.write(Coder1.CodeByteString(st))
		R.close()
		print('Файл зашифрован.\n')
	elif command == 4:
		filename = input('Введите оригинальное (без .coded) имя файла для дешифрования: ').replace('\n', '')
		F = open(filename + '.coded', 'r')
		st = F.read()
		R = open(filename.replace('.coded', ''), 'wb')
		R.write(Coder2.CodeIntString(st))
		R.close()
		print('Файл расшифрован.\n')
	elif command == 5:
		KeyLength = int(input('Длина ключей (8-1000 бит): '))
		CreateKeys(KeyLength, KeyLength + 1, "OpenKey", "ClosedKey")
		Key1 = Key.ReadFromFile('OpenKey')
		Key2 = Key.ReadFromFile('ClosedKey')
		Coder1 = StringCoder(Key1)
		Coder2 = StringCoder(Key2)
		print('Новые ключи записаны в файлы OpenKey и  ClosedKey, данные в памяти обновлены')
	elif command == 6:
		exit(0)
	else:
		print('Попробуем еще разок')
