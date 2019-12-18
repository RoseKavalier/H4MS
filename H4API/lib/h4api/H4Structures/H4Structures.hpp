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

#ifndef _H4STRUCTURES_HPP_
#define _H4STRUCTURES_HPP_

#include "../H4_Core.hpp"
#include "../H4_Base.hpp"
#include "../H4_Vector.hpp"

namespace h4
{
#pragma pack(push, 1)
	struct CreatureAbilities
	{
		H4Vector<int> abilities;
		INT id;
	};
#pragma pack(pop)
}

#endif /* #define _H4STRUCTURES_HPP_ */