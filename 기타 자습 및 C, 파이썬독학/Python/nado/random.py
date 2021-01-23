from random import *

print(random()) # 0.0이상 1.0미만 난수
print(random() * 10) # 0.0이상 10.0미만 난수
print(int(random() * 10)) # 0이상 10미만 정수난수
print(int(random() * 10) + 1) # 1이상 10이하 정수난수
print(int(random() * 45) + 1) # "     45"
print(randrange(1,46)) # 1이상 46미만의 정수난수
print(randint(1,45)) # 1부터 45포함 정수난수 양끝을 포함하는것이 차이
