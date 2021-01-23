name = "김갑환"
character_power_kim = 110
strong = character_power_kim > 100

'''이건 주석 선택하고
crtl+/ 해도 됨'''

print("주 캐릭은 " + name + "입니다.")
print("성능은 ", str(character_power_kim), "정도", sep="", end="되지. ")
print("강캐라고 볼 수 있는가? :"+ str(strong))

print((1==1) | (1==142)) #True |=or임
# 호출없이 부를수있는 함수
print(abs(-142))
print(pow(4, 2)) # 이하동문
print(max(5,12))
print(min(5,12))
print(round(3.14)) # 반올림

from math import *
print(floor(4.99)) # 내림
print(ceil(3.14)) # 올림
print(sqrt(16)) # 제곱근
