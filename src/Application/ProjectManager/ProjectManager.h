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

#ifndef APPLICATION_PROJECTMANAGER_PROJECTMANAGER_H
#define APPLICATION_PROJECTMANAGER_PROJECTMANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif 

// Boost includes
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// Core includes
#include <Core/Utils/StringUtil.h>
#include <Core/Utils/Singleton.h>
#include <Core/Utils/Log.h>
#include <Core/Utils/Exception.h>

// Application includes
#include <Core/State/StateHandler.h>
#include <Application/Project/Project.h>

namespace Seg3D
{

// Forward declaration
class ProjectManager;
  

// Class definition
class ProjectManager : public Core::StateHandler
{
  CORE_SINGLETON( ProjectManager );

  // -- Constructor/Destructor --
private:
  ProjectManager();
  virtual ~ProjectManager();
  
public:
  // NEW_PROJECT:
  // this function sets the state values of the current project to reflect the desired values
  void new_project( const std::string& project_name, const std::string& project_path );
  
  // OPEN_PROJECT:
  // this function takes the path to the desired project and loads the values from the file 
  // located at that location
  void open_project( const std::string& project_path );
  
  // SAVE_PROJECT:
  // this function saves the values in current_project_ to the current save location
  void save_project( bool autosave = false, std::string session_name = "" );
  
  // EXPORT_PROJECT:
  // this function saves the value in current_project_, and the selected session to the desired
  // save location 
  bool export_project( const std::string& export_path, const std::string& project_name, 
    const std::string& session_name );
  
  // SAVE_PROJECT_MANAGER_STATE:
  // this function calls save_states that writes the state values of ProjectManager to file
  void save_projectmanager_state();
  
  // SAVE_PROJECT_SESSION:
  // this function saves the current session to disk
  bool save_project_session( bool autosave = false, std::string session_name = "" ); 
  
  // LOAD_PROJECT_SESSION:
  // this function saves the current session to disk
  bool load_project_session( const std::string& session_name );
  
  // DELETE_PROJECT_SESSION:
  // this function deletes the current session from disk
  bool delete_project_session( const std::string& session_name );

  // SAVE_NOTE:
  // this function saves a note
  void save_note( const std::string& note );

  // GET_PROJECT_DATA_PATH:
  boost::filesystem::path get_project_data_path() const;

  // GET_TIME_SINCE:
  // function that returns a double containing the time difference since the last
  // autosave
  boost::posix_time::ptime get_last_saved_session_time_stamp() const;

  // GET_TIME_SINCE_LAST_SAVED_SESSION:
  // function that returns the difference between the current time and the last saved session
  double get_time_since_last_saved_session() const;

  // IS_SAVING:
  // function that returns whether or not the program  is currently in the process of saving
  bool is_saving() const;

public:
  Core::StateStringVectorHandle recent_projects_state_;
  Core::StateStringHandle     current_project_path_state_;
  Core::StateIntHandle      default_project_name_counter_state_;
  ProjectHandle         current_project_;

private:
  
  // ADD_TO_RECENT_PROJECTS:
  // this function adds the latest project to the list of recent projects
  void add_to_recent_projects( const std::string& project_path, 
    const std::string& project_name = "" );
  
  // CREATE_PROJECT_FOLDERS:
  // this will try and create the project folders and if is successfull return true 
  bool create_project_folders( boost::filesystem::path& path, const std::string& project_name );
  
  // RENAME_PROJECT_FOLDER
  // this function is triggered when a user changes the folder name
  void rename_project( const std::string& new_name, Core::ActionSource source );

  // SAVE_PROJECT_ONLY:
  // this function saves only the project and is used internally only. It returns if it was 
  // successful.
  bool save_project_only( const std::string& project_path_string, 
    const std::string& project_name );

  // SET_LAST_SAVED_SESSION_TIME_STAMP:
  // this function updates last_saved_session_time_stamp_ to reflect the new last saved session
  // time
  void set_last_saved_session_time_stamp();

  // GET_TIMESTAMP:
  // this function is called when you need a timestamp as a string
  std::string get_timestamp();

  // CLEANUP_PROJECTS_LIST:
  // this function cleans up projects from the recent projects list that don't exist.
  void cleanup_projects_list();
   
  void set_project_path( boost::filesystem::path path );

private:
  boost::posix_time::ptime  last_saved_session_time_stamp_;
  std::vector< Core::Color >  project_colors_;
  boost::filesystem::path   local_projectmanager_path_;

  bool            session_saving_;
  bool            changing_projects_;


};

} // end namespace seg3d

#endif

