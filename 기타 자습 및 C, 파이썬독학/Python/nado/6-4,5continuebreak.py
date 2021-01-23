absent = [2,3]
sorijakeum = [5,6]
for student in range(1, 8+1):
    if student in absent:
        continue # for 이하구문 실행없이 다음 for 항목으로 가는 것
    elif student in sorijakeum:
        print("{}번 소리를 들으니 출석부르기 싫어".format(student))
        break # for 자체를 탈출
    print("{}번 왔고".format(student))

students = [1,2,3,4,5]
students = [i+100 for i in students]
print(students)

students = ["김씨", "김갑환", "미친김갑환", "오씨"]
students = [len(i) for i in students]
print(students)

students = ["Lee Mk", "Mke Ir", "Sre Le"]
students = [i.upper() for i in students]
print(students)