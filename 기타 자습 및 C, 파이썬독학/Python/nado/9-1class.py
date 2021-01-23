class Unit: # 붕어빵 틀
    def __init__(self, name, hp):
        #객체 만들어질때 자동으로 호출
        self.name = name # 멤버변수
        self.hp = hp
        print("{} 유닛이 생성".format(self.name))
        print("체:{}".format(self.hp))

marine1 = Unit("마린1", 40) # 인스턴스
marine2 = Unit("마린2", 40)
# marine3 = Unit("마린") 이러면 오류뜸. 수를 맞춰줘야
tank = Unit("시즈탱크", 150)
print("유닛:{}, 체:{}".format(tank.name, tank.hp))
# .으로 멤버변수에 접근할 수 있음
marine1.steam = True # 외부에서 변수를 추가한것
if marine1.steam == True:
    print("{}은 스팀팩 상태!\n".format(marine1.name))
# if marine2.steam == True: # 변수할당을 한 객체가 아니면 오류
#     print("{}는 스팀팩 상태".format(marine2.name))

class AttackUnit:
    def __init__(self, name, hp, dmg):
        self.name = name
        self.hp = hp
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
