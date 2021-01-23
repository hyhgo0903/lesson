class VietnamPackage:
    def detail(self):
        print("[베트남패키지] 3박 4일")

if __name__ == "__main__":
    print("Vietnam 모듈을 직접 실행")
    print("이 문장은 여기서 모듈을 직접 실행할때만 실행돼요")
    trip_to = VietnamPackage()
    trip_to.detail()
else:
    print("Vietnam 외부(11-3__all__.py)에서 모듈 호출")
# 11-3__all__.py에서 가져다 쓰면 이게 출력됨