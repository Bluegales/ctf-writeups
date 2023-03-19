s = 'HTB{5w1rl_4r0und_7h3_4l13n_l4ngu4g3}'
a1 = ''
a2 = ''

for c in s:
    a1 += chr(ord(c) - 2)
    a2 += chr(ord(c) + 2)

print(a1)
print(a2)
