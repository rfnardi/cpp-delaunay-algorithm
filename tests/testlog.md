
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
run-test is a Catch v2.12.2 host application.
Run with -? for options

-------------------------------------------------------------------------------
Validando operador igualdade.
-------------------------------------------------------------------------------
tests/test.cpp:36
...............................................................................

tests/test.cpp:43: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

tests/test.cpp:43: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

tests/test.cpp:43: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

tests/test.cpp:43: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

tests/test.cpp:43: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

tests/test.cpp:43: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

-------------------------------------------------------------------------------
Instância sem valores para construtor deve ser (0,0,0).
-------------------------------------------------------------------------------
tests/test.cpp:47
...............................................................................

tests/test.cpp:52: PASSED:
  REQUIRE( true == comparison )
with expansion:
  true == true

-------------------------------------------------------------------------------
Instância sem valores para construtor em array deve preencher nulos.
-------------------------------------------------------------------------------
tests/test.cpp:55
...............................................................................

tests/test.cpp:61: PASSED:
  REQUIRE( true == isP1Null )
with expansion:
  true == true

tests/test.cpp:61: PASSED:
  REQUIRE( true == isP1Null )
with expansion:
  true == true

tests/test.cpp:61: PASSED:
  REQUIRE( true == isP1Null )
with expansion:
  true == true

tests/test.cpp:61: PASSED:
  REQUIRE( true == isP1Null )
with expansion:
  true == true

tests/test.cpp:61: PASSED:
  REQUIRE( true == isP1Null )
with expansion:
  true == true

tests/test.cpp:61: PASSED:
  REQUIRE( true == isP1Null )
with expansion:
  true == true

-------------------------------------------------------------------------------
Distâncias iguais para mesmos pontos entre os métodos estáticos e não
estáticos.
-------------------------------------------------------------------------------
tests/test.cpp:65
...............................................................................

tests/test.cpp:73: PASSED:
  REQUIRE( dist1 == dist2 )
with expansion:
  10.04988f == 10.04988f

tests/test.cpp:73: PASSED:
  REQUIRE( dist1 == dist2 )
with expansion:
  7.68115f == 7.68115f

tests/test.cpp:73: PASSED:
  REQUIRE( dist1 == dist2 )
with expansion:
  8.66025f == 8.66025f

tests/test.cpp:73: PASSED:
  REQUIRE( dist1 == dist2 )
with expansion:
  3.74166f == 3.74166f

tests/test.cpp:73: PASSED:
  REQUIRE( dist1 == dist2 )
with expansion:
  6.08276f == 6.08276f

tests/test.cpp:73: PASSED:
  REQUIRE( dist1 == dist2 )
with expansion:
  3.31662f == 3.31662f

-------------------------------------------------------------------------------
Cálculo de distâncias deve ser simétrico.
-------------------------------------------------------------------------------
tests/test.cpp:77
...............................................................................

tests/test.cpp:83: PASSED:
  REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) )
with expansion:
  6.78233f == 6.78233f

tests/test.cpp:83: PASSED:
  REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) )
with expansion:
  2.44949f == 2.44949f

tests/test.cpp:83: PASSED:
  REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) )
with expansion:
  5.47723f == 5.47723f

tests/test.cpp:83: PASSED:
  REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) )
with expansion:
  5.09902f == 5.09902f

tests/test.cpp:83: PASSED:
  REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) )
with expansion:
  7.87401f == 7.87401f

tests/test.cpp:83: PASSED:
  REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) )
with expansion:
  9.21954f == 9.21954f

-------------------------------------------------------------------------------
Construtor Set deve encher de nulos caso não receba ponteiro.
-------------------------------------------------------------------------------
tests/test.cpp:89
...............................................................................

tests/test.cpp:96: PASSED:
  REQUIRE( isNullPoint == true )
with expansion:
  true == true

tests/test.cpp:96: PASSED:
  REQUIRE( isNullPoint == true )
with expansion:
  true == true

tests/test.cpp:96: PASSED:
  REQUIRE( isNullPoint == true )
