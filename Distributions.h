/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	Distributions.h
 * @author	Jasson Casey
 * @version	0.1
 *
 * @section LICENSE
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial portions of
 * the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT
 * WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include <random>
#include <algorithm>
#include <memory>

#include "Scale.h"

namespace Distributions {

enum class Type { Constant, Normal, Exponential };

template <typename RNG, typename RetType, typename ScaleType=Unit, 
            typename RealType=double>
class Size {

   public:
      typedef std::normal_distribution<RealType> dist_type;
      typedef typename dist_type::result_type param_type;
      typedef RetType result_type;
      static constexpr double scale = ScaleType::value;

   private:
      Type type;
      RNG& engine;
      param_type mean;
      param_type deviation;

      std::auto_ptr<dist_type> dist;

   public:
      explicit Size( RNG& rng, Type t, param_type m, param_type d = 100 ) : 
                     type(t), engine(rng), mean(m), deviation(d) {
         if ( type != Type::Constant ) {
            dist.reset( new dist_type( mean, deviation ) ) ; 
         }
      }
      Size( const Size& sd ) : type(sd.type), engine(sd.engine), mean(sd.mean), 
            deviation(sd.deviation) {
         if ( type == Type::Normal )
            dist.reset( new dist_type( mean, deviation ) ) ;
      }
      Size( Size&& sd ) : type(sd.type), engine(sd.engine), mean(sd.mean), 
            deviation(sd.deviation) {
         dist = sd.dist;
      }
      result_type operator()() {
         if ( type != Type::Constant ) {
            return dist->operator()(engine) * scale ;
         }
         return mean * scale ;
      }
};

template <typename RNG, typename RetType, typename ScaleType=Unit,
            typename RealType=double>
class InterArrival {

   public:
      typedef std::exponential_distribution<RealType> dist_type;
      typedef typename dist_type::result_type param_type;
      typedef RetType result_type;
      static constexpr double scale = ScaleType::value;

   private:
      Type type;
      RNG& engine;
      param_type rate;

      std::auto_ptr<dist_type> dist;

   public:
      explicit InterArrival( RNG& rng, Type t, param_type r ) : type(t), 
                              engine(rng), rate(r) {
         if ( type != Type::Constant ) {
            dist.reset( new dist_type( rate ) ) ;
         }
      }
      InterArrival( const InterArrival& rd ) : type(rd.type), engine(rd.engine),
                    rate(rd.rate) {
         if ( type == Type::Exponential )
            dist.reset( new dist_type( rate ) ) ;
      }
      InterArrival( InterArrival&& rd ) : type(rd.type), engine(rd.engine), 
                    rate(rd.rate) {
         dist = rd.dist;
      }

      inline param_type Rate() const { return rate; }

      result_type operator()() {
         if ( type != Type::Constant ) {
            return dist->operator()(engine) * scale ;
         }
         return 1/rate * scale ;
      }
};

}

#endif
