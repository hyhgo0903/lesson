class Unit:
    def __init__(self, name, hp):
        self.name = name
        self.hp = hp

class AttackUnit(Unit): # 상속
    def __init__(self, name, hp, dmg):
        Unit.__init__(self, name, hp)
        # Unit을 통해서 name hp를 받아옴
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

firebat = AttackUnit("파벳", 50, 16)
firebat.attack("5시")
firebat.dmged(30)
firebat.dmged(30)
