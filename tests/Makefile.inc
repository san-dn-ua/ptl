
# noinst_PROGRAMS += tests/PTL/VisitorTreeTest

#TESTS += tests/PTL/VisitorTreeTest

#tests_PTL_VisitorTreeTest_SOURCES = \
#	tests/VisitorTreeTest.cc

#tests_PTL_VisitorTreeTest_CPPFLAGS = \
#        -I$(top_srcdir)/${GOOGLE_TEST_INCLUDE} \
#        -I$(top_srcdir)/lib

#tests_PTL_VisitorTreeTest_LDADD = \
#        contrib/gmock/lib/libgtest.la

noinst_PROGRAMS += tests/PTL/VisitorListTest

TESTS += tests/PTL/VisitorListTest

tests_PTL_VisitorListTest_SOURCES = \
	tests/VisitorListTest.cc

tests_PTL_VisitorListTest_CPPFLAGS = \
        -I$(top_srcdir)/${GOOGLE_TEST_INCLUDE} \
        -I$(top_srcdir)/lib

tests_PTL_VisitorListTest_LDADD = \
        contrib/gmock/lib/libgtest.la


noinst_PROGRAMS += tests/PTL/IntTreeTest

TESTS += tests/PTL/IntTreeTest

tests_PTL_IntTreeTest_SOURCES = \
	tests/IntTreeTest.cc

tests_PTL_IntTreeTest_CPPFLAGS = \
        -I$(top_srcdir)/${GOOGLE_TEST_INCLUDE} \
        -I$(top_srcdir)/lib

tests_PTL_IntTreeTest_LDADD = \
        contrib/gmock/lib/libgtest.la

# ObserverTest

noinst_PROGRAMS += tests/PTL/ObserverTest

TESTS += tests/PTL/ObserverTest

tests_PTL_ObserverTest_SOURCES = \
	tests/ObserverTest.cc

tests_PTL_ObserverTest_CPPFLAGS = \
        -I$(top_srcdir)/${GOOGLE_TEST_INCLUDE} \
        -I$(top_srcdir)/lib

tests_PTL_ObserverTest_LDADD = \
        contrib/gmock/lib/libgtest.la

# ObjectPoolTest

noinst_PROGRAMS += tests/PTL/ObjectPoolTest

TESTS += tests/PTL/ObjectPoolTest

tests_PTL_ObjectPoolTest_SOURCES = \
	tests/ObjectPoolTest.cc

tests_PTL_ObjectPoolTest_CPPFLAGS = \
        -I$(top_srcdir)/${GOOGLE_TEST_INCLUDE} \
        -I$(top_srcdir)/lib

tests_PTL_ObjectPoolTest_LDADD = \
        contrib/gmock/lib/libgtest.la

# ObjectPoolTest

noinst_PROGRAMS += tests/PTL/ObjectPoolMTTest

TESTS += tests/PTL/ObjectPoolMTTest

tests_PTL_ObjectPoolMTTest_SOURCES = \
	tests/ObjectPoolMTTest.cc

tests_PTL_ObjectPoolMTTest_CPPFLAGS = \
        -I$(top_srcdir)/${GOOGLE_TEST_INCLUDE} \
        -I$(top_srcdir)/lib

tests_PTL_ObjectPoolMTTest_LDADD = \
        contrib/gmock/lib/libgtest.la

# Local Variables:
# mode: makefile
# End:
