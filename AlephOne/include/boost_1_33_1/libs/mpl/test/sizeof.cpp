
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /var/cvsroot/marathon/marathon/AlephOne/include/boost_1_33_1/libs/mpl/test/sizeof.cpp,v $
// $Date: 2007-01-31 07:15:19 $
// $Revision: 1.1 $

#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/aux_/test.hpp>

struct my
{
    char a[100];
};

MPL_TEST_CASE()
{
    MPL_ASSERT_RELATION( sizeof_<char>::value, ==, sizeof(char) );
    MPL_ASSERT_RELATION( sizeof_<int>::value, ==, sizeof(int) );
    MPL_ASSERT_RELATION( sizeof_<double>::value, ==, sizeof(double) );
    MPL_ASSERT_RELATION( sizeof_<my>::value, ==, sizeof(my) );
}
