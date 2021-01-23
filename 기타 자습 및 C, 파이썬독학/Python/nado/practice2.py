jumin = "910903-1234567"

print("성별 : " + jumin[7])
print("생년 : " + jumin[0:2]) # 0부터 셈 주의. 끝에건 미포함 주의.
print("생년월일 : " + jumin[:6]) # 시작점 부터면 생략가능
print("뒤 7자리 : " + jumin[7:]) # 끝이면 생략가능
print("뒤 7자리 : " + jumin[-7:]) # -7부터 가져옴

pyth = "Hello World"
print(pyth.lower())
print(pyth.upper())
print(pyth[0].isupper()) # true
print(len(pyth))
print(pyth.replace("Hello", "Bye"))

index = pyth.index("o")
print(index) # 하나만 갖고옴
index = pyth.index("o", index + 1) # 앞에서 찾은 위치 다음(6)부터 찾기
print(index)
print(pyth.find("o"))
print(pyth.find("Bye")) # 없으면 -1. 인덱스때와 다른점
# print(pyth.index("Bye")) # 오류
print(pyth.count("o")) # o가 몇번