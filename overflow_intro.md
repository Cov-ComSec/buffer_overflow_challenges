---
title: Introduction to Buffer Overflows
sub_title:
author: Iseefa (aka Duppy)
theme:
  name: catppuccin-macchiato
  override:
    footer:
      style: template
      left: "@duppybad"
      center: "Comsec beginning 2025"
      right: "{current_slide} / {total_slides}"
      colors:
        background: "c6a0f6"
        foreground: "494d64"
---

# Why is an overflow bad?

<!-- column_layout: [2,1] -->
<!-- column: 0-->

- A buffer is a contiguous area in memory used to store data temporarily.

<!-- new_lines: 3 -->
<!-- pause -->

- Size is often defined by the programmer in lower level langauges (We will be
  using C for this session)

<!-- new_lines: 3 -->

- The defined size does not always match the incoming data, especially when the
  user controls data input....

<!-- new_lines: 3-->
<!-- pause -->
<!-- column: 1-->

```C {all|4|4,7} +line_numbers
#include <stdio.h>

void username() {
    char buffer[64];
    
    printf("Enter your name: ");
    gets(buffer);
    
    printf("Hello, %s!\n", buffer);
}

int main() {
    printf("I hope I execute without any problems!\n");
    username();
    printf("Program completed normally.\n");
    return 0;
}
```

<!-- pause -->

_note: `gets()` is deprecated as of C11_

<!-- end_slide-->

# Cool, but how do I abuse this?

Writing past the end of a buffer is undefined behaviour to the developer, but
this does not mean it is random.

For example: We declare a `char buffer[16]`, and it is used for the string
"HELLO"

```txt
Memory: [ H][ E][ L][ L][ O][\0][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ]
         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
```

<!--pause-->

<!-- new_lines: 2-->

Now, if instead we
`strcpy(buffer, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")`

```txt
Memory: [ A][ A][ A][ A][ A][ A][ A][ A][ A][ A][ A][ A][ A][ A][ A][ A]
         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        [ A][ A][ A][ A][ A][\0]
```

<!-- pause -->

This writes to memory _after_ the declared buffer, ie, corrupting it

<!--end_slide-->

# Control flow and the stack

With this ability to write arbitrary data to memory, how do we turn this into
control of a program?

```txt
High Memory
│
├─────────────────┐
│  Return Address │
├─────────────────┤
│  Saved Frame    │
├─────────────────┤
│  buffer[16]     │  
│                 │
└─────────────────┘
│
Low Memory
```

<!-- pause -->

The return address holds the memory address of the next thing to be executed. If
we control this area, we can point the program to execute anything in memory of
our choice.

What exactly you want to be executed will depend on the situation, but we will
go over some classic CTF style implementations

<!-- end_slide-->

# Returning to prexisting function: Ret2Win

The second challenge is a "Ret2Win" style challenge, where developer has
accidentally left a call to "/bin/bash" in the binary, and no compiler
optimisation has stripped it

<!-- new_lines: 3 -->

This is where tools like `objdump`, `gdb` and `readelf` are useful. we will be
using `objdump`

<!-- pause -->

`objdump -d  chal1`