with expansion:
  true == true

tests/test.cpp:96: PASSED:
  REQUIRE( isNullPoint == true )
with expansion:
  true == true

tests/test.cpp:96: PASSED:
  REQUIRE( isNullPoint == true )
with expansion:
  true == true

tests/test.cpp:96: PASSED:
  REQUIRE( isNullPoint == true )
with expansion:
  true == true

the pointers inside set ( memory addresses ):
0x7ffedb5c78b0
0x7ffedb5c7690
the pointers inside set ( memory addresses ):
0x7ffedb5c78bc
0x7ffedb5c769c
the pointers inside set ( memory addresses ):
0x7ffedb5c78c8
0x7ffedb5c76a8
the pointers inside set ( memory addresses ):
0x7ffedb5c78d4
0x7ffedb5c76b4
the pointers inside set ( memory addresses ):
0x7ffedb5c78e0
0x7ffedb5c76c0
the pointers inside set ( memory addresses ):
0x7ffedb5c78ec
0x7ffedb5c76cc
-------------------------------------------------------------------------------
Construtor Set deve fazer uma cópia dos valores inseridos para o ponteiro
interno.
-------------------------------------------------------------------------------
tests/test.cpp:101
...............................................................................

tests/test.cpp:110: PASSED:
  CHECK_FALSE( sMem == pMem )
with expansion:
  !(0x00007ffedb5c78b0 == 0x00007ffedb5c7690)

tests/test.cpp:110: PASSED:
  CHECK_FALSE( sMem == pMem )
with expansion:
  !(0x00007ffedb5c78bc == 0x00007ffedb5c769c)

tests/test.cpp:110: PASSED:
  CHECK_FALSE( sMem == pMem )
with expansion:
  !(0x00007ffedb5c78c8 == 0x00007ffedb5c76a8)

tests/test.cpp:110: PASSED:
  CHECK_FALSE( sMem == pMem )
with expansion:
  !(0x00007ffedb5c78d4 == 0x00007ffedb5c76b4)

tests/test.cpp:110: PASSED:
  CHECK_FALSE( sMem == pMem )
with expansion:
  !(0x00007ffedb5c78e0 == 0x00007ffedb5c76c0)

tests/test.cpp:110: PASSED:
  CHECK_FALSE( sMem == pMem )
with expansion:
  !(0x00007ffedb5c78ec == 0x00007ffedb5c76cc)

the pointers inside set ( memory addresses ):
0x7ffedb5c78b0
0x7ffedb5c7690
the pointers inside set ( memory addresses ):
0x7ffedb5c78bc
0x7ffedb5c769c
the pointers inside set ( memory addresses ):
0x7ffedb5c78c8
0x7ffedb5c76a8
the pointers inside set ( memory addresses ):
0x7ffedb5c78d4
0x7ffedb5c76b4
the pointers inside set ( memory addresses ):
0x7ffedb5c78e0
0x7ffedb5c76c0
the pointers inside set ( memory addresses ):
0x7ffedb5c78ec
0x7ffedb5c76cc
-------------------------------------------------------------------------------
Após instanciar Set, este  não depende do ponteiro inserido inicialmente,
podendo recebe-lo em outra stack 'filha'.
-------------------------------------------------------------------------------
tests/test.cpp:114
...............................................................................

tests/test.cpp:129: PASSED:
  CHECK( comparison == true )
with expansion:
  true == true

tests/test.cpp:129: PASSED:
  CHECK( comparison == true )
with expansion:
  true == true

tests/test.cpp:129: PASSED:
  CHECK( comparison == true )
with expansion:
  true == true

tests/test.cpp:129: PASSED:
  CHECK( comparison == true )
with expansion:
  true == true

tests/test.cpp:129: PASSED:
  CHECK( comparison == true )
with expansion:
  true == true

tests/test.cpp:129: PASSED:
  CHECK( comparison == true )
with expansion:
  true == true

===============================================================================
All tests passed (43 assertions in 8 test cases)

