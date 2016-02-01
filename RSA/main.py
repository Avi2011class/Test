import re
import tkinter
from coder import StringCoder
from keygen import Key, CreateKeys

tk = tkinter.Tk()
tk.withdraw()

# Некорректные ключи по-умолчанию
Key1 = Key.ReadFromFile('OpenKey')
Key2 = Key.ReadFromFile('ClosedKey')
Coder1 = StringCoder(Key1)
Coder2 = StringCoder(Key2)

while True:
	print('''Выберите действие:
	1. Установить файл ключа для зашифровки
	2. Установить файл ключа для расшифровки
	3. Зашифровать строку
	4. Расшифровать строку
	5. Создать новые ключи
	6. Выйти
>>''', end = '')
	command = int(input())
	if command == 1:
		filename = input('Имя файла: ')
		Key1 = Key.ReadFromFile(filename)
		Coder1 = StringCoder(Key1)
	elif command == 2:
		filename = input('Имя файла: ')
		Key2 = Key.ReadFromFile(filename)
		Coder2 = StringCoder(Key2)
	elif command == 3:
		string = input("Введите строку для шифрования: ").replace('\n', '')
		result = Coder1.CodeString(string)
		tk.clipboard_clear()
		tk.clipboard_append(result)
		print('Зашифрованная срока(скопирована в буфер обмена):', result)
	elif command == 4:
		string = input("Введите строку для дешифрования: ")
		result = Coder2.CodeIntString(string)
		tk.clipboard_clear()
		tk.clipboard_append(result)
		print('Дешифрованная строка(скопирована в буфер обмена):', result)
	elif command == 5:
		KeyLength = int(input('Длина ключей (8-50 бит): '))
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
		
		
