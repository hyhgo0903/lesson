print("나는 %d살입니다." % 30) # d는 정수를 의미
print("나는 30%s" % "살입니다.") # s는 문자열(string)
print("나는 30%c입니다." % "살") # c는 한 글자만(character)
print("나는 %s살입니다." % 30)
print("나는 %s색과 %s색을 좋아해요." % ("파란", "빨강"))

print("나는 {}살입니다.".format(30))
print("나는 {}색과 {}색을 좋아해요.".format("파란", "빨강"))
print("나는 {0}색과 {1}색을 좋아해요.".format("파란", "빨강")) # 중괄호 안에 순서
print("나는 {1}색과 {0}색을 좋아해요.".format("파란", "빨강")) # 는 바꿀수있음

print("나는 {age}살이며 {color}색을 좋아해요.".format(age = 30, color = "빨강"))
print("나는 {age}살이며 {color}색을 좋아해요.".format(color = "빨강", age = 30))

# v3.6이상만
age = 30
color = "빨강"
print(f"나는 {age}살이며 {color}색을 좋아해요.")

print("줄바꾸고\n\"따옴표도 써보고\"\t탭후\\")
print("Blue Apple\rPine") # \r : 커서를 맨앞으로 이동해 대체
print("Blue궰\b Apple") # \b : 백스페이스

quiz = "http://google.com"
first_dot_index = quiz.index(".") # 풀이에선 replace("http://","")로 처리함
first_glza = quiz[7:first_dot_index]
print(\
first_glza[:3]\
+str(len(first_glza))\
+str(first_glza.count("e"))\
 +"!")
