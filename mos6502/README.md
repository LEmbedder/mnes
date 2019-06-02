# MOS 6502

An emulator for the
[MOS Technology 6502](https://en.wikipedia.org/wiki/MOS_Technology_6502) CPU.

## Files

Instructions are organized based on
[this](http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php/6502_Opcodes) reference.

* ```bitwise.cpp```: Implements bitwise instructions.
* ```branch.cpp```: Implements branching instructions.
* ```mos6502.cpp```: Common methods.
* ```debug.cpp```: Contains debugging methods.
* ```instructions.cpp```: Implements the instruction table.
* ```jump.cpp```: Implements jump instructions.
* ```math.cpp```: Implements mathematical instructions.
* ```registers.cpp```: Implements instructions that manipulate processor registers.
* ```stack.cpp```: Implements stack instructions.
* ```storage.cpp```: Implements storage instructions.
* ```system.cpp```: Implements ```BRK``` and ```NOP```.

## License

The project is licensed under GNU GPL v3. See LICENSE.txt for details.
