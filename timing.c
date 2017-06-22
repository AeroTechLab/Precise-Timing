////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Copyright (c) 2016-2017 Leonardo Consoni <consoni_2519@hotmail.com>       //
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


#include "timing.h"

#ifdef XENOMAI

#include <native/task.h>
#include <native/timer.h>

DEFINE_NAMESPACE_INTERFACE( Timing, TIMING_INTERFACE );

// Make the calling thread wait for the given time ( in milliseconds )
void Time_Delay( unsigned long waitMilliseconds )
{
  SRTIME waitNanoseconds = 1000000 * waitMilliseconds;
  SRTIME waitTicks = rt_timer_ns2ticks( waitNanoseconds ); 
  
  rt_task_sleep( (RTIME) waitTicks );
}

// Get system time in milisseconds
unsigned long Time_GetExecMilliseconds()
{
  SRTIME execTimeNanoseconds = rt_timer_tsc2ns( rt_timer_tsc() ) ;
  
  unsigned long execTimeMilliseconds = (unsigned long) ( execTimeNanoseconds / 1000000 );
    
  return execTime;
}

// Get system time in seconds
double Time_GetExecSeconds()
{
    SRTIME execTimeNanoseconds = rt_timer_tsc2ns( rt_timer_tsc() ) ;
    
    double execTimeSeconds = (double) ( execTimeNanoseconds / 1000000000.0 );
    
    return execTimeSeconds;
}

#elif WIN32

#include <Windows.h>

LARGE_INTEGER TICKS_PER_SECOND;

// Make the calling thread wait for the given time ( in milliseconds )
void Time_Delay( unsigned long milliseconds )
{
    Sleep( milliseconds );
}

// Get system time in milliseconds
unsigned long Time_GetExecMilliseconds()
{
    LARGE_INTEGER ticks;
    double exec_time;
    
    QueryPerformanceFrequency( &TICKS_PER_SECOND );
    QueryPerformanceCounter( &ticks );
    
    exec_time = (double) ticks.QuadPart / TICKS_PER_SECOND.QuadPart;
    
    return ( (unsigned long) (1000 * exec_time) );
}

// Get system time in seconds
double Time_GetExecSeconds()
{
    LARGE_INTEGER ticks;
    double exec_time;
    
    QueryPerformanceFrequency( &TICKS_PER_SECOND );
    QueryPerformanceCounter( &ticks );
    
    exec_time = (double) ticks.QuadPart / TICKS_PER_SECOND.QuadPart;
    
    return exec_time;
}

#else // Unix

#include <time.h>

// Make the calling thread wait for the given time ( in milliseconds )
void Time_Delay( unsigned long milliseconds )
{
  struct timespec delayTime = { .tv_sec = milliseconds / 1000, .tv_nsec = ( milliseconds % 1000 ) * 1000000 };
  struct timespec remainingTime;
    
  nanosleep( &delayTime, &remainingTime );
}

// Get system time in milisseconds
unsigned long Time_GetExecMilliseconds()
{
  struct timespec systemTime;
    
  //clock_getres( CLOCK_MONOTONIC, &ts );
  //printf( "time resolution: %ld s - %ld ns\n", ts.tv_sec, ts.tv_nsec );
  
  clock_gettime( CLOCK_MONOTONIC, &systemTime );
    
  unsigned long execTime = (unsigned long) ( 1000 * systemTime.tv_sec ) + (unsigned long) ( systemTime.tv_nsec / 1000000 );
    
  return execTime;
}

// Get system time in seconds
double Time_GetExecSeconds()
{
  struct timespec systemTime;
  
  clock_gettime( CLOCK_MONOTONIC, &systemTime );
    
  double execTime = (double) systemTime.tv_sec + ((double) systemTime.tv_nsec) / 1000000000.0;
    
  return execTime;
}

#endif
