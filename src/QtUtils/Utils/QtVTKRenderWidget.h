/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2015 Scientific Computing and Imaging Institute,
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

#ifndef QTUTILS_UTILS_QTVTKRENDERWIDGET_H
#define QTUTILS_UTILS_QTVTKRENDERWIDGET_H

#ifndef Q_MOC_RUN

// Glew includes
#include <GL/glew.h>

// Qt VTK includes
#undef __GLEW_H__
#include <QVTKWidget2.h>
#define __GLEW_H__


// Core includes
#include <Core/Utils/ConnectionHandler.h>
#include <Core/Viewer/AbstractViewer.h>

#endif

namespace QtUtils
{

class QtVTKRenderWidget;
class QtVTKRenderWidgetPrivate;
typedef boost::shared_ptr<QtVTKRenderWidgetPrivate> QtVTKRenderWidgetPrivateHandle;

class QtVTKRenderWidget : public QVTKWidget2, private Core::ConnectionHandler
{
  Q_OBJECT
public:
  QtVTKRenderWidget( const QGLFormat& format, QWidget* parent, const QGLWidget* share /*, Qt::WindowFlags flags*/, Core::AbstractViewerHandle viewer );
  virtual ~QtVTKRenderWidget();

  // -- internals of the QtRenderWidget --
private:
  QtVTKRenderWidgetPrivateHandle private_;

  // -- signals / slots --
public:
  /// ACTIVATE_SIGNAL:
  /// This signal is triggered when the mouse is clicked in the widget
  typedef boost::signals2::signal< void () > activate_signal_type;
  activate_signal_type activate_signal_;
};

}

#endif