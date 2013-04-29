# secret-octo-ironman [![Build Status](https://secure.travis-ci.org/meonkeys/secret-octo-ironman.png)](http://travis-ci.org/meonkeys/secret-octo-ironman)

This is a demonstration of git's
[bisect](http://git-scm.com/book/ch6-5.html#Binary-Search) feature.

# Demo script

This code has a bug, and I'm not sure what commit introduced the bug. I have
a way to quickly test if a commit contains the bug or not: I can just run
`make`. This compiles and runs my code. If `make` returns a nonzero exit
status, I know that commit has the bug.

The `Makefile` just compiles `main.c` and runs it, so I check out `main.c`.
Looks like `main()` isn't returning zero, so the test fails. I run `make`
and, sure enough, fail:

    $ make
    cc     main.c   -o main
    ./main
    make: *** [test] Error 255

I try to visually scan the changes with

    git log -p

I see tons of changes to `f2()`, but it's not easy to quickly find the commit
introducing the bug by visually scanning the changes. Let's let git do the
tedious job of testing different revisions to figure out where things started
breaking.

I'm currently looking at the tip of my `master` branch. First we tell
git that we intend to bisect.

    git bisect start

Again, we didn't start searching yet, we just announced our intent. `init` or
`config` would probably make more sense than `start` here. But `start` it is,
so let's continue.

We must provide at least one bad and one good commit to git before we can
actually kick off the binary search for the first bad commit. We've run make on
the tip of `master`, so we know this commit is bad:

    git bisect bad

And I know for sure stuff used to work back when I released v1.0. I even
tagged that commit. If I want to make sure, I can `checkout v1.0` and run
`make`. But let's assume that the bug did not exist in `v1.0`:

    git bisect good v1.0

From this last command, git returns

    Bisecting: 196 revisions left to test after this (roughly 8 steps)
    [0df160395e063ba141ad37c75c654ea0903957a3] change 66a

Git picked a commit halfway between the given bad and good commits and
guessed that 8 more steps would be requrired to find the first bad commit.

Finally, we can kick off the search for the culprit:

    git bisect run make

In the output, I see

    041cd21c815270cb1cde0665744437d4a0f92edf is the first bad commit

Git leaves me at the commit *just before* the commit introducing the bug.

To see the change introducing the bug I can use

    git bisect view -p
    
or

    git bisect visualize

I'm done, so I stop bisecting with

    git bisect reset

This returns me to the tip of my `master` branch where I then fix the bug:

    sed -i 's/return 4/return 5/' main.c
    make
    git commit -m 'fixed bug (introduced in 51166af6)' main.c
