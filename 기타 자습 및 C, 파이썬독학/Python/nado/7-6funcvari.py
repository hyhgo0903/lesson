gun = 100

def cp(soldier):
    gun = 20 # 지역변수. 이게 없으면 할당안됐다고 오류남
    gun = gun - soldier
    print("[이 함수 내] 남은 총 : {}".format(gun))

print("전체 총 : {}".format(gun))
cp(2)
print("남은 총 : {}".format(gun)) #전역변수에 영향X

def cp_glo(soldier):
    global gun # 전역변수를 쓰겠다는 의미. 역시 없으면 할당안됐다고 오류남
    #복잡해지니 가급적 아래와 같이
    gun = gun - soldier
    print("[이 함수 내] 남은 총 : {}".format(gun))

print("전체 총 : {}".format(gun))
cp_glo(2)
print("남은 총 : {}".format(gun)) #전역변수에 영향

def cp_ret(gun, soldier):
    gun = gun - soldier
    print("[이 함수 내] 남은 총 : {}".format(gun))
    return gun # 이게 있어야 적용됨

print("전체 총 : {}".format(gun))
gun = cp_ret(gun, 2)
print("남은 총 : {}".format(gun)) #전역변수에 영향X

# =========quiz============

def std_weight(height, gender):
    num = 0
    height *= 0.01
    if gender == "남":
        num = (height**2)*22
    elif gender == "여":
        num = (height**2)*21
    else:
        raise "성별은 남/여 중에 입력"
    print("키 {}cm, {}성 표준 체중은 {}kg".format(height*100, gender, round((num),2)))

std_weight(175, "남")

# 이하 정답

# def std_weight(height, gender):
#     if gender == "남":
#         return height*height*22
#     else:
#         return height*height*22

# height = 175
# gender = "남"
# weight = round(std_weight(height / 100, gender),2)
# print("키 {}cm, {}성 표준 체중은 {}kg".format(height, gender, weight))