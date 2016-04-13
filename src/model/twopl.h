/*
 * twopl.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef MODEL_TWOPL_H_
#define MODEL_TWOPL_H_

#include "model.h"

namespace mirt {

/*
 * 2PL Model
 *
 * Parameters:
 * 		Difficulty (b)
 * 		Discrimination (alpha)
 * */
class twopl : public model {
	public:
		twopl();
		virtual ~twopl();
};

} /* namespace mirt */

#endif /* MODEL_TWOPL_H_ */
