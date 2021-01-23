class Unit:
    def __init__(self, name, hp, spd):
        self.name = name
        self.hp = hp
        self.spd = spd

    def move(self, location):
        print("[지상유닛 이동]", end= " ")
        print("{}: {}방향으로 이동[속도:{}]"\
            .format(self.name, location, self.spd))

class AttackUnit(Unit):
    def __init__(self, name, hp, spd, dmg):
        Unit.__init__(self, name, hp, spd)
        self.dmg = dmg

    def attack(self, location):
        print("{0} : {1} 방향으로 공격 [공:{2}]"\
            .format(self.name, location, self.dmg))
    
    def dmged(self, dmg):
        print("{0} : {1} 만큼 피해".format(self.name, dmg))
        self.hp -= dmg
        print("{0}의 체력 : {1}".format(self.name, self.hp))
        if self.hp <= 0:
            print("{0}이 사망!".format(self.name))

class Flyable:
    def __init__(self, fly_spd):
        self.fly_spd = fly_spd
    
    def fly(self, name, location):
        print("{}: {}방향으로 날아감[속도:{}]"\
            .format(name, location, self.fly_spd))
    
class FlyableAttackUnit(AttackUnit, Flyable):
    def __init__(self, name, hp, dmg, fly_spd):
        AttackUnit.__init__(self, name, hp, 0, dmg)
        # 지상스피드는 0으로 처리
        Flyable.__init__(self, fly_spd)

    def move(self, location): # 재정의
        print("[공중유닛 이동]", end= " ")
        self.fly(self.name, location)
        

vulture = AttackUnit("벌쳐", 80, 10, 20)
battle = FlyableAttackUnit("배틀크루저", 500, 25, 3)

vulture.move("11시")
battle.fly(battle.name, "9시")
battle.move("9시")
# 42행 무브로 쓸 수 있게. overload