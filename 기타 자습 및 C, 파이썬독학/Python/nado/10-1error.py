class BigNumberError(Exception):
    def __init__(self, msg):
        self.msg = msg
    
    def __str__(self):
        return self.msg
    # 인스턴스가 문자열로 어떻게 표현될지 결정
    # print(err)한 경우

try:
    num1 = int(input("100미만 숫자입력 : "))
    num2 = int(input("100미만 숫자입력 : "))
    if num1 >= 100 or num2 >= 100:
        raise BigNumberError("입력값 : {},{}".format(num1,num2)) # 의도적으로 에러 발생시킨것
    print("{0} / {1} = {2}".format(num1,num2,int(num1/num2)))
except ValueError:
    # try구문에서 문제가 있으면 except를 찾고 밸류에러에 해당하면 이 명령 실행
    print("잘못된 값 입력")
except ZeroDivisionError as err:
    print(err)
except BigNumberError as err:
    print("100미만 숫자로 입력해주세요")
    print(err)
except Exception as err: # 위 에러가 아닌 에러들은 이 명령에 들어옴
    print(err)
finally: # 에러가 나든말든 출력이 됨
    print("안녕")