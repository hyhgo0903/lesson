number=input()
spl=number.split(" ")
[a, b, c]=[int(spl[i]) for i in range(3)]
i=1
while 1:
	if i % a == 0 and i % b == 0 and i % c == 0 :
		break
	i+=1
print(i)
