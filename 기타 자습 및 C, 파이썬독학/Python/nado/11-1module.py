# import theater_module
# theater_module.price(3)
# theater_module.price_soldier(5)

# import theater_module as mv
# mv.price(4)
# mv.price_morning(4)

# from theater_module import *
# price(4)
# price_morning(5)

# from theater_module import price, price_morning
# price(4)
# price_morning(5)
# # price_soldier(5) # 이건 오류발생

from theater_module import price_soldier as price
price(5)