/* This file is part of the Pangolin Project.
 * http://github.com/stevenlovegrove/Pangolin
 *
 * Copyright (c) 2013 Steven Lovegrove
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once


#include <string>
#include <vector>
#include <algorithm>

namespace Crazy
{


std::vector<std::string>& Split(const std::string& s, char delim, std::vector<std::string>& elements);


std::vector<std::string> Split(const std::string &s, char delim);


std::vector<std::string> Expand(const std::string &s, char open='[', char close=']', char delim=',');


std::string SanitizePath(const std::string& path);


std::string PathParent(const std::string& path, int levels = 1);


bool FileExists(const std::string& filename);


std::string FindPath(const std::string& child_path, const std::string& signature_path);


std::string PathExpand(const std::string& sPath);


bool MatchesWildcard(const std::string& str, const std::string& wildcard);


bool FilesMatchingWildcard(const std::string& wildcard_file_path, std::vector<std::string>& file_vec);


std::string MakeUniqueFilename(const std::string& filename);


bool IsPipe(const std::string& file);


bool IsPipe(int fd);


int WritablePipeFileDescriptor(const std::string& file);

/**
 * Open the file for reading. Note that it is opened with O_NONBLOCK.  The pipe
 * open is done in two stages so that the producer knows a reader is waiting
 * (but not blocked). The reader then checks PipeHasDataToRead() until it
 * returns true. The file can then be opened. Note that the file descriptor
 * should be closed after the read stream has been created so that the write
 * side of the pipe does not get signaled.
 */

int ReadablePipeFileDescriptor(const std::string& file);


bool PipeHasDataToRead(int fd);


void FlushPipe(const std::string& file);

// TODO: Tidy these inlines up / move them

inline bool StartsWith(const std::string& str, const std::string& prefix)
{
    return !str.compare(0, prefix.size(), prefix);
}

inline bool EndsWith(const std::string& str, const std::string& prefix)
{
    return !str.compare(str.size() - prefix.size(), prefix.size(), prefix);
}

inline std::string Trim(const std::string& str, const std::string& delimiters = " \f\n\r\t\v" )
{
    const size_t f = str.find_first_not_of( delimiters );
    return f == std::string::npos ?
           "" :
           str.substr( f, str.find_last_not_of( delimiters ) + 1 );
}

inline void ToUpper( std::string& str )
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

inline void ToLower( std::string& str )
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

inline std::string ToUpperCopy( const std::string& str )
{
    std::string out;
    out.resize(str.size());
    std::transform(str.begin(), str.end(), out.begin(), ::toupper);
    return out;
}

inline std::string ToLowerCopy( const std::string& str )
{
    std::string out;
    out.resize(str.size());
    std::transform(str.begin(), str.end(), out.begin(), ::tolower);
    return out;
}


}
