# 내장함수. import가 필요없이 사용가능

# input : 사용자 입력을 받는 함수
lang = input(("입력 : "))
print("{}을 입력했어".format(lang))

# dir : 어떤 객체를 넘겨줬을때, 그 객체가 어떤 변수, 함수를 갖는지 표시
print(dir())
print()
import random # 랜덤은 외장함수
print(dir())
print()
print(dir(random))
print()
lst = [1,2,3]
print(dir(lst))
print()
name = "Jim"
print(dir(name))