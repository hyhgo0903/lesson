from random import *

class Unit:
    def __init__(self, name, hp, spd):
        self.name = name
        self.hp = hp
        self.spd = spd
        print("{} 유닛 생성".format(name))
        # self.name 써도 되긴 함(매개변수 할당이라 그냥 씀)

    def move(self, location):
        print("[지상유닛 이동]", end= " ")
        print("{}: {}방향으로 이동[속도:{}]"\
            .format(self.name, location, self.spd))
    
    def dmged(self, dmg):
        print("{0} : {1} 만큼 피해".format(self.name, dmg))
        self.hp -= dmg
        print("{0}의 체력 : {1}".format(self.name, self.hp))
        if self.hp <= 0:
            print("{0}이 사망!".format(self.name))

class AttackUnit(Unit):
    def __init__(self, name, hp, spd, dmg):
        Unit.__init__(self, name, hp, spd)
        self.dmg = dmg

    def attack(self, location):
        print("{0} : {1} 방향으로 공격 [공:{2}]"\
            .format(self.name, location, self.dmg))

class Marine(AttackUnit):
    def __init__(self):
        AttackUnit.__init__(self, "마린", 40, 2, 5)
    
    def stimpack(self):
        if self.hp > 10:
            self.hp -= 10
            print("{} : 스팀팩 사용".format(self.name))
        else:
            print("{} : 스팀팩 사용불가".format(self.name))

class Tank(AttackUnit):
    seize_developed = False
    def __init__(self):
        AttackUnit.__init__(self, "탱크", 150, 1, 30)
        self.seize_mode = False
    
    def set_seize_mode(self):
        if Tank.seize_developed == False:
            return
        if self.seize_mode == False:
            print("{} : 시즈모드로 전환".format(self.name))
            self.dmg = 70
            self.seize_mode = True
        else:
            print("{} : 시즈모드 해제".format(self.name))
            self.dmg = 30
            self.seize_mode = False

class Flyable:
    def __init__(self, fly_spd):
        self.fly_spd = fly_spd
    
    def fly(self, name, location):
        print("{}: {}방향으로 날아감[속도:{}]"\
            .format(name, location, self.fly_spd))
    
class FlyableAttackUnit(AttackUnit, Flyable):
    def __init__(self, name, hp, dmg, fly_spd):
        AttackUnit.__init__(self, name, hp, 0, dmg)
        Flyable.__init__(self, fly_spd)

    def move(self, location):
        print("[공중유닛 이동]", end= " ")
        self.fly(self.name, location)

class Wraith(FlyableAttackUnit):
    def __init__(self):
        FlyableAttackUnit.__init__(self, "레이스", 80, 20, 5)
        self.cloaked = False
    
    def cloaking(self):
        if self.cloaked == True:
            print("{} : 클로킹 해제".format(self.name))
            self.cloaked = False
        else:
            print("{} : 클로킹 상태로".format(self.name))
            self.cloaked = True

attack_units = []
m1 = Marine()
attack_units.append(m1)
m2 = Marine()
attack_units.append(m2)
m3 = Marine()
attack_units.append(m3)
t1 = Tank()
attack_units.append(t1)
t2 = Tank()
attack_units.append(t2)
w1 = Wraith()
attack_units.append(w1)

for unit in attack_units:
    unit.move("1시")

Tank.seize_developed = True
print("시즈모드 개발완료")

for unit in attack_units:
    if isinstance(unit, Marine):
        unit.stimpack()
    elif isinstance(unit, Tank):
        unit.set_seize_mode()
    elif isinstance(unit, Wraith):
        unit.cloaking()

for unit in attack_units:
    unit.attack("1시")

for unit in attack_units:
    unit.dmged(randint(5, 20))