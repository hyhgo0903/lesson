class House:
    def __init__(self, location, house_type, deal_type, price, year):
        self.location = location
        self.house_type = house_type
        self.deal_type = deal_type
        self.price = price
        self.year = year
    
    def show_detail(self):
        print(self.location, self.house_type, self.deal_type, self.price, self.year)

house = []
house1 = House("강남", "아파트", "매매" , "10억", "2010년")
house2 = House("마포", "오피스텔", "전세" , "5억", "2004년")
house3 = House("송파", "빌라", "월세" , "500/50", "2000년")
house.append(house1)
house.append(house2)
house.append(house3)
print(len(house), "대의 매물이 있습니다.")
for i in house:
    i.show_detail()