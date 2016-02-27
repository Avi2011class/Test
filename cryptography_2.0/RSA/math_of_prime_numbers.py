import math
import random

class math_of_prime_numbers:
    @staticmethod
    def GCD(__1, __2): 
        # Вычисление наибольшего общего делителя двух натуральных чисел
        if __1 == 0 and __2 == 0:
            return 1
        if __1 == 0:
            return abs(__2)
        if __2 == 0:
            return abs(__1)
        __1, __2 = abs(__1), abs(__2)
        while not __2 == 0:
            __1, __2 = __2, __1 % __2
        return __1
    
    @staticmethod
    def power_mod(base, exponent, module): 
        # Быстрое возведение в степень по модулю
        result = 1
        while exponent != 0:
            if exponent % 2 == 1:
                result, exponent = (result * base) % module, exponent - 1
            else:
                base, exponent = (base * base) % module, exponent // 2
        return result

    @staticmethod
    def prime_test(number): 
        # Проверка числа на простоту "в лоб", а затем тестом Ферма
        if number == 1:
            return False
        initial_prime_numbers = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, \
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
        for divisor in initial_prime_numbers:
            if divisor * divisor > number:
                break
            if number % divisor == 0:
                return False
        ferma_test_iteration = 0
        while ferma_test_iteration < 1000:
            test_base = random.randint(7, 10 ** 10)
            if math_of_prime_numbers.GCD(test_base, number) == 1:
                ferma_test_iteration += 1
                if not math_of_prime_numbers.power_mod(test_base, number - 1, number) == 1:
                    return False
            else:
                pass
        return True

    @staticmethod
    def generate_e(phi): 
        # Поиск числа, взаимно простого с phi в порядке приоритета
        for e in [257, 65537, 17]:
            if GCD(e, phi) == 1:
                return e
        for i in range(1, 100):
            e = random.randint(20, 10000)
            if GCD(e, phi) == 1:
                return e
        for i in range(1, 100):
            e = random.randint(10 ** 4, 10 ** 6)
            if GCD(e, phi) == 1:
                return e    
        while True:
            e = random.randint(10 ** 6, 10 ** 15)
            if GCD(e, phi) == 1:
                return e

    @staticmethod
    def linear_diophantine_equations(x, y):
        # Поиск a, b таких, что ax + by = GCD(x, y), причем a > 0
        first = (x, 1, 0)
        second = (y, 0, 1)
        while second[0] != 0:
            q = first[0] // second[0]
            first, second = second, (first[0] % second[0], first[1] - q * second[1], first[2] - q * second[2])
        k = 0
        if first[1] < 0:
            k = (-first[1]) // y + 1
        return (k * y + first[1], -k * x + first[2])
        
    @staticmethod   
    def get_prime_number(min_bits, max_bits):
        # Получение простого числа, состоящего из заданного числа бит
        result = random.randint(2 ** min_bits, 2 ** max_bits)
        while not prime_test(result):
            result = random.randint(2 ** min_bits, 2 ** max_bits)
        return result
