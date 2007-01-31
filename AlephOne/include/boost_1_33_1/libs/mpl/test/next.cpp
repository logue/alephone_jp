
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /var/cvsroot/marathon/marathon/AlephOne/include/boost_1_33_1/libs/mpl/test/next.cpp,v $
// $Date: 2007-01-31 07:15:19 $
// $Revision: 1.1 $

#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef int_<0> _0;
    typedef int_<1> _1;
    typedef int_<2> _2;

    MPL_ASSERT(( is_same< next<_0>::type, _1 > ));
    MPL_ASSERT(( is_same< next<_1>::type, _2 > ));
    MPL_ASSERT(( is_same< prior<_1>::type, _0 > ));
    MPL_ASSERT(( is_same< prior<_2>::type, _1 > ));
}
