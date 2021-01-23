# 외장함수. 직접 import해서 사용해야

# glob : 경로 내 폴더 / 파일목록 조회 (윈도우 dir)
import glob
print(glob.glob("*.py")) # 확장자 py인 모든 파일
print()

# os : 운영체제에서 제공하는 기본 기능
import os
print(os.getcwd()) # 현재 디렉토리 표시
print()

folder = "sample_dir"

if os.path.exists(folder):
    print("이미 존재하는 폴더로군")
    os.rmdir(folder)
    print(folder, "폴더를 삭제하였습니다.")
else:
    os.makedirs(folder) #폴더 생성
    print(folder, "폴더를 생성하였습니다.")
print()
print(os.listdir()) # glob와 유사
print()

# time : 시간관련함수
import time
print(time.localtime())
print()
print(time.strftime("%Y-%m-%d %H:%M:%S"))
print()

import datetime
print("오늘 날짜는", datetime.date.today())
print()
# timedelta : 두 날짜 사이의 간격
today = datetime.date.today() # 오늘 날짜 저장
td = datetime.timedelta(days=100) # 100일 저장
print("우리가 만난지 100일은", today + td) # 오늘부터 100일 후