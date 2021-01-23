numbers = [273, 103, 5, 32, 65, 9, 72, 800, 99]

for number in numbers:
    if number % 2 == 0:
        print(number,"는 짝수입니다.")
    else:
        print("{}는 홀수입니다.".format(number))

print("#3번")

for number in numbers:
    print(number, "는 {} 자릿수입니다.".format(len(str(number))))

print("#4번")

list_of_list = [
    [1,2,3],
    [4,5,6,7],
    [8,9],
]

for array in list_of_list:
    for item in array:
        print(item)

print("#5번")

numbers=[1,2,3,4,5,6,7,8,9]
output=[[],[],[]]

for number in numbers:
    output[(number+2)%3].append(number)

print(output)
