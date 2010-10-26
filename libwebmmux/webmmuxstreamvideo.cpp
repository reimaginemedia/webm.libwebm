// Copyright (c) 2010 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS.  All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.

#include <cassert>
#include "webmmuxcontext.hpp"

namespace webmmux
{

StreamVideo::VideoFrame::VideoFrame()
{
}



StreamVideo::StreamVideo(
    Context& c,
    const StreamInfo& info) :
    Stream(c)
{
    m_Info = info;

}


StreamVideo::~StreamVideo()
{
    //MediaTypeUtil::Destroy(m_mt);
}


/*const BITMAPINFOHEADER& StreamVideo::GetBitmapInfoHeader() const
{
    const AM_MEDIA_TYPE& mt = m_mt;
    assert(mt.majortype == MEDIATYPE_Video);
    assert(mt.pbFormat);

    if (mt.formattype == FORMAT_VideoInfo)
    {
        assert(mt.cbFormat >= sizeof(VIDEOINFOHEADER));

        VIDEOINFOHEADER& vih = (VIDEOINFOHEADER&)(*mt.pbFormat);
        BITMAPINFOHEADER& bmih = vih.bmiHeader;
        assert(bmih.biSize >= sizeof(BITMAPINFOHEADER));

        return bmih;
    }

    assert(mt.formattype == FORMAT_VideoInfo2);

    {
        assert(mt.cbFormat >= sizeof(VIDEOINFOHEADER2));

        VIDEOINFOHEADER2& vih = (VIDEOINFOHEADER2&)(*mt.pbFormat);
        BITMAPINFOHEADER& bmih = vih.bmiHeader;
        assert(bmih.biSize >= sizeof(BITMAPINFOHEADER));

        return bmih;
    }
}*/


float StreamVideo::GetFramerate() const
{
    StreamInfo streamInfo = m_Info;
    return(streamInfo.GetFrameRate());
}


void StreamVideo::WriteTrackType()
{
    webmmux::File& f = m_context.m_file;

    f.WriteID1(0x83);     //track type
    f.Write1UInt(1);
    f.Serialize1UInt(1);  //1=video
}


bool StreamVideo::Wait() const
{
    return m_context.WaitVideo();
}


StreamVideo::frames_t& StreamVideo::GetFrames()
{
    return m_vframes;
}


StreamVideo::frames_t& StreamVideo::GetKeyFrames()
{
    return m_rframes;
}


void StreamVideo::Flush()
{
    m_context.FlushVideo(this);
}



}  //end namespace webmmux



