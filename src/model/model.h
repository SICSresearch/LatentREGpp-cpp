/*
 * model.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

namespace mirt {

/*
 * Model class
 * It represents what is the model approach to use
 * Might be 1PL, 2PL, 3PL
 * */
class model {
public:
	model();
	virtual ~model();
};

} /* namespace mirt */

#endif /* MODEL_MODEL_H_ */
