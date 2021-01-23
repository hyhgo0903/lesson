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
        pass # 아무것도 안하고 일단은 넘어간다

supply = BuildingUnit("디팟", 500, "7시")

def game_start():
    print("게임 시작")

def game_over():
    pass

game_start()
game_over()
