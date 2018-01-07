#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
	/**
	TODO:
	* Calculate the RMSE here.
	*/
	VectorXd rmse(4);
	rmse << 0,0,0,0;

	// check the validity of the following inputs:
	//  * the estimation vector size should not be zero
	//  * the estimation vector size should equal ground truth vector size
	if(estimations.size() != ground_truth.size()
			|| estimations.size() == 0){
		cout << "Invalid estimation or ground_truth data" << endl;
		return rmse;
	}

	//accumulate squared residuals
	for(unsigned int i=0; i < estimations.size(); ++i){

		VectorXd residual = estimations[i] - ground_truth[i];

		//coefficient-wise multiplication
		residual = residual.array()*residual.array();
		rmse += residual;
	}

	//calculate the mean
	rmse = rmse/estimations.size();

	//calculate the squared root
	rmse = rmse.array().sqrt();

	//return the result
	return rmse;
  
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
	/**
	TODO:
    * Calculate a Jacobian here.
	*/
	MatrixXd Hj(3,4);
	Hj << 0,0,0,0,
        0,0,0,0,
        0,0,0,0;
	//recover state parameters
	float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

	//TODO: YOUR CODE HERE 
	float psq = px*px + py*py;
	//check division by zero
	if (psq==0) {
		cout << "Division by zero in the Jacobian calculations";
	}
	//compute the Jacobian matrix
	
	Hj(0, 0) = px/pow(psq, 0.5); 
	Hj(0, 1) = py/pow(psq, 0.5); 
	Hj(1, 0) = -py/psq;
	Hj(1, 1) = px/psq;
	Hj(2, 0) = (py*(py*vx - px*vy))/pow(psq, 1.5);
	Hj(2, 1) = (px*(px*vy - py*vx))/pow(psq, 1.5);
	Hj(2, 2) = px/pow(psq, 0.5); 
	Hj(2, 3) = py/pow(psq, 0.5);
	return Hj;
}
