# 숫자에대한 약수 집합 구하는 알고리즘

def yaksu(num):
    yak=[]
    for i in range(1, num+1):
        if num % i == 0:
            yak.append(i)
    return yak

try:
    print(yaksu(int((input("자연수 입력: ")))))
except:
    print("오류")
