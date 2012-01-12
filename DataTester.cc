/**
 * Copyright (c) 2012 Jasson Casey
 *
 * @file	DataTester.cc
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

#include "DataTester.h"
#include <iostream>

typedef SizeDistrib<std::mt19937> sd_type;

int main() {
   SizeDistrib<std::mt19937> ds1(DistribType::Constant, 1500);
   SizeDistrib<std::mt19937> ds2(DistribType::Normal, 1000);
   InterArrivalDistrib<std::mt19937> ds3(DistribType::Constant, 50);

   for(int i=0;i<10;++i) {
      std::cout << "c: " << ds1() << std::endl;
      std::cout << "n: " << ds2() << std::endl;
      std::cout << "r: " << ds3() << std::endl;

   }
}
