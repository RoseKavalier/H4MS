//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-18                        //
//                      Last edit: 2019-12-18                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H4FUNCTIONS_HPP_
#define _H4FUNCTIONS_HPP_

#include "../H4_Core.hpp"
#include "../H4_Base.hpp"

namespace h4
{
	 /**
	  * @brief Loads the specified *.h4r file
	  *
	  * @param name File to load, relative to current directory
	  * @return Whether the specified resource was added.
	  */
	_H4API_ BOOL8 LoadResourceFile(LPCSTR name);
	/**
	 * @brief Loads all *.h4d files from the specified directory
	 *
	 * @param directory Folder to load files from, relative to current directory
	 */
	_H4API_ VOID  LoadResourcesFromDirectory(LPCSTR directory);
}

namespace h4e
{
	/**
	  * @brief Loads the specified *.h4r file
	  *
	  * @param name File to load, relative to current directory
	  * @return Whether the specified resource was added.
	  */
	_H4API_ BOOL8 LoadResourceFile(LPCSTR name);
	/**
	 * @brief Loads all *.h4d files from the specified directory
	 *
	 * @param directory Folder to load files from, relative to current directory
	 */
	_H4API_ VOID  LoadResourcesFromDirectory(LPCSTR directory);
}

#endif /* #define _H4FUNCTIONS_HPP_ */