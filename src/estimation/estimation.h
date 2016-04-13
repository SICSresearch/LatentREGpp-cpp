/*
 * estimation.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_ESTIMATION_H_
#define ESTIMATION_ESTIMATION_H_

namespace mirt {


/*
 * Class to run the estimation process
 *
 * The main method is EMAlgorithm
 * */
class estimation {
	public:
		estimation();
		virtual ~estimation();

		/*
		 * Runs the EMAlgorithm to find out the parameters
		 * depending on what is the model used
		 * */
		void EMAlgortihm();
};

} /* namespace mirt */

#endif /* ESTIMATION_ESTIMATION_H_ */
