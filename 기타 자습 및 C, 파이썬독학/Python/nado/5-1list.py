a = ["유", "박", "조"]
print(a.index("조"))
a.append("하")
print(a)
a.insert(1, "정")
print(a)
a.pop()
print(a)
a.append("유")
print(a.count("유"))

numli = [5, 2, 4, 3, 1]
numli.sort()
print(numli)
numli.reverse()
print(numli)
numli.clear()
print(numli)
numli.append(1)
numli.append(True) # 다른 자료형과 같이 쓸수있음

numli.extend(a)
print(numli)