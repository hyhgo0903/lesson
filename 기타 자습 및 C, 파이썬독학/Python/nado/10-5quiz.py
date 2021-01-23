chicken = 10
waiting = 1

class SoldOutError(Exception):
    def __init__(self,msg):
        self.msg = msg
    
    def __str__(self):
        return self.msg

while(True):
    try:
        print("[남은 치킨 : {}]".format(chicken))
        order = int(input("치킨 몇 마리 주문하시겠습니까?"))
        if order < 1:
            raise ValueError
        if order > chicken:
            print("재고보다 많음")
        else:
            print("[대기번호 {}] {}마리 주문 완료"\
                .format(waiting, order))
            waiting += 1
            chicken -= order
        if chicken == 0:
            raise SoldOutError("장사끝")
    except ValueError:
        print("잘못된 값")
    except SoldOutError as err:
        print(err)
        break