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

#include "H4Defines.hpp"

namespace h4
{
	_H4API_ CreatureAbilities & P_CreatureAbilities(int id)
	{
		return reinterpret_cast<CreatureAbilities*>(0xAB1960)[id];
	}
}