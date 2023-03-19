# [cyber-apocalypse-2023](https://ctf.hackthebox.com/event/details/cyber-apocalypse-2023-the-cursed-mission-821)

## Alien Saboteaur

**Category: reverse** 

**Difficulty: medium** 

## Description

You finally manage to make it into the main computer of the vessel, it's time to get this over with. You try to shutdown the vessel, however a couple of access codes unknown to you are needed. You try to figure them out, but the computer start speaking some weird language, it seems like gibberish...

## Writeup

The challenge is a Binary(vm) and a data file(bin).
Running the binary gives the following output

```sh
./vm bin
[Main Vessel Terminal]
<  Enter keycode 
> AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Unknown keycode!
```

Looking at the binary in ghidra we can see that bin is getting read into a buffer and vm_run is getting called on it.

```c
void vm_run(long param_1) {
  while (*(char *)(param_1 + 4) == '\0') {
    vm_step(param_1);
  }
}

void vm_step(uint *param_1) {
    (*(code *)(&original_ops)[(uint)*(char *)((ulong)*param_1 + *(long *)(param_1 + 0x24))])
            (param_1);
}
```

original_ops is an array of function pointers:

```c
void (*functions[])(uint *) = {vm_add,   vm_addi, vm_sub,   vm_subi, vm_mul,
                               vm_muli,  vm_div,  vm_cmp,   vm_jmp,  vm_inv,
                               vm_push,  vm_pop,  vm_mov,   vm_nop,  vm_exit,
                               vm_print, vm_putc, vm_je,    vm_jne,  vm_jle,
                               vm_jge,   vm_xor,  vm_store, vm_load, vm_input};
```

almost all the function do this as their last instruction:

```c
    *param_1 = *param_1 + 6;
```

this means that depending on every 6th char in the file the respective function is getting called.
recreating the binary in c we can easily print out which functions are getting called.
looking at the function_trace(function_trace.log) we can see 17 times input is getting called which means its reading in 17 characters.
Interesting is the last vm_je call which doesnt jump if we add the following code to the function and instead of going to the print statements 

```c
if (*param_1 == 360)
    *param_1 = 468;
```

running the binary again we get the following:

```sh
./a.out bin
[Main Vessel Terminal]
< Enter keycode 
> AAAAAAAAAAAAAAAAA                         
< Enter secret phrase
> AAAAAAAAAAAAAAAAA 
AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAA
Wrong!
```

and the function trace(function_trace_2.log) is a lot larger this time.
cleaning up the loops(function_trace_2_clean.log) we can detect some patterns.

```
    336, vm_load
    342, vm_load
    348, vm_xor
    354, vm_je --> 468
    LOST
    468, vm_addi
    474, vm_addi
    480, vm_addi
    486, vm_jle --> 336
```

this looks very much like a compare function which loops over an array.
we can see one for both of the inputs if also skip the check for the second je and print out the characters vm_je compares we get the following:

```sh
printf 'A%.0s' {1..60} | ./a.out bin 
[Main Vessel Terminal]
< Enter keycode 
> 354 - c - A
354 - 0 - A
354 - d - A
354 - 3 - A
354 - _ - A
354 - r - A
354 - 3 - A
354 - d - A
354 - _ - A
354 - 5 - A
354 - h - A
528 -  - 
< Enter secret phrase
> 1152 - C - e
1152 - C - ]
1152 - C - w
1152 - C - J
1152 - C - 3
1152 - C - @
1152 - C - V
1152 - C - l
1152 - C - u
1152 - C - 7
1152 - C - ]
1152 - C - 5
1152 - C - n
1152 - C - n
1152 - C - f
1152 - C - 6
1152 - C - l
1152 - C - 6
1152 - C - p
1152 - C - e
1152 - C - w
1152 - C - j
1152 - C - 1
1152 - C - y
1152 - C - ]
1152 - C - 1
1152 - C - p
1152 - C - 
1152 - C - l
1152 - C - n
1152 - C - 3
1152 - C - 2
1152 - C - 6
1152 - C - 6
1152 - C - 1
1152 - C - ]
Access granted, shutting down!
```

we can see that for the second comparison the As are converted to Cs. And the order is also not the same as the input. 
However using `c0d3_r3d_5h.......HTB{"""""""""""""""""""""""""""""""}` as an input we can see that some of the characters are already correct.
With that knowledge the rest can easily be bruteforced.

The resulting flag is the following: HTB{5w1rl_4r0und_7h3_4l13n_l4ngu4g3}
