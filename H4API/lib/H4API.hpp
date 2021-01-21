//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//////////////////////////////////////////////////////////////////////

//
//  ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄
// ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
// ▐░▌       ▐░▌ ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀
// ▐░▌       ▐░▌          ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌
// ▐░█▄▄▄▄▄▄▄█░▌ ▄▄▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌     ▐░▌
// ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌     ▐░▌
// ▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀      ▐░▌
// ▐░▌       ▐░▌          ▐░▌▐░▌       ▐░▌▐░▌               ▐░▌
// ▐░▌       ▐░▌ ▄▄▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌▐░▌           ▄▄▄▄█░█▄▄▄▄
// ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌          ▐░░░░░░░░░░░▌
//  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀            ▀▀▀▀▀▀▀▀▀▀▀
//

// * Note to USERS
// *
// * If you are using MSVC 2017+ and are getting errors
// * with the H4API headers, go to your project's
// * Property Pages. Under the C/C++ options, look
// * for "Conformance mode" and set it as "No".
// * It's a bug that is still not resolved in VS.
// *
// * https://developercommunity.visualstudio.com/content/problem/174539/objbaseh-error-when-compiling-with-permissive-and.html

// * H4API may now be used as a header-only style library
// * in which case all you are required to do is:
// * #include "[relative_path]/H4API.hpp"
// *               
// * It it now possible as well to complie H4API into a 
// * static library, in this case you need to write:
// * #define _H4API_LIBRARY_
// * #include "[relative_path]/H4API.hpp"
// * and link the library to your project.

// *
// * H4API Preprocessor Definitions Overview
// * 

// * _H4API_LIBRARY_
// * tells the library that it should only include header files within your project
// * and that you will rely on the static library to access the library's implementation
// * by default the library is header-only.

// * _H4API_OPERATORS_
// * tells the library to replace the new, new[], delete and delete[] operators
// * by the game's own operators.
// * be mindful of hooking too early in the launch process when using this.

// * _H4_STD_CONVERSIONS_
// * allows conversion between the following formats
// * std::vector <<==>> H4::H4Vector


// * _H4API_PATCHER_X86_
// * tells the library to include its own "patcher_x86.hpp" header within your project
// * don't use this if you prefer having your own patcher_x86 header.

#ifndef _H4API_HPP_
#define _H4API_HPP_

#include "H4api/H4_Allocator.hpp"
#include "H4api/H4_Base.hpp"
#include "H4api/H4_Constants.hpp"
#include "H4api/H4_Defines.hpp"
#include "H4api/H4_Functions.hpp"
#include "H4api/H4_Memory.hpp"
#include "H4api/H4_Vector.hpp"

#ifdef _H4API_PATCHER_X86_
// * include H4API's version of patcher_x86 header
#include "patcher_x86.hpp"
#endif

#endif /* #define _H4API_HPP_ */