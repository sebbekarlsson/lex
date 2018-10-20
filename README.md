# lex
> Simple lexer written in `C`.

## Compiling
> Simply run:

    make

## Running
> Make sure you have done everything in the `Compiling` step, then you can
> run the lexer doing something like:

    ./lex.out fiddle/someprogram.language

> to try it out.

## Unit test
> Coming soon!

## Notes
> This might become a new cool programming language later, so I would suggest
> to not depend on this project somehow. Feel free to copy the source code
> though.


add = int (int x, int y) {
    return x * y;    
};

something = int (int x) {
    myvar = int 300;
    myothervar = int add(x, myvar);
};

mylist =  array<int> [300, 500, 100];

// this will iterate the list and execute `something` on every item
// when it is done, it will return the modified list.
modified_list = array<int> iterate mylist with something;

iterate mylist as x with something {
    // something(x) is exposed here
    // x is the current item in the loop   
}
