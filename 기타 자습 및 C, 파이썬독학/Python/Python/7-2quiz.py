from primePy import primes
 
# upto 메서드 예제
primes_to_10 = primes.upto(10)
print("10까지의 소수 리스트:", primes_to_10)
primes_to_100 = primes.upto(100)
print("100까지의 소수 리스트:", primes_to_100)
print() # 띄어쓰기를 위해서
 
# first 메서드 예제
first_5_primes = primes.first(5)
print("처음 5개 소수 리스트:", first_5_primes)
first_10_primes = primes.first(10)
print("처음 10개 소수 리스트:", first_10_primes)
print()
 
# check 메서드 예제
print("15는 소수인가요?", primes.check(15))
print("277은 소수인가요?", primes.check(277))
print("백에서 천까지 소수의 수?", len(primes.upto(1000))-len(primes.upto(100)))
