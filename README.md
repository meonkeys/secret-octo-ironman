# secret-octo-ironman [![Build Status](https://secure.travis-ci.org/meonkeys/secret-octo-ironman.png)](http://travis-ci.org/meonkeys/secret-octo-ironman)

This is a demonstration of git's
[bisect](http://git-scm.com/book/ch6-5.html#Binary-Search) feature.

Demo script:

    git bisect good last-known-good-commit
    git bisect bad
    git bisect run make
