
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /var/cvsroot/marathon/marathon/AlephOne/include/boost_1_33_1/boost/mpl/set/aux_/clear_impl.hpp,v $
// $Date: 2007-01-31 06:21:21 $
// $Revision: 1.1 $

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
