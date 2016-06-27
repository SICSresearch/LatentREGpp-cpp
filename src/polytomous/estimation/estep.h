/*
 * estep.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_ESTEP_H_
#define ESTIMATION_ESTEP_H_

#include "../model/model.h"

#include "../../util/matrix.h"
#include "../type/estimationdata.h"

//Includes for testing
#include "../../test/test.h"
#include <ctime>

#include <iostream>

namespace irtpp {


/**
 * Estep of the EMAlgortihm
 *
 * Receives an estimation_data reference that MUST bring all the
 * data needed to run the Estep
 * */
void Estep(estimation_data&);

} /* namespace irtpp */

#endif /* ESTIMATION_ESTEP_H_ */
