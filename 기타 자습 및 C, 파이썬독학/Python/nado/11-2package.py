import travel.thailand # 여기엔 모듈이나 패키지만 써야
# 즉 import travel.thailand.ThailandPackage 는 오류
# from travel.thailand import ThailandPackage 처럼 쓰는건 가능
trip_to = travel.thailand.ThailandPackage()
trip_to.detail()

# from travel.thailand import ThailandPackage # 를 쓴 경우
# trip_to = ThailandPackage()
# trip_to.detail()

from travel import vietnam
trip_to = vietnam.VietnamPackage()
trip_to.detail()