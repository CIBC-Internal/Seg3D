/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

// Boost includes
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>


#include <Core/Utils/Log.h>
#include <Core/Utils/Exception.h>

#include <Core/EventHandler/Event.h>
#include <Core/EventHandler/EventHandler.h>
#include <Core/EventHandler/DefaultEventHandlerContext.h>

namespace Core
{

EventHandler::EventHandler()
{
  // Code for installing a default message handling queue
  eventhandler_context_ = EventHandlerContextHandle( new DefaultEventHandlerContext );
}

EventHandler::~EventHandler()
{
  eventhandler_context_->terminate_eventhandler();
}

bool EventHandler::is_eventhandler_thread() const
{
  // use the private context class to answer this question
  return ( eventhandler_context_->is_eventhandler_thread() );
}

void EventHandler::run_eventhandler()
{
  initialize_eventhandler();
  
  try
  {
    while ( !( wait_and_process_events() ) );
  }
  catch ( Exception& e )
  {
    CORE_LOG_ERROR(e.message());
  }
}

void EventHandler::initialize_eventhandler()
{
}

void EventHandler::install_eventhandler_context( EventHandlerContextHandle& context )
{
  // install the new context atomically
  eventhandler_context_ = context;
}

void EventHandler::post_event( boost::function< void() > function )
{
  EventHandle event = EventHandle( new EventT< boost::function< void() > > ( function ) );
  eventhandler_context_->post_event( event );
}

void EventHandler::post_and_wait_event( boost::function< void() > function )
{
  if ( is_eventhandler_thread() )
  {
    function();
  }
  else
  {
    EventHandle event = EventHandle( new EventT< boost::function< void() > > ( function ) );
    eventhandler_context_->post_and_wait_event( event );
  }
}

bool EventHandler::process_events()
{
  // use the implementation of the application context
  return ( eventhandler_context_->process_events() );
}

bool EventHandler::wait_and_process_events()
{
  // use the implementation of the application context
  return ( eventhandler_context_->wait_and_process_events() );
}

bool EventHandler::start_eventhandler()
{
  return ( eventhandler_context_->start_eventhandler( this ) );
}

bool EventHandler::eventhandler_started()
{
  return ( eventhandler_context_->eventhandler_started() );
}

void EventHandler::terminate_eventhandler()
{
  eventhandler_context_->terminate_eventhandler();
}

// TERMINATE_EVENTHANDLER

void TerminateEventHandlerThread( EventHandlerHandle handle )
{
  handle->terminate_eventhandler();
}

void TerminateEventHandler( EventHandlerHandle& handle )
{
  boost::thread termination_thread( &TerminateEventHandlerThread, handle );
  handle.reset();
}

} // end namespace Core
