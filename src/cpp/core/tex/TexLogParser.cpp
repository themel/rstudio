/*
 * TexLogParser.cpp
 *
 * Copyright (C) 2009-11 by RStudio, Inc.
 *
 * This program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */

#include <core/tex/TexLogParser.hpp>

#include <boost/foreach.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <core/Error.hpp>
#include <core/FilePath.hpp>
#include <core/FileSerializer.hpp>

namespace core {
namespace tex {

namespace {

Error parseLog(
     const FilePath& logFilePath,
     const boost::regex& re,
     const boost::function<LogEntry(const boost::smatch& match)> matchToEntry,
     LogEntries* pLogEntries)
{
   // get the lines
   std::vector<std::string> lines;
   Error error = core::readStringVectorFromFile(logFilePath, &lines);
   if (error)
      return error;

   // look for error messages
   BOOST_FOREACH(std::string line, lines)
   {
      boost::smatch match;
      if (regex_match(line, match, re))
      {
         pLogEntries->push_back(matchToEntry(match));
      }
   }

   return Success();
}

LogEntry fromLatexMatch(const boost::smatch& match)
{
   return LogEntry(LogEntry::Error,
                   match[1],
                   boost::lexical_cast<int>(match[2]),
                   match[3]);
}

LogEntry fromBibtexMatch(const boost::smatch& match)
{
   return LogEntry(LogEntry::Error,
                   match[3],
                   boost::lexical_cast<int>(match[2]),
                   match[1]);
}


} // anonymous namespace

Error parseLatexLog(const FilePath& logFilePath, LogEntries* pLogEntries)
{
   return parseLog(logFilePath,
                   boost::regex ("^\\./([^:]+):([0-9]+): ([^\n]+)$"),
                   fromLatexMatch,
                   pLogEntries);
}

Error parseBibtexLog(const FilePath& logFilePath, LogEntries* pLogEntries)
{
   return parseLog(logFilePath,
                   boost::regex("^(.*)---line ([0-9]+) of file (.*)$"),
                   fromBibtexMatch,
                   pLogEntries);
  ;
}

} // namespace tex
} // namespace core 



