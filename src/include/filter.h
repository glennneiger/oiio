/*
  Copyright 2008 Larry Gritz and the other authors and contributors.
  All Rights Reserved.
  Based on BSD-licensed software Copyright 2004 NVIDIA Corp.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the software's owners nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  (This is the Modified BSD License)
*/


#ifndef OPENIMAGEIO_FILTER_H
#define OPENIMAGEIO_FILTER_H

#include "version.h"

OIIO_NAMESPACE_ENTER
{

// Filter2D is the abstract data type for a 2D filter.
// The filters are NOT expected to have their results normalized.

// We haven't implemented the analogous Filter1D for now, just because
// we don't know if we'll need it.  But it should be very straightforward.

class Filter1D {
public:
    Filter1D (float width) : m_w(width) { }
    virtual ~Filter1D (void) { };

    // Set and get the width and height of the filter
    float width (void) const { return m_w; }
    void width (float newwidth) { m_w = newwidth; }

    // Evalutate the filter at an x position (relative to filter center)
    virtual float operator() (float x) const = 0;

    // Return the name of the filter, e.g., "box", "gaussian"
    virtual const std::string name (void) const = 0;

    // This static function allocates and returns an instance of the
    // specific filter implementation for the name you provide.
    // Example use:
    //        Filter1D *myfilt = Filter1::create ("box", 1);
    // The caller is responsible for deleting it when it's done.
    // If the name is not recognized, return NULL.
    static Filter1D *create (const std::string &filtername, float width);

    // Destroy a filter that was created with create().
    static void destroy (Filter1D *filt);

protected:
    float m_w;
};



class Filter2D {
public:
    Filter2D (float width, float height) : m_w(width), m_h(height) { }
    virtual ~Filter2D (void) { };

    // Set and get the width and height of the filter
    float width (void) const { return m_w; }
    void width (float newwidth) { m_w = newwidth; }
    float height (void) const { return m_h; }
    void height (float newheight) { m_h = newheight; }

    // Evalutate the filter at an x and y position (relative to filter center)
    virtual float operator() (float x, float y) const = 0;

    // Return the name of the filter, e.g., "box", "gaussian"
    virtual const std::string name (void) const = 0;

    // This static function allocates and returns an instance of the
    // specific filter implementation for the name you provide.
    // Example use:
    //        Filter2D *myfilt = Filter2::create ("box", 1, 1);
    // The caller is responsible for deleting it when it's done.
    // If the name is not recognized, return NULL.
    static Filter2D *create (const std::string &filtername,
                             float width, float height);

    // Destroy a filter that was created with create().
    static void destroy (Filter2D *filt);

protected:
    float m_w, m_h;
};


}
OIIO_NAMESPACE_EXIT

#endif // OPENIMAGEIO_FILTER_H
