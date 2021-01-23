Python 3.9.0 (tags/v3.9.0:9cf6752, Oct  5 2020, 15:34:40) [MSC v.1927 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> 
========== RESTART: C:\Users\HA Family\Desktop\study\Python\output.py ==========
#하나만 출력
Hello HellHello Hell

#여러개 출력
10 20 30
Hello Hell Hello Hell

#아무것도 출력하지 않습니다.
---확인 전용선---


--- 확인 전용선 ---
엔터는 줄바꿈이 안돼
>>> 
========== RESTART: C:\Users\HA Family\Desktop\study\Python\output.py ==========
#하나만 출력
Hello HellHello Hell

#여러개 출력
10 20 30
Hello Hell Hello Hell

#아무것도 출력하지 않습니다.
---확인 전용선---


--- 확인 전용선 ---
엔터는 줄바꿈이 안돼
>>> print(type("안녕하세요"))
<class 'str'>
>>> print(type("123"))
<class 'str'>
>>> print(type(123))
<class 'int'>
>>> print(type(12.3))
<class 'float'>
>>> print(type(log(12)))
Traceback (most recent call last):
  File "<pyshell#5>", line 1, in <module>
    print(type(log(12)))
NameError: name 'log' is not defined
>>> print(type(144^2))
<class 'int'>
>>> print(type(12/166))
<class 'float'>
>>> print(""안녕하세요라"고 말했습니다.")
SyntaxError: invalid syntax
>>> print("'안녕하세요라'고 말했습니다.")
'안녕하세요라'고 말했습니다.
>>> print('"안녕하세요"라고 말했습니다.')
"안녕하세요"라고 말했습니다.
>>> print("'안녕하세요'라고 말했습니다.")
'안녕하세요'라고 말했습니다.
>>> 
====== RESTART: C:\Users\HA Family\Desktop\study\Python\string_operator.py =====
이름	나이	지역
하융호	30	서울
김김	10	강서구
바로이거야
이게아닌가?
>>> 
====== RESTART: C:\Users\HA Family\Desktop\study\Python\string_operator.py =====
이름	나이	지역
하융호	30	서울
김김	10	강서구
바로이거야
이게아닌가?
\ \ \ 	
>>> print("""zpzpzpp
zzz
dddd

ddd
dfge""")
zpzpzpp
zzz
dddd

ddd
dfge
>>> print("""zpzpzpp
zzz
dddd

ddd
dfge""")
zpzpzpp
zzz
dddd

ddd
dfge
>>> print("안녕하세요","그래")
안녕하세요 그래
>>> print("안녕하세요[5]")
안녕하세요[5]
>>> print("안녕하세요"[5])
Traceback (most recent call last):
  File "<pyshell#21>", line 1, in <module>
    print("안녕하세요"[5])
IndexError: string index out of range
>>> print("안녕하세요!"[5])
!
>>> print("안s녕s하세요!"[7])
!
>>> print("안s녕s하 세요!"[7])
요
>>> print("안s녕s하세요!"[-1])
!
>>> print("안s녕s하세요!"[-0])
안
>>> hello="안녕하세요"
>>> hello
'안녕하세요'
>>> hello='안녕하세요아님'
>>> hello
'안녕하세요아님'
>>> hello
'안녕하세요아님'
>>> print(hello[2:3])
하
>>> print(hello[2:6])
하세요아
>>> print(hello[2:7])
하세요아님
>>> print(hello[2:8])
하세요아님
>>> print(hello)
안녕하세요아님
>>> len(hello)
7
>>> print(len(hello))
7
>>> print("5")
5
>>> print(5)
5
>>> print("""\
음
하
하\
""")
음
하
하
>>> print('''
음
하
하
''')

음
하
하

>>> type(1)
<class 'int'>
>>> type(1.0)
<class 'float'>
>>> 