/*
 * threepl.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef MODEL_THREEPL_H_
#define MODEL_THREEPL_H_

#include "model.h"

namespace mirt {

/*
 * 3PL Model
 *
 * Parameters:
 * 		Difficulty (b)
 * 		Discrimination (alpha)
 * 		Guessing parameter (c)
 * */
class threepl : public model {
	public:
		threepl();
		virtual ~threepl();
};

} /* namespace mirt */

#endif /* MODEL_THREEPL_H_ */
