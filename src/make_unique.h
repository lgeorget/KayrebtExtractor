/**
 * \file make_unique.h
 * \author Laurent Georget
 * \date 2015-05-06
 * \brief Definition of make_unique because C++11 is lacking it
 */
#ifndef MAKE_UNIQUE_H
#define MAKE_UNIQUE_H
#include <memory>

/**
 * \brief Construct an object of type T and wrap it in a std::unique_ptr
 *
 * This is identical to the make_unique function available since C++14.
 * @tparam T the type of the object to wrap in a unique_ptr
 * @tparam ...Args the type of the arguments needed by the constructor of T
 * \param ...args the arguments needed by the constructor of T
 *
 * \return a unique_ptr containing a new instance of T, built with args
 */
template<typename T, typename ...Args>
inline std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#endif
