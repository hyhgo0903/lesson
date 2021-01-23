#세트(집합) 중복안됨. 순서없음
set_a = {1,2,3,3,3}
print(set_a)

set_b = {"김","이","박"}
set_c = {"김","하"}

print(set_b & set_c) # 교집합
print(set_b.intersection(set_c))

print(set_b | set_c) # 합집합
print(set_b.union(set_c))

print(set_b - set_c) # 차집합
print(set_b.difference(set_c))

set_c.add("정") # 추가
set_c.remove("김") # 제거
print(set_c)