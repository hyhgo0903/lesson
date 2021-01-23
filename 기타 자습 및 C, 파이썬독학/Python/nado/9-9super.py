class Unit:
    def __init__(self, name, hp, spd):
        self.name = name
        self.hp = hp
        self.spd = spd

    def move(self, location):
        print("[지상유닛 이동]", end= " ")
        print("{}: {}방향으로 이동[속도:{}]"\
            .format(self.name, location, self.spd))

class BuildingUnit(Unit):
    def __init__(self, name, hp, location):
        # Unit.__init__(self, name, hp, 0)
        super().__init__(name, hp, 0) # self가 없음
        self.location = location
# but, super는 다중상속때 문제가 생김
    
class Yoong:
    def __init__(self):
        print("Yoong 생성자")

class Ho:
    def __init__(self):
        print("Ho 생성자")

class YoongHo(Yoong, Ho):
    def __init__(self):
        super().__init__()

yoong_ho = YoongHo()
# 모두 상속받지 못함

# class YoongHo(Yoong, Ho):
#     def __init__(self):
#         Yoong.__init__(self)
#         Ho.__init__(self)
# 이렇게 해야 둘다 호출됨