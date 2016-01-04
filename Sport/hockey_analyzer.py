import re
import os
import sys

class OneTime:  # Один тайм встречи
    def __init__(self, first, second):
        self.first = first  # Голов первой комманды
        self.second = second  # Голов второй комманды

    def __str__(self):
        return '({0}, {1})'.format(self.first, self.second)

    @staticmethod
    def parse(string):
        if string:
            # 1:1
            arr = string.split(':')
            return OneTime(int(arr[0]), int(arr[1]))
        else:
            return None


class Game:
    def __init__(self, team1, team2, time1, time2, time3, overtime=None, bullits=None):
        self.team1 = team1  # Играют в гостях
        self.team2 = team2  # Играют на выезде
        self.time1 = time1
        self.time2 = time2
        self.time3 = time3
        self.overtime = overtime
        self.bullits = bullits

        self.main_time = OneTime(time1.first + time2.first + time3.first, time1.second + time2.second + time3.second)
        self.all_time = OneTime(time1.first + time2.first + time3.first, time1.second + time2.second + time3.second)
        if self.overtime:
            self.all_time.first += self.overtime.first
            self.all_time.second += self.overtime.second
        if self.bullits:
            self.all_time.first += self.bullits.first
            self.all_time.second += self.bullits.second

    def __str__(self):
        winner = 'Ничья'
        if self.all_time.first > self.all_time.second:
            winner = 'победила комманда "{0}"'.format(self.team1)
        if self.all_time.first < self.all_time.second:
            winner = 'победила комманда "{0}"'.format(self.team2)

        res_str = 'Встреча "{0}" и "{1}", {2}\n'.format(self.team1, self.team2, winner)

        res_str += '   Результаты по таймам: {0}, {1}, {2}\n'.format(self.time1, self.time2, self.time3)
        res_str += '   Результат основного времени: {0}\n'.format(self.main_time)

        if self.overtime:
            res_str += '   Результат дополнительного времени: {0}\n'.format(self.overtime)
            if self.bullits:
                res_str += '   Результат буллитов: {0}\n'.format(self.bullits)
            res_str += '   Общий счет: {0}\n'.format(self.all_time)

        return res_str

    @staticmethod
    def parse(string):
        try:
            arr = string.split('$$$')
            team1, team2 = arr[0][14:].split(' - ')
            all, time1, time2, time3 = re.findall('\d*:\d*', arr[1])
            overtime = None
            bullits = None
            if len(arr) > 2:
                overtime = re.findall('\d*:\d*', arr[2])[0]
            if len(arr) > 3:
                bullits = re.findall('\d*:\d*', arr[3])[0]
            return Game(team1, team2,
                        OneTime.parse(time1),
                        OneTime.parse(time2),
                        OneTime.parse(time3),
                        OneTime.parse(overtime),
                        OneTime.parse(bullits))
        except:
            return None


file = open('hockey.txt', 'r').readlines()
Base = [Game.parse(i) for i in file]
for index, item in enumerate(Base):
    if None == item:
        del Base[index]


def get_team_info(team):
    win = 0
    lose = 0
    tb0 = tb1 = tb2 = tb3 = tb4 = tb5 = tb6 = 0
    tm1 = tm2 = tm3 = tm4 = tm5 = tm6 = tm7 = 0
    count = 0
    for i in Base:
        if i is not None:
            if i.team1 == team:
                count += 1
                if i.all_time.first > i.all_time.second:
                    win += 1
                else:
                    lose += 1

                if i.all_time.first > 0:
                    tb0 += 1
                if i.all_time.first > 1:
                    tb1 += 1
                if i.all_time.first > 2:
                    tb2 += 1
                if i.all_time.first > 3:
                    tb3 += 1
                if i.all_time.first > 4:
                    tb4 += 1
                if i.all_time.first > 5:
                    tb5 += 1
                if i.all_time.first > 6:
                    tb6 += 1

                if i.all_time.first < 1:
                    tm1 += 1
                if i.all_time.first < 2:
                    tm2 += 1
                if i.all_time.first < 3:
                    tm3 += 1
                if i.all_time.first < 4:
                    tm4 += 1
                if i.all_time.first < 5:
                    tm5 += 1
                if i.all_time.first < 6:
                    tm6 += 1
                if i.all_time.first < 7:
                    tm7 += 1

            if i.team2 == team:
                count += 1
                if i.all_time.second > i.all_time.first:
                    win += 1
                else:
                    lose += 1

                if i.all_time.second > 0:
                    tb0 += 1
                if i.all_time.second > 1:
                    tb1 += 1
                if i.all_time.second > 2:
                    tb2 += 1
                if i.all_time.second > 3:
                    tb3 += 1
                if i.all_time.second > 4:
                    tb4 += 1
                if i.all_time.second > 5:
                    tb5 += 1
                if i.all_time.second > 6:
                    tb6 += 1

                if i.all_time.second < 1:
                    tm1 += 1
                if i.all_time.second < 2:
                    tm2 += 1
                if i.all_time.second < 3:
                    tm3 += 1
                if i.all_time.second < 4:
                    tm4 += 1
                if i.all_time.second < 5:
                    tm5 += 1
                if i.all_time.second < 6:
                    tm6 += 1
                if i.all_time.second < 7:
                    tm7 += 1
    if count == 0:
        print('Информация не найдена')
    else:
        print('Статистика по команде "{0}"'.format(team))
        print('     Матчей сыграно: {0}'.format(count))
        print('     Выиграно: {0}  Проиграно: {1}'.
              format(round(win/count * 100, 1),
                     round(lose/count * 100, 1)))
        print('     Тоталы больше: ТБ0:{0} ТБ1:{1} ТБ2:{2} ТБ3:{3} ТБ4:{4} ТБ5:{5} ТБ6:{6}'.
              format(round(tb0/count * 100, 1),
                     round(tb1/count * 100, 1),
                     round(tb2/count * 100, 1),
                     round(tb3/count * 100, 1),
                     round(tb4/count * 100, 1),
                     round(tb5/count * 100, 1),
                     round(tb6/count * 100, 1)))
        print('     Тоталы меньше: ТМ1:{0} ТМ2:{1} ТМ3:{2} ТМ4:{3} ТМ5:{4} ТМ6:{5} ТМ7:{6}'.
              format(round(tm1/count * 100, 1),
                     round(tm2/count * 100, 1),
                     round(tm3/count * 100, 1),
                     round(tm4/count * 100, 1),
                     round(tm5/count * 100, 1),
                     round(tm6/count * 100, 1),
                     round(tm7/count * 100, 1)))

get_team_info('Ванкувер Джайнтс')
get_team_info('Аризона Койотс')




