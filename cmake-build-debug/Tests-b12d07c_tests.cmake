add_test( [==[Single edge -> A->B]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Single edge -> A->B]==]  )
set_tests_properties( [==[Single edge -> A->B]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Zero iterations -> initial distribution]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Zero iterations -> initial distribution]==]  )
set_tests_properties( [==[Zero iterations -> initial distribution]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Single iteration -> partial update]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Single iteration -> partial update]==]  )
set_tests_properties( [==[Single iteration -> partial update]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[A <-> B -> mutual link]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[A <-> B -> mutual link]==]  )
set_tests_properties( [==[A <-> B -> mutual link]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( 3-cycle /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests 3-cycle  )
set_tests_properties( 3-cycle PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Fully connected triad]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Fully connected triad]==]  )
set_tests_properties( [==[Fully connected triad]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[4-node partial mesh]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[4-node partial mesh]==]  )
set_tests_properties( [==[4-node partial mesh]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Disconnected components]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Disconnected components]==]  )
set_tests_properties( [==[Disconnected components]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Self-loop edges]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Self-loop edges]==]  )
set_tests_properties( [==[Self-loop edges]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Duplicate edges -> repeated insertion]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Duplicate edges -> repeated insertion]==]  )
set_tests_properties( [==[Duplicate edges -> repeated insertion]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[Large iteration count -> potential convergence]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[Large iteration count -> potential convergence]==]  )
set_tests_properties( [==[Large iteration count -> potential convergence]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
add_test( [==[No edges at all]==] /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug/Tests [==[No edges at all]==]  )
set_tests_properties( [==[No edges at all]==] PROPERTIES WORKING_DIRECTORY /Users/nickfarr/Desktop/DSA/pagerank/cmake-build-debug)
set( Tests_TESTS [==[Single edge -> A->B]==] [==[Zero iterations -> initial distribution]==] [==[Single iteration -> partial update]==] [==[A <-> B -> mutual link]==] 3-cycle [==[Fully connected triad]==] [==[4-node partial mesh]==] [==[Disconnected components]==] [==[Self-loop edges]==] [==[Duplicate edges -> repeated insertion]==] [==[Large iteration count -> potential convergence]==] [==[No edges at all]==])
