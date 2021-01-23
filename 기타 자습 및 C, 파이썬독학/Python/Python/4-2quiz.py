for key in character:
	if type(character[key]) is list:
		for a in character[key]:
			print(key,":",a)
	elif type(character[key]) is dict:
		for b in character[key]:
			print(b,":",character[key][b])
	else:
		print(key,":",character[key])
