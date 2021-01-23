try:
    file=open("info.txt","w")
    예외.발생()
except Exception as e:
    print("다음의 에러",e)
finally:
    file.close()
    print("file.closed:",file.closed)
Exception
