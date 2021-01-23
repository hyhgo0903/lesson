# 자료구조변경
menu = {"커피","우유","주스"} # 세트로 정의
print(menu, type(menu))
menu = list(menu)
print(menu, type(menu))
menu = tuple(menu)
print(menu, type(menu))
menu = set(menu)

# 퀴즈

from random import *
lst = [i for i in range(1,20+1)]
# 해답은 lst = range(1, 21) 이후
# lst = list(lst) 로 처리했음.
shuffle(lst) # sample함수를 쓸거라 의미는 없는데 사용하는게 조건임
print(lst)
winner = sample(lst, 4)
print("{}는 치킨 당첨,\n{}는 커피에 당첨".format(winner[0],winner[1:]))