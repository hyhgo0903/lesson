class Unit:
    def __init__(self, name, hp):
        self.name = name
        self.hp = hp

class AttackUnit(Unit):
    def __init__(self, name, hp, dmg):
        Unit.__init__(self, name, hp)
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
    
class FlyableAttackUnit(AttackUnit, Flyable): # 다중상속
    def __init__(self, name, hp, dmg, fly_spd):
        AttackUnit.__init__(self, name, hp, dmg)
        Flyable.__init__(self, fly_spd)

valkyrie = FlyableAttackUnit("발키리", 200, 6, 5)
valkyrie.fly(valkyrie.name, "1시")