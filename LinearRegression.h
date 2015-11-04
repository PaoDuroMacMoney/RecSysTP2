/* 
 * File:   LinearRegression.h
 * Author: rodrigo
 *
 * Created on 4 de Novembro de 2015, 10:42
 */
#include "Util.h"
#include <set>
#ifndef LINEARREGRESSION_H
#define	LINEARREGRESSION_H

class LinearRegression
{
public:
    float predict(training_instance * x);
    LinearRegression(float learning_rate, float regularization_factor, int hash_size); 
    void train(int epochs, training_data * x);
    virtual ~LinearRegression();
private:
    void update(training_instance * instance, float instance_prediction_error);
    int hash_trick(std::string feature);
    //learning rate
    float alpha;
    //regularization factor
    float lambda;
    //Hash Trick Length Space
    int hash_space;
    float * helper_sum;
    float * weights;
    std::set<int> used_indices;
};

#endif	/* LINEARREGRESSION_H */

