def open():
    print("새 계좌 생성")

open() # 이게 없으면 정의만 해놓는 것

def deposit(balance, money):
    print("입금완료. 잔액 {0}원".format(balance + money))
    return balance + money

balance = 0
balance = deposit(balance, 1000) # 이때 함수의 프린트나옴
print(balance) # 이게 없으면 함수값을 할당하기만 한거

def withdraw(balance, money):
    if balance >= money:
        print("출금완료. 잔액 {0}원".format(balance - money))
        return balance - money
    else:
        print("잔액 부족")
        return balance

balance = withdraw(balance, 500)
print(balance)
balance = withdraw(balance, 1000)
print(balance)

balance = 1000
def withdraw_night(balance, money):
    commission = 100 # 수수료
    return commission, balance - money - commission
    # 튜플형식으로 리턴

commission, balance = withdraw_night(balance, 500)
print("수수료 {}, 잔액 {}".format(commission, balance))
