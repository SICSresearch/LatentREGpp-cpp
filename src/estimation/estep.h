/*
 * estep.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_ESTEP_H_
#define ESTIMATION_ESTEP_H_

#include <iostream>
#include "../model/model.h"
#include "../util/matrix.h"
#include "../util/estimationdata.h"

namespace irtpp {


/**
 * Estep of the EMAlgortihm
 *
 * */
void Estep(estimation_data&);

} /* namespace irtpp */

#endif /* ESTIMATION_ESTEP_H_ */
