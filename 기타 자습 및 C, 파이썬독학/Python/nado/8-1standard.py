import sys
print("python", "java", file=sys.stdout) # 표준출력으로
print("python", "java", file=sys.stderr) # 표준에러로

score = {"수학":0, "영어":50,"코딩":100}
for sub, score in score.items(): #item은 키 밸류를 튜플형식의 list
    #('수학', 0), ('영어', 50), ('코딩', 100)] 불러옴
    print(sub.ljust(12), str(score).rjust(4), sep=":")
    # ljust는 숫자칸만큼 확보하고 왼쪽정렬. r은 오른쪽

for num in range(7, 12+1):
    print("숫자: " + str(num).zfill(3))
    # 숫자칸만큼 확보하고 zero를 fill하는것

answer = input("아무 값 : ") # 인풋은 str로 받는다(숫자라도)