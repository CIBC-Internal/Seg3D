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

#ifndef CORE_GRAPHICS_RENDERBUFFER_H
#define CORE_GRAPHICS_RENDERBUFFER_H

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <GL/glew.h>

namespace Core
{

class Renderbuffer;
typedef boost::shared_ptr< Renderbuffer > RenderbufferHandle;

class Renderbuffer : public boost::noncopyable
{
public:
  Renderbuffer();
  ~Renderbuffer();

  void bind();
  void unbind();

  void set_storage(int width, int height, unsigned int internal_format, int samples = 1);

  inline unsigned int get_id() const
  {
    return id_;
  }

  inline unsigned int get_target() const
  {
    return TARGET_;
  }

private:
  void safe_bind();
  void safe_unbind();

  unsigned int id_;
  int saved_id_;

  const static unsigned int TARGET_;
};

} // end namespace Core

#endif
