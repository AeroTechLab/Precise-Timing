////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Copyright (c) 2016-2020 Leonardo Consoni <leonardojc@protonmail.com>       //
//                                                                            //
//  This file is part of Precise Timing.                                      //
//                                                                            //
//  Precise Timing is free software: you can redistribute it and/or modify    //
//  it under the terms of the GNU Lesser General Public License as published  //
//  by the Free Software Foundation, either version 3 of the License, or      //
//  (at your option) any later version.                                       //
//                                                                            //
//  Precise Timing is distributed in the hope that it will be useful,         //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of            //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              //
//  GNU Lesser General Public License for more details.                       //
//                                                                            //
//  You should have received a copy of the GNU Lesser General Public License  //
//  along with Precise Timing. If not, see <http://www.gnu.org/licenses/>.    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


/// @file timing.h
/// @brief Platform agnostic time management functions.
///
/// Wrapper library for time measurement and thread sleeping (blocking) 
/// abstracting underlying low level operating system native methods                     


#ifndef TIMING_H
#define TIMING_H
                                                                          
/// @brief Makes the calling thread wait for the specified time                                           
/// @param[in] milliseconds time interval (in milliseconds) during which the calling thread will block/sleep                                   
void Time_Delay( unsigned long milliseconds ) ;

/// @brief Gets system time in milisseconds                             
/// @return system clock ticks count converted to milliseconds 
unsigned long Time_GetExecMilliseconds();

/// @brief Gets system time in seconds                              
/// @return system clock ticks count converted to seconds
double Time_GetExecSeconds();

#endif // TIMING_H
