cabinet = {3:"유",100:"김", "B-100":"박"}
print(cabinet[3]) # 키를 적는것
print(cabinet.get(3))
print(cabinet.get("B-100"))
print(cabinet.get(5)) # 오류를 발생시키지 않음. cabinet[5]는 오류뜸
print(cabinet.get(5, "없는 키"))
print(3 in cabinet) # True
print(5 in cabinet) # False

print(cabinet)
cabinet["C-20"] = "조" # 추가
cabinet[100] = "정" # 갱신
del cabinet[3] # 제거
print(cabinet)

print(cabinet.keys()) #키들만 출력
print(cabinet.values()) #밸류만 출력
print(cabinet.items())

cabinet.clear() #모든값 제거
print(cabinet)