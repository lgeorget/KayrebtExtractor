/**
 * \file make_unique.h
 * \author Laurent Georget
 * \date 2015-05-06
 * \brief Definition of make_unique because C++11 is lacking it
 */
#ifndef MAKE_UNIQUE_H
#define MAKE_UNIQUE_H
#include <memory>

template<typename T, typename ...Args>
inline std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#endif
