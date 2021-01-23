import pickle
with open("profile.pickle","rb") as profile_file:
    print(pickle.load(profile_file))

# 불러와서 변수로 지정하는것까지 포함하는것
# with문끝내면 close할 필요도 없이 자동으로 종료해줌

with open("study.txt", "w", encoding="utf8") as study_file:
    study_file.write("파이썬인더버거")

with open("study.txt", "r", encoding="utf8") as study_file:
    print(study_file.read())

for i in range(1,3+1):
    with open("{}주차.txt".format(i),"w", encoding="utf8") as quizf:
         quizf.write("{}주차 보고\n부서 :\n이름 :\n요약 :".format(i))