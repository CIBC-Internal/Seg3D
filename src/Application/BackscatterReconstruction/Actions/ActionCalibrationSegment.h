/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2013 Scientific Computing and Imaging Institute,
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

#ifndef APPLICATION_BACKSCATTERRECONSTRUCTION_ACTIONS_ACTIONCALIBRATIONSEGMENT_H
#define APPLICATION_BACKSCATTERRECONSTRUCTION_ACTIONS_ACTIONCALIBRATIONSEGMENT_H


#include <Core/Action/Actions.h>
#include <Core/Interface/Interface.h>

#include <Application/Layer/Layer.h>
#include <Application/Layer/DataLayer.h> 
#include <Application/Layer/LayerManager.h>
#include <Application/Layer/LayerAction.h>

#include <boost/smart_ptr.hpp> 

namespace Seg3D
{
  
class ActionCalibrationSegment : public LayerAction
{
  
CORE_ACTION(
  CORE_ACTION_TYPE( "ActionCalibrationSegment", "" )
  CORE_ACTION_ARGUMENT( "layerid", "The ID of the target layer." )
  CORE_ACTION_OPTIONAL_ARGUMENT( "sandbox", "-1", "The sandbox in which to run the action." )
  CORE_ACTION_ARGUMENT_IS_NONPERSISTENT( "sandbox" )	
  CORE_ACTION_CHANGES_PROJECT_DATA()
)
  
  // -- Constructor/Destructor --
public:
  ActionCalibrationSegment()
  {
    this->add_layer_id( this->target_layer_ );
		this->add_parameter( this->sandbox_ );
  }
  
  // -- Functions that describe action --
public:
  virtual bool validate( Core::ActionContextHandle& context );
  virtual bool run( Core::ActionContextHandle& context, Core::ActionResultHandle& result );
  
  // -- Dispatch this action from the interface --
public:
  /// DISPATCH:
  /// Dispatch an action that saves the preferences
  static void Dispatch( Core::ActionContextHandle context, std::string target_layer );

private:
  std::string target_layer_;
	SandboxID sandbox_;
};
  
} // end namespace Seg3D

#endif