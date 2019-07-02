# Google Test and Code Coverage

Nailing down the fundamentals:

### Compile testapp

```
$ make testapp
g++ -isystem include -g -Wall -Wextra -pthread -c sample1.cc
g++ -isystem include -Igooglemock -Igooglemock/include -g -Wall -Wextra -pthread -c googlemock/src/gmock-all.cc
g++ -isystem include -I. -g -Wall -Wextra -pthread -c src/gtest-all.cc
ar rv gmock.a gmock-all.o gtest-all.o
ar: creating gmock.a
a - gmock-all.o
a - gtest-all.o
g++ -isystem include -g -Wall -Wextra -pthread sample1.o testapp.cc gmock.a -o testapp
```

### Run testapp
```
$ ./testapp
Running main() from testapp.cc
[==========] Running 6 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 3 tests from FactorialTest
[ RUN      ] FactorialTest.Negative
[       OK ] FactorialTest.Negative (0 ms)
[ RUN      ] FactorialTest.Zero
[       OK ] FactorialTest.Zero (0 ms)
[ RUN      ] FactorialTest.Positive
[       OK ] FactorialTest.Positive (0 ms)
[----------] 3 tests from FactorialTest (0 ms total)

[----------] 3 tests from IsPrimeTest
[ RUN      ] IsPrimeTest.Negative
[       OK ] IsPrimeTest.Negative (0 ms)
[ RUN      ] IsPrimeTest.Trivial
[       OK ] IsPrimeTest.Trivial (0 ms)
[ RUN      ] IsPrimeTest.Positive
[       OK ] IsPrimeTest.Positive (0 ms)
[----------] 3 tests from IsPrimeTest (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 2 test cases ran. (0 ms total)
[  PASSED  ] 6 tests.
```

### Some Explanations

The `testapp.cc` has the `main()` entry point and the `sample1.cc` contains the critical algorithms to be tested. Therefore, the 
executable `testapp` is the stopshop opportunity to statically link `gmock.a` into itself as well as the `sample1.o` binary to
be tested. In summary, `testapp` has the following core meat ingredients:

    - testapp.cc
    - sample1.cc
    - gmock.a (has all of the Google Test stuff)

In the `Makefile`, the `gmock.a` is the static binary artifact that has all (gmock and gtest) of the Google Test stuff. Here is why:

```
# combines both gtest and gmock into one static library. gmock.a is the entire Google Test stuff
gmock.a : gmock-all.o gtest-all.o
    $(AR) $(ARFLAGS) $@ $^

gtest-all.o : src/*.cc src/*.h include/gtest/*.h include/gtest/internal/*.h
    $(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) -c src/gtest-all.cc

gmock-all.o : googlemock/src/*.cc googlemock/include/gmock/*.h googlemock/include/gmock/internal/*.h
    $(CXX) $(CPPFLAGS) -Igooglemock -Igooglemock/include $(CXXFLAGS) -c googlemock/src/gmock-all.cc
```

### How to Get Code Coverage

This line in `Makefile` is for code coverage:

```
-lgcov -fprofile-arcs -ftest-coverage
```

To get code coverage steps:

    - make testapp
    - ./getcoverage.sh
    - cd CODE_COVERAGE/ && python -m SimpleHTTPServer

### Points to Ponder

Compilation step only produces `*.gcno`. Running the `testapp` executable producest `*.gcda`.  Running `gcov testapp.gcno` produces  `*.gcov` files.
Then running `lcov --capture --directory . --output-file gcov_result.info` produces the `gcov_result.info` file.
Finally, `genhtml gcov_result.info --output-directory outputdir/` produces `html` files showing the coverage result percentage.

### Nix Way

With the provided `shell.nix`, the `gcov`, `lcov` and `python 2.7` will be accessible by:

```
nix-shell
```

