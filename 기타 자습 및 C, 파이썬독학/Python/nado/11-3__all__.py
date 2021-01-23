from travel import *
trip_to = vietnam.VietnamPackage()
# trip_to = thailand.VietnamPackage()
# 이건 오류 __all__구문에서 없었음. 공개를 안한 것
trip_to.detail()
# [__init__.py에서 __all__구문없으면
# 오류 : 공개 범위를 설정해줘야 함]

import inspect
import random
print(inspect.getfile(random))
# import는 파이썬의 lib폴더에 있거나
print(inspect.getfile(vietnam))
# 현재파일과 같은 경로에 있어야 불러올 수 있음
# 패키지를 lib파일에 넣어도 불러올 수 있음