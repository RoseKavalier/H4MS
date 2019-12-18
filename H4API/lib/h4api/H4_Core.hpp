#ifndef _H4CORE_HPP_
#define _H4CORE_HPP_

#ifdef _H4API_LIBRARY_
// * allow function to be compiled
#define _H4API_
// * do not include *.cpp files
#undef _H4API_HEADER_ONLY_
#else
// * force function to be inline
#define _H4API_ inline
// * includes *.cpp as if it were a *.hpp
// * with forced inline functions
#define _H4API_HEADER_ONLY_
#endif

#endif /* #define _H4CORE_HPP_ */