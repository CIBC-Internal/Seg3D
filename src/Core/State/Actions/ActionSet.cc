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

#include <Core/State/StateEngine.h>
#include <Core/State/Actions/ActionSet.h>
#include <Core/Action/Actions.h>

// REGISTER ACTION:
// Define a function that registers the action. The action also needs to be
// registered in the CMake file.
CORE_REGISTER_ACTION( Core, Set )

namespace Core
{

bool ActionSet::validate( ActionContextHandle& context )
{
  // Check whether the state exists

  // NOTE: We use lock() to avoid constructor from throwing an exception
  StateBaseHandle state( state_weak_handle_.lock() );

  // If not the state cannot be retrieved report an error
  if ( !state.get() )
  {
    if ( !( StateEngine::Instance()->get_state( stateid_, state ) ) )
    {
      context->report_error( std::string( "Unknown state variable '" ) + stateid_
          + "'" );
      return false;
    }
    state_weak_handle_ = state;
  }

  // The Variant parameter can contain both the value send from the State in
  // its right format or a string in case it is send from a script.
  // In any case we need to validate whether the value can be transcribed into
  // the type we want.

  std::string error;
  if ( !( state->validate_variant( state_value_, error ) ) )
  {
    context->report_error( error );
    return false;
  }

  if ( state->get_locked() )
  {
    context->report_error( std::string( "State variable '" ) + stateid_ + "' has been locked." );
    return false; 
  }

  return true;
}

bool ActionSet::run( ActionContextHandle& context, ActionResultHandle& result )
{
  // Get the state
  StateBaseHandle state( state_weak_handle_.lock() );

  if ( state.get() )
  {
    // Set the value
    return state->import_from_variant( state_value_, context->source() );
  }

  return false;
}

bool ActionSet::changes_project_data()
{
  StateBaseHandle state( state_weak_handle_.lock() );

  // If not the state cannot be retrieved report an error
  if ( !state )
  {
    if ( !( StateEngine::Instance()->get_state( stateid_, state ) ) )
    {
      return false;
    }
  }

  // Keep track of whether the state changes the data of the program
  return state->is_project_data();
}

} // end namespace Core
