from random import *
# customer = [randint(5,50) for i in range(50)]
# count = 0
# ccount = 1
# for i in customer:
#     if 5<= i <=15:
#         print("[O] ", ccount, "번째 손님 (소요시간 : {}분)".format(i), sep="")
#         count += 1
#     else:
#         print("[ ] ", ccount, "번째 손님 (소요시간 : {}분)".format(i), sep="")
#     ccount += 1
# print("총 탑승 승객 : {}명".format(count))

# ========해답============
cnt = 0
for i in range(1,51):
    time = randrange(5,50+1)
    if 5 <= time <= 15:
        print("[O] {0}번째 손님 (소요시간 : {1}분)".format(i,time))
        cnt += 1
    else:
        print("[ ] {0}번째 손님 (소요시간 : {1}분)".format(i,time))
print("총 탑승승객 : {}명".format(cnt))