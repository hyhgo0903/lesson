weather = input("날씨입력: ")
if weather == "비" or weather == "눈":
    print("우산")
elif weather == "미세먼지":
    print("마스크")
else:
    print("빈손으로")

temp = int(input("기온은?: ")) # 인풋은 무조건 문자열임 주의
if temp >= 70:
    print("불지옥")
elif temp < 70 and temp > -50: # -50 < temp < 70 이라해도 됨
    print("생존")
else:
    print("얼어붙어라")

for waiting in [0,1,2,3]: # 리스트를 넣어도 됨
    print("대기번호 : {}".format(waiting))
# = for waiting in range(4)

index = 5
while index >= 1:
    print("{}회 남음".format(index))
    index -= 1
    if index == 0:
        print("끝")

# count=0
# while True:
#     print("무한루프{}".format(count), end=" ") # Ctrl+C
#     count += 1
# 무한루프라 부득이 주석처리

customer = "하융호"
person = "Blank"
while person != customer :
    print("while문 탈출을 위해 하융호를 치세요")
    person = input("HERE: ")

