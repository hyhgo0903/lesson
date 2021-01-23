# # 쓰기 "w"rite
# score_file = open("score.txt", "w", encoding="utf8")
# print("수학 : 0", file=score_file)
# score_file.write("영어 : 50\n") #이건 줄바꿈이 따로 없어서 \n
# score_file.close()

# # 이어서 쓰기 "a"ppend
# score_file = open("score.txt", "a", encoding="utf8")
# score_file.write("과학 : 80\n")
# print("코딩 : 100", file=score_file)
# score_file.close()

# # 읽기 "r"ead
# score_file = open("score.txt", "r", encoding="utf8")
# print(score_file.readline(), end="") # 한줄씩, 한줄읽고 커서는 다음줄로 이동
# print(score_file.readline(), end="") # 비었으면 출력안함
# print(score_file.readline(), end="")
# print(score_file.readline(), end="")
# print(score_file.readline(), end="")
# # print(score_file.read()) # 한번에 모든내용
# score_file.close()

# score_file = open("score.txt", "r", encoding="utf8")
# while True:
#     line = score_file.readline()
#     if not line:
#         break
#     print(line, end="")
# score_file.close()

score_file = open("score.txt", "r", encoding="utf8")
lines = score_file.readlines() # list 형태로 저장함
for line in lines:
    print(line,end="")
score_file.close()
