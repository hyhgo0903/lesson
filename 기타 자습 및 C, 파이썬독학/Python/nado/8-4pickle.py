import pickle
# profile_file = open("profile.pickle", "wb")
# # b는 바이너리. 피클에선 꼭 넣어줘야. 피클에서 인코딩은 굳이 x
# profile = {"이름":"박","나이":30,"취미":["축구","골프","코딩"]}
# print(profile)
# pickle.dump(profile, profile_file)
# # profile의 정보를 뒤 file에 저장
# # 피클로 이 정보를 쓰는것임
# profile_file.close()

profile_file = open("profile.pickle", "rb")
profile = pickle.load(profile_file)
# file의 정보를 profile에 불러오기
print(profile)
profile_file.close()