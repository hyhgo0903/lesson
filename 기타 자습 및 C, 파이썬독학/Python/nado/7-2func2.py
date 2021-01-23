def profile(name, age=30, lang="한글"):
    print("이름:{}\t나이:{}\t언어:{}"\
        .format(name,age,lang))
    
profile("유",40,"영어")
profile("김") # 기본값 설정됨
print()

def profile(name, age, lang):
    print("이름:{}\t나이:{}\t언어:{}"\
        .format(name,age,lang))

profile(age=40, name="유", lang="영어")
# 순서 바뀌어있어도 제대로 호출하면 인식
print()

def profile(name, age, *lang):
    print("이름:{}\t나이:{}".format(name,age), end=" ")
    for i in lang: # lang은 튜플로 받는듯. 즉 i는 튜플구성성분
        print(i, end=" ")
    print()

profile("유", 30, "영어", "한글", "이태리어", "아랍어")
profile("김", 40, "한글", "아랍어")