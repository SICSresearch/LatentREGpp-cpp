/*
 * onepl.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef MODEL_ONEPL_H_
#define MODEL_ONEPL_H_

#include "model.h"

namespace mirt {

/*
 * 1PL Model
 *
 * Parameters:
 * 		Difficulty (b)
 * */
class onepl: public model {
	public:
		onepl();
		virtual ~onepl();
};

} /* namespace mirt */

#endif /* MODEL_ONEPL_H_ */
