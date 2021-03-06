/*
 * directory.cc - Simple directory handling functions.
 *
 * This file is part of lumail - http://lumail.org/
 *
 * Copyright (c) 2015 by Steve Kemp.  All rights reserved.
 *
 **
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 dated June, 1991, or (at your
 * option) any later version.
 *
 * On Debian GNU/Linux systems, the complete text of version 2 of the GNU
 * General Public License can be found in `/usr/share/common-licenses/GPL-2'
 */


#include <sys/stat.h>
#include <dirent.h>

#include "directory.h"
#include "util.h"

/*
 * Does the directory exist?
 */
bool CDirectory::exists(std::string path)
{
    struct stat sb;

    if ((stat(path.c_str(), &sb) == 0))
        return true;
    else
        return false;
}


/*
 * Return a sorted list of files beneath the directory.
 */
std::vector < std::string > CDirectory::entries(std::string prefix)
{
    std::vector < std::string > result;

    dirent *de;
    DIR *dp;

    if ((dp = opendir(prefix.c_str())) != NULL)
    {
        result.push_back(prefix);

        while ((de = readdir(dp)) != NULL)
        {
            /*
             * Build up a string - removing duplicate "/" characters.
             */
            std::string r = prefix + "/" + de->d_name;
            r.erase(std::unique(r.begin(), r.end(), both_slashes()), r.end());


            result.push_back(r);
        }
    }

    std::sort(result.begin(), result.end());

    return result;
}
